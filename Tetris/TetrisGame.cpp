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
#include "Lines/ColorLinesTileMap.h"

static const ColorLinesTile::Color blockColor = ColorLinesTile::CYAN;
static const ColorLinesTile::Color buildingColor = ColorLinesTile::BLACK;
static const int acceleration = 7;

enum
{
    PLOT_ROW_CNT = 20,
    PLOT_COL_CNT = 10,

    TIMER_PERIOD = 10,
    MIN_DOWN_PERIOD = 3,
    HORIZONTAL_MOVING_PERIOD = 10,
    DOWN_PERIOD_DECREMENT = 2
};

struct Block
{
    enum
    {
        BLOCK_WIDTH_MAX = 4
    };

    struct Matrix
    {
        Matrix();
        bool m[BLOCK_WIDTH_MAX][BLOCK_WIDTH_MAX];
    };

    Matrix matrix;
    ColorLinesTile::Color color;
    int col;
    int row;
    ColorLinesTile *topLeft;
    QList<ColorLinesTile *> body;
    virtual void rotate();
    void printShape(Matrix m);
    virtual void down();
    virtual void left();
    virtual void right();
    virtual bool landed();
    virtual bool lefted();
    virtual bool righted();
    Matrix getLeftTurned();
    Matrix getRightTurned();
    bool isVisible(int col, int row);
    int getPlotRow(int row);
    int getPlotCol(int col);
    QList<ColorLinesTile *> getBody(Matrix m);
    void updateBody();

    Block(ColorLinesTile *topLeft, int matrixSide = BLOCK_WIDTH_MAX);
    virtual ~Block(){}
private:
    Block();
    int matrixSide;
};

struct Line : Block
{
    Line(ColorLinesTile *topLeft);
};

struct Cross : Block
{
    Cross(ColorLinesTile *topLeft);
};

struct LBlock : Block
{
    LBlock(ColorLinesTile *topLeft);
};

struct Rect : Block
{
    Rect(ColorLinesTile *topLeft);
    void rotate(){}
};

struct Zeta : Block
{
    Zeta(ColorLinesTile *topLeft);
};

struct Zeta2 : Block
{
    Zeta2(ColorLinesTile *topLeft);
};

struct LBlock2 : Block
{
    LBlock2(ColorLinesTile *topLeft);
};

/// Блок отстроенного здания, который должен упасть.
struct Drop
{
    QList<ColorLinesTile *> body;
    Drop(ColorLinesTile *topLeft, int row);
    ColorLinesTile *next(ColorLinesTile *tile);
    void down();
    bool landed();
};

Block::Block(ColorLinesTile *topLeft, int rectSide)
    : col(BLOCK_WIDTH_MAX / 2 - 1),
      row(-BLOCK_WIDTH_MAX),
      topLeft(topLeft),
      matrixSide(rectSide)
{
}

Block::Matrix::Matrix()
{
    for(int i = 0; i < BLOCK_WIDTH_MAX; i++){
        for(int j = 0; j < BLOCK_WIDTH_MAX; j++){
            m[i][j] = false;
        }
    }
}

Block::Matrix Block::getLeftTurned()
{
    Matrix newM;
    for(int i = 0; i < matrixSide; i++){
        for(int j = 0; j < matrixSide; j++){
            newM.m[i][j] = matrix.m[matrixSide - 1 - j][i];
        }
    }
    return newM;
}

Block::Matrix Block::getRightTurned()
{
    Matrix newM;
    for(int i = 0; i < matrixSide; i++){
        for(int j = 0; j < matrixSide; j++){
            newM.m[i][j] = matrix.m[j][matrixSide - i - 1];
        }
    }
    return newM;
}

void Block::down()
{
    if(!landed()){
        row++;
        updateBody();
    }
}

void Block::right()
{
    if(!righted()){
        col++;
        updateBody();
    }
}

void Block::left()
{
    if(!lefted()){
        col--;
        updateBody();
    }
}

void Block::printShape(Matrix m)
{
    for(int i = 0; i < BLOCK_WIDTH_MAX; i++){
        qDebug() << (m.m[0][i] ? 'x' : ' ')
                << (m.m[1][i] ? 'x' : ' ')
                << (m.m[2][i] ? 'x' : ' ')
                << (m.m[3][i] ? 'x' : ' ');
    }
    qDebug() << "";
}

void Block::rotate()
{
    Matrix newMatrix = getLeftTurned();
    printShape(matrix);
    printShape(newMatrix);

    bool ok = true;
    for(int i = 0; i < matrixSide; i++){
        for(int j = 0; j < matrixSide; j++){
            int plotRow = getPlotRow(j);
            int plotCol = getPlotCol(i);
            bool visibleOrUpper = (plotRow < PLOT_ROW_CNT) &&
                    (plotCol >= 0) && (plotCol < PLOT_COL_CNT);
            if((newMatrix.m[i][j]) && (!visibleOrUpper)){
                ok = false;
                break;
            }else if((newMatrix.m[i][j]) && isVisible(i, j)){
                ColorLinesTile *tile = topLeft->getTile(plotCol, plotRow);
                if(tile->getColor() == buildingColor){
                    ok = false;
                    break;
                }
            }
        }
    }
    if(ok){
        matrix = newMatrix;
        updateBody();
    }
}

bool Block::landed()
{
    bool ret = false;

    if(row > PLOT_ROW_CNT - 1){
        ret = true;
    }else{
        foreach (ColorLinesTile *tile, body){
            ColorLinesTile *bottom = tile->getBottomTile();
            if((bottom == 0) ||
                    ((bottom->getColor() != ColorLinesTile::NONE) &&
                     (!body.contains(bottom)))){
                ret = true;
                break;
            }
        }
    }

    return ret;
}

bool Block::lefted()
{
    bool ret = false;
    foreach (ColorLinesTile *tile, body){
        ColorLinesTile *left = tile->getLeftTile();
        if((left == 0) || (left->getColor() == buildingColor)){
            ret = true;
            break;
        }
    }

    for(int mcol = 0; mcol < matrixSide; ++mcol){
        for(int mrow = 0; mrow < matrixSide; ++mrow){
            if(matrix.m[mcol][mrow] && (col + mcol <= 0)){
                ret = true;
                break;
            }
        }
    }

    return ret;
}

bool Block::righted()
{
    bool ret = false;
    foreach (ColorLinesTile *tile, body){
        ColorLinesTile *right = tile->getRightTile();
        if((right == 0) || (right->getColor() == buildingColor)){
            ret = true;
            break;
        }
    }

    for(int mcol = 0; mcol < matrixSide; ++mcol){
        for(int mrow = 0; mrow < matrixSide; ++mrow){
            if(matrix.m[mcol][mrow] && (col + mcol >= (PLOT_COL_CNT - 1))){
                ret = true;
                break;
            }
        }
    }

    return ret;
}

bool Block::isVisible(int col, int row)
{
    int plotRow = getPlotRow(row);
    int plotCol = getPlotCol(col);
    return (plotRow >= 0) && (plotRow < PLOT_ROW_CNT) &&
            (plotCol >= 0) && (plotCol < PLOT_COL_CNT);
}

int Block::getPlotRow(int row)
{
    return row + this->row;
}

int Block::getPlotCol(int col)
{
    return col + this->col;
}

QList<ColorLinesTile *> Block::getBody(Matrix m)
{
    QList<ColorLinesTile *> body;
    for(int j = 0; j < BLOCK_WIDTH_MAX; j++){
        for(int i = 0; i < BLOCK_WIDTH_MAX; i++){
            if(isVisible(i, j)){
                if(m.m[i][j]){
                    body.push_back(topLeft->getTile(i + col, getPlotRow(j)));
                }
            }
        }
    }
    return body;
}

void Block::updateBody()
{
    foreach (ColorLinesTile *tile, body){
        tile->setColor(ColorLinesTile::NONE);
    }
    QList<ColorLinesTile *> newBody = getBody(matrix);
    foreach (ColorLinesTile *tile, newBody){
        tile->setColor(color);
    }
    body = newBody;
}

Line::Line(ColorLinesTile *topLeft)
    : Block(topLeft)
{
    color = blockColor;
    for(int i = 0; i < BLOCK_WIDTH_MAX; i++){
        matrix.m[i][BLOCK_WIDTH_MAX - 1] = true;
    }
}

Cross::Cross(ColorLinesTile *topLeft)
    : Block(topLeft, 3)
{
    color = blockColor;
    for(int i = 0; i < BLOCK_WIDTH_MAX; i++){
        for(int j = 0; j < BLOCK_WIDTH_MAX; j++){
            matrix.m[i][j] = false;
        }
    }
    matrix.m[0][0] = true;
    matrix.m[1][0] = true;
    matrix.m[2][0] = true;
    matrix.m[1][1] = true;
}


Rect::Rect(ColorLinesTile *topLeft)
    : Block(topLeft)
{
    color = blockColor;
    matrix.m[BLOCK_WIDTH_MAX/2][BLOCK_WIDTH_MAX/2] = true;
    matrix.m[BLOCK_WIDTH_MAX/2 - 1][BLOCK_WIDTH_MAX/2] = true;
    matrix.m[BLOCK_WIDTH_MAX/2][BLOCK_WIDTH_MAX/2 + 1] = true;
    matrix.m[BLOCK_WIDTH_MAX/2 - 1][BLOCK_WIDTH_MAX/2 + 1] = true;
}

Zeta::Zeta(ColorLinesTile *topLeft)
    : Block(topLeft, 3)
{
    color = blockColor;
    matrix.m[0][0] = true;
    matrix.m[1][0] = true;
    matrix.m[1][1] = true;
    matrix.m[2][1] = true;
}

Zeta2::Zeta2(ColorLinesTile *topLeft)
    : Block(topLeft, 3)
{
    color = blockColor;
    matrix.m[0][1] = true;
    matrix.m[1][0] = true;
    matrix.m[2][0] = true;
    matrix.m[1][1] = true;
}

LBlock::LBlock(ColorLinesTile *topLeft)
    : Block(topLeft, 3)
{
    color = blockColor;
    matrix.m[0][0] = true;
    matrix.m[0][1] = true;
    matrix.m[1][1] = true;
    matrix.m[2][1] = true;
}

LBlock2::LBlock2(ColorLinesTile *topLeft)
    : Block(topLeft, 3)
{
    color = blockColor;
    matrix.m[0][1] = true;
    matrix.m[0][0] = true;
    matrix.m[1][0] = true;
    matrix.m[2][0] = true;
}

Drop::Drop(ColorLinesTile *topLeft, int row)
{
    if(row > 0){
        /// левый тайл следующей строки
        ColorLinesTile *left = topLeft->getTile(0, row - 1);
        ColorLinesTile *tile = left;
        //        while ((tile != 0) && (tile->getColor() != buildingColor)){
        //            ColorLinesTile *right = tile->getRightTile();
        //            if(right == 0){
        //                left = left->getTopTile();
        //                tile = left;
        //            }else {
        //        tile = right;
        //    }
        //        }

        //        /// Найден уголок блока
        //        if(tile != 0){
        //            ColorLinesTile *first = tile;
        //            tile->setColor(ColorLinesTile::RED);
        //            tile = next(first);
        //        }
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
    /// Создает новую падающую фигуру.
    Block *createBlock();
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

Block* GameData::createBlock()
{
    enum
    {
        LINE,
        CROSS,
        L_BLOCK,
        RECT,
        ZETA,
        ZETA2,
        L_BLOCK2,

        COUNT
    };

    Block *block = 0;
    int type = rand() % COUNT;
    qDebug() << type;
    switch (type) {
    case LINE:
        block = new Line(tileMap.topLeft);
        break;
    case CROSS:
        block = new Cross(tileMap.topLeft);
        break;
    case L_BLOCK:
        block = new LBlock(tileMap.topLeft);
        break;
    case RECT:
        block = new Rect(tileMap.topLeft);
        break;
    case ZETA:
        block = new Zeta(tileMap.topLeft);
        break;
    case ZETA2:
        block = new Zeta2(tileMap.topLeft);
        break;
    case L_BLOCK2:
        block = new LBlock2(tileMap.topLeft);
        break;
    default:
        assert(false);
        break;
    }
    return block;
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
            data->block = QSharedPointer<Block>(data->createBlock());
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

