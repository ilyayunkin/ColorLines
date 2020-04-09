#ifndef BLOCK_H
#define BLOCK_H

#include <array>
#include <vector>
#include <algorithm>

#include "COMMON/MAP/ColorLinesTileMap.h"


struct Matrix
{
    enum
    {
        BLOCK_WIDTH_MAX = 4
    };
    typedef std::array<std::array<bool, BLOCK_WIDTH_MAX>, BLOCK_WIDTH_MAX> MatrixField;

    static constexpr int side(const MatrixField&m)
    {
        int longestRow = 0;
        for (int i = 0; i < BLOCK_WIDTH_MAX; ++i)
        {
            for (int j = 0; j < BLOCK_WIDTH_MAX; ++j)
            {
                if(m[i][j])
                {
                    longestRow = std::max(j + 1, longestRow);
                    longestRow = std::max(i + 1, longestRow);
                }

            }
        }
        return longestRow;
    }
    MatrixField m;
    const int matrixSide;
    constexpr Matrix(const int matrixSide) : m{{{0}}}, matrixSide(matrixSide)
    {};
    constexpr Matrix(const Matrix &other) : m(other.m), matrixSide(other.matrixSide)
    {}
    constexpr Matrix(const MatrixField &m) : m(m), matrixSide(side(m))
    {}
    void operator=(const Matrix &other)
    {
        m = other.m;
    }
    Matrix getLeftTurned();
    Matrix getRightTurned();
};

class Block final
{
    Matrix matrix;
    int col;
    int row;
    ColorLinesTile *topLeft;
    std::vector<ColorLinesTile *> body;
    std::vector<ColorLinesTile *> getBody(const Matrix &m) const;
    void updateBody();
    Block() = delete;
    bool lefted() const;
    bool righted() const;
    bool isVisible(int col, int row) const;
    int getPlotRow(int row) const;
    int getPlotCol(int col) const;
public:
    void rotate();
    void down();
    void left();
    void right();
    bool landed() const;

    Block(ColorLinesTile *topLeft, const Matrix &matrix);

    /// Создает новую падающую фигуру.
    static Block *createBlock(ColorLinesTile *topLeft);
    std::vector<ColorLinesTile *> getBody() const {return body;}
};

#endif // BLOCK_H
