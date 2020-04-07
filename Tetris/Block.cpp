#include "Block.h"

#include <assert.h>
#include <time.h>

#include <QDebug>

#include "TetrisCommon.h"

namespace
{
struct Line : Block
{
    explicit Line(ColorLinesTile *topLeft) : Block(topLeft)
    {
        color = blockColor;
        for(int i = 0; i < BLOCK_WIDTH_MAX; i++){
            matrix.m[i][BLOCK_WIDTH_MAX - 1] = true;
        }
    }
};

struct Cross : Block
{
    explicit Cross(ColorLinesTile *topLeft) : Block(topLeft, 3)
    {
        color = blockColor;
        for(int i = 0; i < BLOCK_WIDTH_MAX; i++){
            for(int j = 0; j < BLOCK_WIDTH_MAX; j++){
                matrix.m[i][j] = false;
            }
        }
        matrix.m[0][0] = true;
        matrix.m[1][0] = true;
        matrix.m[2][0] = true;
        matrix.m[1][1] = true;
    }
};

struct LBlock : Block
{
    explicit LBlock(ColorLinesTile *topLeft) : Block(topLeft, 3)
    {
        color = blockColor;
        matrix.m[0][0] = true;
        matrix.m[0][1] = true;
        matrix.m[1][1] = true;
        matrix.m[2][1] = true;
    }
};

struct LBlock2 : Block
{
    explicit LBlock2(ColorLinesTile *topLeft) : Block(topLeft, 3)
    {
        color = blockColor;
        matrix.m[0][1] = true;
        matrix.m[0][0] = true;
        matrix.m[1][0] = true;
        matrix.m[2][0] = true;
    }
};

struct Rect : Block
{
    explicit Rect(ColorLinesTile *topLeft) : Block(topLeft)
    {
        color = blockColor;
        matrix.m[BLOCK_WIDTH_MAX/2][BLOCK_WIDTH_MAX/2] = true;
        matrix.m[BLOCK_WIDTH_MAX/2 - 1][BLOCK_WIDTH_MAX/2] = true;
        matrix.m[BLOCK_WIDTH_MAX/2][BLOCK_WIDTH_MAX/2 + 1] = true;
        matrix.m[BLOCK_WIDTH_MAX/2 - 1][BLOCK_WIDTH_MAX/2 + 1] = true;
    }
};

struct Zeta : Block
{
    explicit Zeta(ColorLinesTile *topLeft) : Block(topLeft, 3)
    {
        color = blockColor;
        matrix.m[0][0] = true;
        matrix.m[1][0] = true;
        matrix.m[1][1] = true;
        matrix.m[2][1] = true;
    }
};

struct Zeta2 : Block
{
    explicit Zeta2(ColorLinesTile *topLeft) : Block(topLeft, 3)
    {
        color = blockColor;
        matrix.m[0][1] = true;
        matrix.m[1][0] = true;
        matrix.m[2][0] = true;
        matrix.m[1][1] = true;
    }
};
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
}

Block::Block(ColorLinesTile *topLeft, int rectSide)
    : col(BLOCK_WIDTH_MAX / 2 - 1),
      row(-BLOCK_WIDTH_MAX),
      topLeft(topLeft),
      matrixSide(rectSide)
{
}

std::default_random_engine Block::randomEngine(time(NULL));

Block *Block::createBlock(ColorLinesTile *topLeft)
{

    Block *block = 0;
    int type = randomEngine() % COUNT;
    switch (type) {
    case LINE:
        block = new Line(topLeft);
        break;
    case CROSS:
        block = new Cross(topLeft);
        break;
    case L_BLOCK:
        block = new LBlock(topLeft);
        break;
    case RECT:
        block = new Rect(topLeft);
        break;
    case ZETA:
        block = new Zeta(topLeft);
        break;
    case ZETA2:
        block = new Zeta2(topLeft);
        break;
    case L_BLOCK2:
        block = new LBlock2(topLeft);
        break;
    default:
        assert(false);
        break;
    }
    return block;
}


Block::Matrix::Matrix()
{
    for(int i = 0; i < BLOCK_WIDTH_MAX; i++){
        for(int j = 0; j < BLOCK_WIDTH_MAX; j++){
            m[i][j] = false;
        }
    }
}

Block::Matrix Block::getLeftTurned()
{
    Matrix newM;
    for(int i = 0; i < matrixSide; i++){
        for(int j = 0; j < matrixSide; j++){
            newM.m[i][j] = matrix.m[matrixSide - 1 - j][i];
        }
    }
    return newM;
}

Block::Matrix Block::getRightTurned()
{
    Matrix newM;
    for(int i = 0; i < matrixSide; i++){
        for(int j = 0; j < matrixSide; j++){
            newM.m[i][j] = matrix.m[j][matrixSide - i - 1];
        }
    }
    return newM;
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

void Block::printShape(Matrix m)
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
    Matrix newMatrix = getLeftTurned();
    printShape(matrix);
    printShape(newMatrix);

    bool ok = true;
    for(int i = 0; i < matrixSide; i++){
        for(int j = 0; j < matrixSide; j++){
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

bool Block::landed()
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

bool Block::lefted()
{
    bool ret = false;
    foreach (ColorLinesTile *tile, body){
        ColorLinesTile *left = tile->getLeftTile();
        if((left == 0) || (left->getColor() == buildingColor)){
            ret = true;
            break;
        }
    }

    for(int mcol = 0; mcol < matrixSide; ++mcol){
        for(int mrow = 0; mrow < matrixSide; ++mrow){
            if(matrix.m[mcol][mrow] && (col + mcol <= 0)){
                ret = true;
                break;
            }
        }
    }

    return ret;
}

bool Block::righted()
{
    bool ret = false;
    foreach (ColorLinesTile *tile, body){
        ColorLinesTile *right = tile->getRightTile();
        if((right == 0) || (right->getColor() == buildingColor)){
            ret = true;
            break;
        }
    }

    for(int mcol = 0; mcol < matrixSide; ++mcol){
        for(int mrow = 0; mrow < matrixSide; ++mrow){
            if(matrix.m[mcol][mrow] && (col + mcol >= (PLOT_COL_CNT - 1))){
                ret = true;
                break;
            }
        }
    }

    return ret;
}

bool Block::isVisible(int col, int row)
{
    int plotRow = getPlotRow(row);
    int plotCol = getPlotCol(col);
    return (plotRow >= 0) && (plotRow < PLOT_ROW_CNT) &&
            (plotCol >= 0) && (plotCol < PLOT_COL_CNT);
}

int Block::getPlotRow(int row)
{
    return row + this->row;
}

int Block::getPlotCol(int col)
{
    return col + this->col;
}

QList<ColorLinesTile *> Block::getBody(Matrix m)
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
