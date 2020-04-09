/** @file
  * @author Yunkin Ilya.
  */
#include "ClickLinesGame.h"

#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <QMessageBox>
#include <QQueue>
#include <QSet>

#include "COMMON/GUI/ChampionsTable.h"

enum
{
    PLOT_ROW_CNT = 10,
    PLOT_COL_CNT = 10,
    COLOR_CNT = 3
};

class NeighboursFinder
{
    const ColorLinesTile::Color color;
    QSet<ColorLinesTile *> neighbours;
    QQueue<ColorLinesTile *> queue; ///< Очередь на посещение
    /// Получить список соприкасающихся тайлов того же цвета.
public:
    explicit NeighboursFinder(ColorLinesTile *tile);
    /// Возвращает список, включающий всех соседей тайла,
    /// переданного в конструктор, имеющих с ним один цвет, включая сам тайл.
    QSet<ColorLinesTile *> findNeighbours();
    void enqueueChild(ColorLinesTile *child);
};

NeighboursFinder::NeighboursFinder(ColorLinesTile *tile)
    : color(tile->getColor())
{
    assert(tile != 0);
    queue.enqueue(tile);
    neighbours.insert(tile);
}

QSet<ColorLinesTile *> NeighboursFinder::findNeighbours()
{
    while(!queue.isEmpty()){
        ColorLinesTile *current = queue.takeFirst();
        enqueueChild(current->getLeftTile());
        enqueueChild(current->getRightTile());
        enqueueChild(current->getTopTile());
        enqueueChild(current->getBottomTile());
    }
    return neighbours;
}

void NeighboursFinder::enqueueChild(ColorLinesTile *child)
{
    if((child != 0) &&
            (child->getColor() == color) &&
            (!neighbours.contains(child))){
        queue.enqueue(child);
        neighbours.insert(child);
    }
}

struct ClickLinesGameData
{
    /// Последний успешно проделанный путь между тайлами.
    QList<ColorLinesTile *> path;

    /// Набранные очки.
    int coins;
    ColorLinesTileMap tileMap;
    QString statistics;
    ClickLinesGameData();
private:
    explicit ClickLinesGameData(ClickLinesGameData&);
    ClickLinesGameData &operator =(const ClickLinesGameData&);
};


ClickLinesGameData::ClickLinesGameData()
    : coins(0),
      tileMap(PLOT_COL_CNT, PLOT_ROW_CNT)
{
    srand(time(0));
    statistics = QString("Coins=%1").arg(coins);
    ColorLinesTile *left = tileMap.topLeft;
    ColorLinesTile *tile = tileMap.topLeft;
    while(tile != 0){
        int color = rand() % COLOR_CNT;
        tileMap.set(tile, ColorLinesTile::Color(color));
        if(tile->getRightTile() != 0){
            tile = tile->getRightTile();
        }else{
            left = left->getBottomTile();
            tile = left;
        }
    }
}

ClickLinesGame::ClickLinesGame(QObject *parent)
    : AbstractColorLinesGame(parent),
      data(new ClickLinesGameData)
{
}

void ClickLinesGame::dropDown()
{
    bool redrop = true;
    while(redrop){
        redrop = false;
	for (ColorLinesTile * freeTile: data->tileMap.freeList) {
            ColorLinesTile *tile = freeTile->getTopTile();
            QList<ColorLinesTile *> upperBlocks;
            while (tile != 0) {
                if(tile->getColor() != ColorLinesTile::NONE){
                    upperBlocks.push_back(tile);
                }
                tile = tile->getTopTile();
            }
            ColorLinesTile *dropToTile = freeTile;
	    for (ColorLinesTile *block: upperBlocks) {
                data->tileMap.set(dropToTile, block->getColor());
                data->tileMap.free(block);
                dropToTile = dropToTile->getTopTile();
            }
            if(!upperBlocks.isEmpty()){
                redrop = true;
                break;
            }
        }
    }
}

void ClickLinesGame::moveLeft()
{
    ColorLinesTile *freeTile = 0;
    ColorLinesTile *tile = data->tileMap.topLeft->getTile(0, PLOT_ROW_CNT - 1);
    while(tile){
        if(tile->getColor() == ColorLinesTile::NONE){
            freeTile = tile;
            break;
        }
        tile = tile->getRightTile();
    }
    if(freeTile != 0){
        ColorLinesTile *left = freeTile;
        ColorLinesTile *movingFront = 0;
        ColorLinesTile *frontCandidate = left->getRightTile();
        while((frontCandidate != 0) && (movingFront == 0)){
            if(frontCandidate->getColor() != ColorLinesTile::NONE){
                movingFront = frontCandidate;
                break;
            }
            frontCandidate = frontCandidate->getRightTile();
        }
        if(movingFront){
            while(left != 0){
                ColorLinesTile *tile = movingFront;
                QList<ColorLinesTile *> rightBlocks;
                while (tile != 0) {
                    if(tile->getColor() != ColorLinesTile::NONE){
                        rightBlocks.push_back(tile);
                    }
                    tile = tile->getRightTile();
                }
                ColorLinesTile *moveToTile = left;
		for (ColorLinesTile *block: rightBlocks) {
                    data->tileMap.set(moveToTile, block->getColor());
                    data->tileMap.free(block);
                    moveToTile = moveToTile->getRightTile();
                }
                left = left->getTopTile();
                movingFront = movingFront->getTopTile();
            }
        }
    }
}

void ClickLinesGame::lose()
{
    ChampionsTable t("Ilya Yunkin", "ClickLines");
    t.setResult(data->coins);
    QMessageBox::StandardButton b =
            QMessageBox::question(0, tr("Game over!"),
                                  tr("Do you want to replay?"));
    if(b == QMessageBox::Yes){
        data = QSharedPointer<ClickLinesGameData>(new ClickLinesGameData);
    }else{
        emit quitToMenu();
    }
}

int ClickLinesGame::getRowCount() const
{
    return PLOT_ROW_CNT;
}

int ClickLinesGame::getColCount() const
{
    return PLOT_ROW_CNT;
}

int ClickLinesGame::getCoins() const
{
    return data->coins;
}

const QString &ClickLinesGame::getStatistics() const
{
    return data->statistics;
}

ColorLinesTile *ClickLinesGame::getRootTile() const
{
    return data->tileMap.topLeft;
}

ColorLinesTile *ClickLinesGame::getSelectedTile() const
{
    return 0;
}

QList<ColorLinesTile *> const&ClickLinesGame::getPath() const
{
    return data->path;
}

void ClickLinesGame::tileClicked(int col, int row)
{
    ColorLinesTile *tile = data->tileMap.topLeft->getTile(col, row);
    if(tile->getColor() != ColorLinesTile::NONE){
        QSet<ColorLinesTile *> neighbours =
                NeighboursFinder(tile).findNeighbours();
        if(neighbours.size() > 1){
	    for (ColorLinesTile *tile: neighbours) {
                data->tileMap.free(tile);
            }
            data->coins += neighbours.size() * neighbours.size();
            dropDown();
            moveLeft();

            bool existChain = false;
	    for (ColorLinesTile *tile: data->tileMap.ownedList) {
                if(NeighboursFinder(tile).findNeighbours().size() > 1){
                    existChain = true;
                    break;
                }
            }
            data->statistics = QString("Coins=%1").arg(data->coins);
            if(!existChain){
                lose();
                return;
            }
        }
    }
}
