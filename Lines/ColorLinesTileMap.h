/** @file
  * @author Yunkin Ilya.
  */
#ifndef COLORLINESTILEMAPBUILDER_H
#define COLORLINESTILEMAPBUILDER_H

#include "ColorLinesTile.h"

struct ColorLinesTileMap
{
    /// Корневой узел карты тайлов.
    ColorLinesTile *topLeft;
    /// Список свободных тайлов.
    QList<ColorLinesTile *> freeList;
    /// Список тайлов с фишками.
    QList<ColorLinesTile *> ownedList;
    void set(ColorLinesTile *tile, ColorLinesTile::Color color);
    void free(ColorLinesTile *tile);
    void clear();

    ColorLinesTileMap(int colCount, int rowCount);
    ~ColorLinesTileMap();
    int getRowCount();
    int getColCount();
private:
    int colCount;
    int rowCount;
    ColorLinesTileMap();
    explicit ColorLinesTileMap(ColorLinesTileMap&);
    ColorLinesTileMap& operator=(const ColorLinesTileMap& f);
    void deleteBottomTiles(ColorLinesTile *tile);
    void deleteRightTiles(ColorLinesTile *tile);
};

#endif // COLORLINESTILEMAPBUILDER_H
