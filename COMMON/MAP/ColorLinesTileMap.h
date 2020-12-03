/** @file
  * @author Yunkin Ilya.
  */
#ifndef COLORLINESTILEMAPBUILDER_H
#define COLORLINESTILEMAPBUILDER_H

#include "ColorLinesTile.h"
#include <vector>

/// Класс карты игрового поля
struct ColorLinesTileMap
{
    /// Корневой узел карты тайлов.
    ColorLinesTile *topLeft;
    /// Список свободных тайлов.
    std::vector<ColorLinesTile *> freeList;
    /// Список тайлов с фишками.
    std::vector<ColorLinesTile *> ownedList;
    /// Установить фишку на квадрат игрового поля.
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
    /// Запрещен конструктор по умолчанию
    ColorLinesTileMap();
    /// Запрещен конструктор копирования
    explicit ColorLinesTileMap(ColorLinesTileMap&);
    /// Запрещен оператор присваивания
    ColorLinesTileMap& operator=(const ColorLinesTileMap& f);
    /// Освобождает память со всех тайлов ниже и вправо.
    void deleteBottomTiles(ColorLinesTile *tile);
    /// Освобождает память для всех тайлов справа.
    void deleteRightTiles(ColorLinesTile *tile);
};

#endif // COLORLINESTILEMAPBUILDER_H
