#ifndef BLOCK_H
#define BLOCK_H

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

    Matrix matrix;
    ColorLinesTile::Color color;
    int col;
    int row;
    ColorLinesTile *topLeft;
    QList<ColorLinesTile *> body;
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
    QList<ColorLinesTile *> getBody(const Matrix &m) const;
    void updateBody();

    Block(ColorLinesTile *topLeft, const Matrix &matrix);

    /// Создает новую падающую фигуру.
    static Block *createBlock(ColorLinesTile *topLeft);
private:
    Block() = delete;
};

#endif // BLOCK_H
