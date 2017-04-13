/** @file
  * @author Yunkin Ilya.
  */
#include "ColorLinesTileMap.h"

void ColorLinesTileMap::set(ColorLinesTile *tile, ColorLinesTile::Color color)
{
    tile->setColor(color);
    ownedList.push_back(tile);
    freeList.removeAll(tile);
}

void ColorLinesTileMap::free(ColorLinesTile *tile)
{
    ownedList.removeAll(tile);
    freeList.push_back(tile);
    tile->setColor(ColorLinesTile::NONE);
}

void ColorLinesTileMap::clear()
{
    QList<ColorLinesTile *> list = topLeft->getTileList();
    freeList = list;
    ownedList.clear();
    foreach (ColorLinesTile *t, list) {
        t->setColor(ColorLinesTile::NONE);
    }
}

ColorLinesTileMap::ColorLinesTileMap(int colCount, int rowCount) :
    topLeft(0),
    colCount(colCount),
    rowCount(rowCount)
{
    topLeft = 0;
    for(int row = 0; row < rowCount; row++){
        ColorLinesTile *leftTile = (row == 0) ? topLeft : 0;
        ColorLinesTile *currentTile = leftTile;
        for(int col = 0; col < colCount; col++){
            ColorLinesTile *newTile = new ColorLinesTile;

            if(topLeft == 0){
                topLeft = newTile;
            }
            if(currentTile != 0){
                currentTile->setRightTile(newTile);
            }
            if(row > 0){
                newTile->setTopTile(topLeft->getTile(col, row - 1));
            }
            currentTile = newTile;
        }
    }

    freeList = topLeft->getTileList();
}

ColorLinesTileMap::~ColorLinesTileMap()
{
    deleteBottomTiles(topLeft);
}

int ColorLinesTileMap::getRowCount()
{
    return rowCount;
}

int ColorLinesTileMap::getColCount()
{
    return colCount;
}

void ColorLinesTileMap::deleteBottomTiles(ColorLinesTile *tile)
{
    if(tile->getBottomTile())
    {
        deleteBottomTiles(tile->getBottomTile());
    }
    deleteRightTiles(tile);
}

void ColorLinesTileMap::deleteRightTiles(ColorLinesTile *tile)
{
    if(tile->getRightTile())
    {
        deleteRightTiles(tile->getRightTile());
    }
    delete tile;
}
