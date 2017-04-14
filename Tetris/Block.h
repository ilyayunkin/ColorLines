#ifndef BLOCK_H
#define BLOCK_H

#include <QList>
#include "Lines/ColorLinesTileMap.h"

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

    /// Создает новую падающую фигуру.
    static Block *createBlock(ColorLinesTile *topLeft);
private:
    Block();
    int matrixSide;
};

#endif // BLOCK_H
