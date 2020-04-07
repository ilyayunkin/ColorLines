#ifndef BLOCK_H
#define BLOCK_H

#include <random>
#include <array>

#include <QList>

#include "COMMON/MAP/ColorLinesTileMap.h"

struct Block final
{
    enum
    {
        BLOCK_WIDTH_MAX = 4
    };

    struct Matrix
    {
        typedef std::array<std::array<bool, BLOCK_WIDTH_MAX>, BLOCK_WIDTH_MAX> MatrixField;
        MatrixField m;
        const int matrixSide;

        Matrix(const int matrixSide) : m{{{0}}}, matrixSide(matrixSide)
        {};
        Matrix(const Matrix &other) : m(other.m), matrixSide(other.matrixSide)
        {
        }
        Matrix(const MatrixField &m, int matrixSide) : m(m), matrixSide(matrixSide)
        {
        }
        void operator=(const Matrix &other)
        {
            m = other.m;
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

    Block(ColorLinesTile *topLeft, const Matrix &matrix);

    /// Создает новую падающую фигуру.
    static Block *createBlock(ColorLinesTile *topLeft);
private:
    Block() = delete;
};

#endif // BLOCK_H
