#include "Block.h"

#include <random>
#include <assert.h>
#include <time.h>

#include <QDebug>

#include "TetrisCommon.h"

namespace
{
constexpr Block::Matrix lineMatrix({
                                       std::array<bool, 4>{false, false, false, true},
                                       std::array<bool, 4>{false, false, false, true},
                                       std::array<bool, 4>{false, false, false, true},
                                       std::array<bool, 4>{false, false, false, true}
                                   }, 4);
constexpr Block::Matrix crossMatrix({
                                        std::array<bool, 4>{false, true, false, false},
                                        std::array<bool, 4>{true, true, true, false},
                                        std::array<bool, 4>{false, true, false, false},
                                        std::array<bool, 4>{false, false, false, false}
                                    }, 3);
constexpr Block::Matrix lbMatrix({
                                     std::array<bool, 4>{true, true, false, false},
                                     std::array<bool, 4>{false, true, false, false},
                                     std::array<bool, 4>{false, true, false, false},
                                     std::array<bool, 4>{false, false, false, false}
                                 }, 3);
constexpr Block::Matrix lb2Matrix({
                                      std::array<bool, 4>{true, true, false, false},
                                      std::array<bool, 4>{true, false, false, false},
                                      std::array<bool, 4>{true, false, false, false},
                                      std::array<bool, 4>{false, false, false, false}
                                  }, 3);
constexpr Block::Matrix rectMatrix({
                                       std::array<bool, 4>{false, true, true, false},
                                       std::array<bool, 4>{false, true, true, false},
                                       std::array<bool, 4>{false, false, false, false},
                                       std::array<bool, 4>{false, false, false, false}
                                   }, 4);
constexpr Block::Matrix zetaMatrix({
                                       std::array<bool, 4>{true, true, false, false},
                                       std::array<bool, 4>{false, true, true, false},
                                       std::array<bool, 4>{false, false, false, false},
                                       std::array<bool, 4>{false, false, false, false}
                                   }, 3);
constexpr Block::Matrix zeta2Matrix({
                                        std::array<bool, 4>{false, true, true, false},
                                        std::array<bool, 4>{true, true, false, false},
                                        std::array<bool, 4>{false, false, false, false},
                                        std::array<bool, 4>{false, false, false, false}
                                    }, 3);

enum
{
    LINE,
    CROSS,
    L_BLOCK,
    RECT,
    ZETA,
    ZETA2,
    L_BLOCK2,

    COUNT
};
std::default_random_engine randomEngine(time(NULL));
}


Block::Matrix Block::Matrix::getLeftTurned()
{
    Matrix newM(matrixSide);
    for(int i = 0; i < matrixSide; i++){
        for(int j = 0; j < matrixSide; j++){
            newM.m[i][j] = m[matrixSide - 1 - j][i];
        }
    }
    return newM;
}

Block::Matrix Block::Matrix::getRightTurned()
{
    Matrix newM(matrixSide);
    for(int i = 0; i < matrixSide; i++){
        for(int j = 0; j < matrixSide; j++){
            newM.m[i][j] = m[j][matrixSide - i - 1];
        }
    }
    return newM;
}

Block::Block(ColorLinesTile *topLeft, const Matrix &matrix)
    : matrix(matrix),
      color(blockColor),
      col(BLOCK_WIDTH_MAX / 2 - 1),
      row(-BLOCK_WIDTH_MAX),
      topLeft(topLeft)
{
}


Block *Block::createBlock(ColorLinesTile *topLeft)
{

    Block *block = 0;
    int type = randomEngine() % COUNT;
    switch (type) {
    case LINE:
        block = new Block(topLeft, lineMatrix);
        break;
    case CROSS:
        block = new Block(topLeft, crossMatrix);
        break;
    case L_BLOCK:
        block = new Block(topLeft, lbMatrix);
        break;
    case RECT:
        block = new Block(topLeft, rectMatrix);
        break;
    case ZETA:
        block = new Block(topLeft, zetaMatrix);
        break;
    case ZETA2:
        block = new Block(topLeft, zeta2Matrix);
        break;
    case L_BLOCK2:
        block = new Block(topLeft, lb2Matrix);
        break;
    default:
        assert(false);
        break;
    }
    return block;
}

void Block::down()
{
    if(!landed()){
        row++;
        updateBody();
    }
}

void Block::right()
{
    if(!righted()){
        col++;
        updateBody();
    }
}

void Block::left()
{
    if(!lefted()){
        col--;
        updateBody();
    }
}

void Block::printShape(const Matrix &m) const
{
    for(int i = 0; i < BLOCK_WIDTH_MAX; i++){
        qDebug() << (m.m[0][i] ? 'x' : ' ')
                << (m.m[1][i] ? 'x' : ' ')
                << (m.m[2][i] ? 'x' : ' ')
                << (m.m[3][i] ? 'x' : ' ');
    }
    qDebug() << "";
}

void Block::rotate()
{
    Matrix newMatrix = matrix.getLeftTurned();
    printShape(matrix);
    printShape(newMatrix);

    bool ok = true;
    for(int i = 0; i < matrix.matrixSide; i++){
        for(int j = 0; j < matrix.matrixSide; j++){
            int plotRow = getPlotRow(j);
            int plotCol = getPlotCol(i);
            bool visibleOrUpper = (plotRow < PLOT_ROW_CNT) &&
                    (plotCol >= 0) && (plotCol < PLOT_COL_CNT);
            if((newMatrix.m[i][j]) && (!visibleOrUpper)){
                ok = false;
                break;
            }else if((newMatrix.m[i][j]) && isVisible(i, j)){
                ColorLinesTile *tile = topLeft->getTile(plotCol, plotRow);
                if(tile->getColor() == buildingColor){
                    ok = false;
                    break;
                }
            }
        }
    }
    if(ok){
        matrix = newMatrix;
        updateBody();
    }
}

bool Block::landed() const
{
    bool ret = false;

    if(row > PLOT_ROW_CNT - 1){
        ret = true;
    }else{
        foreach (ColorLinesTile *tile, body){
            ColorLinesTile *bottom = tile->getBottomTile();
            if((bottom == 0) ||
                    ((bottom->getColor() != ColorLinesTile::NONE) &&
                     (!body.contains(bottom)))){
                ret = true;
                break;
            }
        }
    }

    return ret;
}

bool Block::lefted() const
{
    bool ret = false;
    foreach (ColorLinesTile *tile, body){
        ColorLinesTile *left = tile->getLeftTile();
        if((left == 0) || (left->getColor() == buildingColor)){
            ret = true;
            break;
        }
    }

    for(int mcol = 0; mcol < matrix.matrixSide; ++mcol){
        for(int mrow = 0; mrow < matrix.matrixSide; ++mrow){
            if(matrix.m[mcol][mrow] && (col + mcol <= 0)){
                ret = true;
                break;
            }
        }
    }

    return ret;
}

bool Block::righted() const
{
    bool ret = false;
    foreach (ColorLinesTile *tile, body){
        ColorLinesTile *right = tile->getRightTile();
        if((right == 0) || (right->getColor() == buildingColor)){
            ret = true;
            break;
        }
    }

    for(int mcol = 0; mcol < matrix.matrixSide; ++mcol){
        for(int mrow = 0; mrow < matrix.matrixSide; ++mrow){
            if(matrix.m[mcol][mrow] && (col + mcol >= (PLOT_COL_CNT - 1))){
                ret = true;
                break;
            }
        }
    }

    return ret;
}

bool Block::isVisible(int col, int row) const
{
    int plotRow = getPlotRow(row);
    int plotCol = getPlotCol(col);
    return (plotRow >= 0) && (plotRow < PLOT_ROW_CNT) &&
            (plotCol >= 0) && (plotCol < PLOT_COL_CNT);
}

int Block::getPlotRow(int row) const
{
    return row + this->row;
}

int Block::getPlotCol(int col) const
{
    return col + this->col;
}

QList<ColorLinesTile *> Block::getBody(const Matrix &m) const
{
    QList<ColorLinesTile *> body;
    for(int j = 0; j < BLOCK_WIDTH_MAX; j++){
        for(int i = 0; i < BLOCK_WIDTH_MAX; i++){
            if(isVisible(i, j)){
                if(m.m[i][j]){
                    body.push_back(topLeft->getTile(i + col, getPlotRow(j)));
                }
            }
        }
    }
    return body;
}

void Block::updateBody()
{
    foreach (ColorLinesTile *tile, body){
        tile->setColor(ColorLinesTile::NONE);
    }
    QList<ColorLinesTile *> newBody = getBody(matrix);
    foreach (ColorLinesTile *tile, newBody){
        tile->setColor(color);
    }
    body = newBody;
}
