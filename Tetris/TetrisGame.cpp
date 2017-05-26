/** @file
  * @author Yunkin Ilya.
  */
#include "TetrisGame.h"

#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <QMessageBox>
#include <QTimer>
#include <QDebug>

#include "COMMON/GUI/ChampionsTable.h"
#include "COMMON/MAP/ColorLinesTileMap.h"
#include "Block.h"
#include "TetrisCommon.h"

static const int acceleration = 7;

/// Блок отстроенного здания, который должен упасть.
struct Drop
{
    QList<ColorLinesTile *> body;
    Drop(ColorLinesTile *topLeft, int row);
    ColorLinesTile *next(ColorLinesTile *tile);
    void down();
    bool landed();
};

Drop::Drop(ColorLinesTile *topLeft, int row)
{
    if(row > 0){
        /// левый тайл следующей строки
        ColorLinesTile *left = topLeft->getTile(0, row - 1);
        ColorLinesTile *tile = left;

        while(tile != 0){
            if(tile->getColor() == buildingColor){
                body.push_back(tile);
            }
            ColorLinesTile *right = tile->getRightTile();
            if(right == 0){
                left = left->getTopTile();
                tile = left;
            }else {
                tile = right;
            }
        }
    }
}

void Drop::down()
{
    QList<ColorLinesTile *> newBody;
    if(!landed()){
        foreach (ColorLinesTile *tile, body){
            ColorLinesTile *bottom = tile->getBottomTile();
            newBody.push_back(bottom);
        }
        foreach (ColorLinesTile *tile, body){
            tile->setColor(ColorLinesTile::NONE);
        }
        foreach (ColorLinesTile *tile, newBody){
            tile->setColor(buildingColor);
        }
        body = newBody;
    }
}

bool Drop::landed()
{
    bool ret = false;
    if(!body.isEmpty()){
        foreach (ColorLinesTile *tile, body){
            ColorLinesTile *bottom = tile->getBottomTile();
            if((bottom == 0) ||
                    ((bottom->getColor() != ColorLinesTile::NONE) &&
                     (!body.contains(bottom)))){
                ret = true;
                break;
            }
        }
    }else{
        ret = true;
    }
    return ret;
}

ColorLinesTile *Drop::next(ColorLinesTile *tile)
{
    ColorLinesTile *next = 0;
    ColorLinesTile *right = tile->getRightTile();
    if((right != 0) && (right->getColor() == blockColor)){
        next = right;
    }else{
        ColorLinesTile *top = tile->getTopTile();
        if((top != 0) && (top->getColor() == blockColor)){
            next = top;
        }else {
            ColorLinesTile *left = tile->getLeftTile();
            if((left != 0) && (left->getColor() == blockColor)){
                next = left;
            }else{
                ColorLinesTile *bottom = tile->getBottomTile();
                if((bottom != 0) && (bottom->getColor() == blockColor)){
                    next = bottom;
                }else{
                    next = tile;
                }
            }
        }
    }

    return next;
}

struct GameData
{
    QSharedPointer<Block> block;
    /// Последний успешно проделанный путь между тайлами.
    QList<ColorLinesTile *> path;
    /// То, что уже нападало.
    QList<ColorLinesTile *> building;

    QTimer timer;

    bool left;
    bool right;
    bool down;
    bool fire;

    int periodCnt;
    int blockDownPeriod;

    int level;

    /// Набранные очки.
    int coins;
    /// Флаг постановки на паузу.
    bool paused;
    ColorLinesTileMap tileMap;
    QString statistics;
    explicit GameData(TetrisGame *game);
private:
    GameData();
    explicit GameData(GameData&);
    GameData &operator =(const GameData&);
 };

GameData::GameData(TetrisGame *game)
    : block(0),
      left(false),
      right(false),
      down(false),
      fire(false),
      periodCnt(0),
      blockDownPeriod(50),
      level(1),
      coins(0),
      paused(false),
      tileMap(PLOT_COL_CNT, PLOT_ROW_CNT)
{
    QObject::connect(&timer, SIGNAL(timeout()), game, SLOT(update()));
    timer.start(TIMER_PERIOD);
}

TetrisGame::TetrisGame()
    : data(new GameData(this))
{
    srand(time(0));
}


void TetrisGame::lose()
{
    qDebug() << __PRETTY_FUNCTION__ << __LINE__;
    data->timer.stop();
    ChampionsTable t("Ilya Yunkin", "Tetris");
    t.setCoins(data->coins);
    QMessageBox::StandardButton b =
            QMessageBox::question(0, tr("Game over!"),
                                  tr("Do you want to replay?"));
    if(b == QMessageBox::Yes){
        data = QSharedPointer<GameData>(new GameData(this));
    }
}

bool TetrisGame::clearIfLined(int row)
{
    ColorLinesTile *left =
            data->tileMap.topLeft->getTile(0, row);
    ColorLinesTile *tile = left;
    bool lined = true;
    while(tile != 0){
        if(tile->getColor() != buildingColor){
            lined = false;
            break;
        }
        tile = tile->getRightTile();
    }

    if(lined){
        tile = left;
        while(tile != 0){
            tile->setColor(ColorLinesTile::NONE);
            tile = tile->getRightTile();
        }
    }


    return lined;
}

bool TetrisGame::clearIfLined()
{
    bool lined = false;

    for(int row = 0; row < PLOT_ROW_CNT; row++){
        if(clearIfLined(row)){
            lined = true;
            data->coins++;
            if(data->coins % 10 == 0){
                data->level ++;
                data->blockDownPeriod =
                        (data->blockDownPeriod - DOWN_PERIOD_DECREMENT > MIN_DOWN_PERIOD) ?
                            (data->blockDownPeriod - DOWN_PERIOD_DECREMENT) :
                            MIN_DOWN_PERIOD;
            }
            dropAfterLined(row);
            break;
        }
    }

    return lined;
}

void TetrisGame::dropAfterLined(int row)
{
    Drop d(data->tileMap.topLeft, row);
    while(!d.landed()){
        d.down();
    }
}

void TetrisGame::rotate()
{
    if(!data->block.isNull()){
        data->block->rotate();
    }
}

bool TetrisGame::isCaput()
{
    bool ret = false;
    ColorLinesTile *tile = data->tileMap.topLeft;
    while(tile != 0){
        if(tile->getColor() == buildingColor){
            ret = true;
            break;
        }
        tile = tile->getRightTile();
    }
    return ret;
}

int TetrisGame::getRowCount() const
{
    return PLOT_ROW_CNT;
}
int TetrisGame::getColCount() const
{
    return PLOT_COL_CNT;
}
int TetrisGame::getCoins() const
{
    return data->coins;
}
const QString &TetrisGame::getStatistics() const
{
    return data->statistics;
}
ColorLinesTile *TetrisGame::getRootTile() const
{
    return data->tileMap.topLeft;
}
ColorLinesTile *TetrisGame::getSelectedTile() const
{
    return 0;
}
QList<ColorLinesTile *> const &TetrisGame::getPath() const
{
    return data->path;
}

void TetrisGame::update()
{
    if(!data->paused){
        data->periodCnt++;
        while(clearIfLined()){
        }

        if(data->block == 0){
            data->block = QSharedPointer<Block>(Block::createBlock(data->tileMap.topLeft));
        }else{
            if(data->periodCnt % HORIZONTAL_MOVING_PERIOD == 0){
                if(data->left){
                    data->block->left();
                }else if(data->right){
                    data->block->right();
                }
            }
            int blockDownPeriod = (data->down) ?
                        (data->blockDownPeriod / acceleration) :
                        data->blockDownPeriod;
            if(data->periodCnt % blockDownPeriod == 0){
                if(data->block->landed()){
                    foreach (ColorLinesTile *tile, data->block->body) {
                        tile->setColor(buildingColor);
                    }
                    data->block.clear();
                }else{
                    data->block->down();
                }
            }
        }
        data->statistics =
                QString("Coins=%1 Level=%2").arg(data->coins).arg(data->level);
    }else{
        data->statistics = "Paused";
    }

    if(isCaput()){
        lose();
    }
}

void TetrisGame::keyPressed(int key, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers);
    switch (key) {
    case Qt::Key_Left: data->left = true;
        break;
    case Qt::Key_Right: data->right = true;
        break;
    case Qt::Key_Down: data->down = true;
        break;
    case Qt::Key_Space: rotate();
        break;
    default:
        break;
    }
}

void TetrisGame::keyReleased(int key)
{
    switch (key) {
    case Qt::Key_Left: data->left = false;
        break;
    case Qt::Key_Right: data->right = false;
        break;
    case Qt::Key_Down: data->down = false;
        break;
    case Qt::Key_Space: break;
    default:
        break;
    }
}

void TetrisGame::pauseToggle()
{
    data->paused = !data->paused;
}

