#ifndef BLOCK_H
#define BLOCK_H

#include <random>

#include <QList>

#include "COMMON/MAP/ColorLinesTileMap.h"

struct Block
{
    enum
    {
        BLOCK_WIDTH_MAX = 4
    };

    struct Matrix
    {
        typedef bool MatrixField[BLOCK_WIDTH_MAX][BLOCK_WIDTH_MAX];
        MatrixField m;
        const int matrixSide;

        Matrix(const int matrixSide) : m{{0}}, matrixSide(matrixSide)
        {};
        void operator=(const Matrix &other)
        {
            memcpy(m, other.m, sizeof(m));
        }
        Matrix getLeftTurned();
        Matrix getRightTurned();
    };

    static std::default_random_engine randomEngine;
    Matrix matrix;
    ColorLinesTile::Color color;
    int col;
    int row;
    ColorLinesTile *topLeft;
    QList<ColorLinesTile *> body;
    void rotate();
    void printShape(Matrix m);
    void down();
    void left();
    void right();
    bool landed();
    bool lefted();
    bool righted();
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
    Block() = delete;
};

#endif // BLOCK_H
