#ifndef BLOCK_H
#define BLOCK_H

#include <array>
#include <vector>

#include "COMMON/MAP/ColorLinesTileMap.h"

struct Matrix
{
    enum
    {
        BLOCK_WIDTH_MAX = 4
    };
    typedef std::array<std::array<bool, BLOCK_WIDTH_MAX>, BLOCK_WIDTH_MAX> MatrixField;
    MatrixField m;
    const int matrixSide;

    constexpr Matrix(const int matrixSide) : m{{{0}}}, matrixSide(matrixSide)
    {};
    constexpr Matrix(const Matrix &other) : m(other.m), matrixSide(other.matrixSide)
    {
    }
    constexpr Matrix(const MatrixField &m, int matrixSide) : m(m), matrixSide(matrixSide)
    {
    }
    void operator=(const Matrix &other)
    {
        m = other.m;
    }
    Matrix getLeftTurned();
    Matrix getRightTurned();
};

struct Block final
{


    Matrix matrix;
    ColorLinesTile::Color color;
    int col;
    int row;
    ColorLinesTile *topLeft;
    std::vector<ColorLinesTile *> body;
    void rotate();
    void printShape(const Matrix &m) const;
    void down();
    void left();
    void right();
    bool landed() const;
    bool lefted() const;
    bool righted() const;
    bool isVisible(int col, int row) const;
    int getPlotRow(int row) const;
    int getPlotCol(int col) const;
    std::vector<ColorLinesTile *> getBody(const Matrix &m) const;
    void updateBody();

    Block(ColorLinesTile *topLeft, const Matrix &matrix);

    /// Создает новую падающую фигуру.
    static Block *createBlock(ColorLinesTile *topLeft);
private:
    Block() = delete;
};

#endif // BLOCK_H
