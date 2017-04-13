/** @file
  * @author Yunkin Ilya.
  */
#include "ColorLinesTile.h"

#include <assert.h>

#include "COMMON/MISC/sign.h"

ColorLinesTile::ColorLinesTile(Color color) :
    left(0),
    right(0),
    top(0),
    bottom(0),
    color(color)
{
}

ColorLinesTile *ColorLinesTile::getLeftTile() const
{
    return left;
}

ColorLinesTile *ColorLinesTile::getLeftTile(int index) const
{
    const ColorLinesTile *tile = this;
    for (int i = 0; i != index; i += SIGN(index)){
        tile = tile->left;
    }
    return const_cast<ColorLinesTile *>(tile);
}

ColorLinesTile *ColorLinesTile::getRightTile() const
{
    return right;
}

ColorLinesTile *ColorLinesTile::getRightTile(int index) const
{
    const ColorLinesTile *tile = this;
    for (int i = 0; i != index; i += SIGN(index)){
        tile = tile->right;
    }
    return const_cast<ColorLinesTile *>(tile);
}

ColorLinesTile *ColorLinesTile::getTopTile() const
{
    return top;
}

ColorLinesTile *ColorLinesTile::getTopTile(int index) const
{
    const ColorLinesTile *tile = this;
    for (int i = 0; i != index; i += SIGN(index)){
        tile = tile->top;
    }
    return const_cast<ColorLinesTile *>(tile);
}

ColorLinesTile *ColorLinesTile::getBottomTile() const
{
    return bottom;
}

ColorLinesTile *ColorLinesTile::getBottomTile(int index) const
{
    const ColorLinesTile *tile = this;
    for (int i = 0; i != index; i += SIGN(index)){
        tile = tile->bottom;
    }
    return const_cast<ColorLinesTile *>(tile);
}

void ColorLinesTile::setLeftTile(ColorLinesTile *tile)
{
    left = tile;
    tile->right = this;
}

void ColorLinesTile::setRightTile(ColorLinesTile *tile)
{
    right = tile;
    tile->left = this;
}

void ColorLinesTile::setTopTile(ColorLinesTile *tile)
{
    top =tile;
    tile->bottom = this;
}

void ColorLinesTile::setBottomTile(ColorLinesTile *tile)
{
    bottom = tile;
    tile->top = this;
}

ColorLinesTile *ColorLinesTile::getTile(int col, int row) const
{
    return getRightTile(col)->getBottomTile(row);
}

QPoint ColorLinesTile::getTileCoordinate(const ColorLinesTile *tile) const
{
    QPoint ret;
    int row = 0;
    const ColorLinesTile *left = this;
    while(left){
        int col = 0;
        const ColorLinesTile *current = left;
        while(current){
            if(current == tile){
                return QPoint(col, row);
            }
            col++;
            current = current->right;
        }
        left = left->bottom;
        row++;
    }
    return ret;
}


ColorLinesTile::Color ColorLinesTile::getColor() const
{
    return color;
}

QColor ColorLinesTile::getQColor() const
{
    QColor c;
    switch (color) {
    case RED:
        c = QColor(Qt::red);
        break;
    case GREEN:
        c = QColor(Qt::green);
        break;
    case BLUE:
        c = QColor(Qt::blue);
        break;
    case BLACK:
        c = QColor(Qt::black);
        break;
    case YELLOW:
        c = QColor(Qt::yellow);
        break;
    case MAGENTA:
        c = QColor(Qt::magenta);
        break;
    case CYAN:
        c = QColor(Qt::cyan);
        break;
    case COUNT:
    default:
        assert(false);
        break;
    }
    return c;
}

void ColorLinesTile::setColor(Color color)
{
    this->color = color;
}

QList<ColorLinesTile *> ColorLinesTile::getTileList() const
{
    QList<ColorLinesTile *> list;
    const ColorLinesTile *left = this;
    while(left){
        const ColorLinesTile *current = left;
        while(current){
            list.push_back(const_cast<ColorLinesTile *>(current));
            current = current->right;
        }
        left = left->bottom;
    }
    return list;
}

QList<ColorLinesTile *> ColorLinesTile::getHorizontalColorList() const
{
    QList<ColorLinesTile *> list;
    list.push_back(const_cast<ColorLinesTile *>(this));
    ColorLinesTile *cur = right;
    while((cur != 0) && (cur->getColor() == color)){
        list.push_back(cur);
        cur = cur->right;
    }
    cur = left;
    while((cur != 0) && (cur->getColor() == color)){
        list.push_back(cur);
        cur = cur->left;
    }
    return list;
}

QList<ColorLinesTile *> ColorLinesTile::getVerticalColorList() const
{
    QList<ColorLinesTile *> list;
    list.push_back(const_cast<ColorLinesTile *>(this));
    ColorLinesTile *cur = getTopTile();
    while((cur != 0) && (cur->getColor() == getColor())){
        list.push_back(cur);
        cur = cur->getTopTile();
    }
    cur = getBottomTile();
    while((cur != 0) && (cur->getColor() == getColor())){
        list.push_back(cur);
        cur = cur->getBottomTile();
    }
    return list;
}

QList<ColorLinesTile *> ColorLinesTile::getDiagonal1ColorList() const
{
    QList<ColorLinesTile *> list;
    list.push_back(const_cast<ColorLinesTile *>(this));
    ColorLinesTile *cur = (left != 0) ? left->top : 0;
    while((cur != 0) && (cur->getColor() == getColor())){
        list.push_back(cur);
        cur = (cur->left != 0) ? cur->left->top : 0;
    }
    cur = (right != 0) ? right->bottom : 0;
    while((cur != 0) && (cur->getColor() == getColor())){
        list.push_back(cur);
        cur = (cur->right != 0) ? cur->right->bottom : 0;
    }
    return list;
}

QList<ColorLinesTile *> ColorLinesTile::getDiagonal2ColorList() const
{
    QList<ColorLinesTile *> list;
    list.push_back(const_cast<ColorLinesTile *>(this));
    ColorLinesTile *cur = (left != 0) ? left->bottom : 0;
    while((cur != 0) && (cur->getColor() == getColor())){
        list.push_back(cur);
        cur = (cur->left != 0) ? cur->left->bottom : 0;
    }
    cur = (right != 0) ? right->top : 0;
    while((cur != 0) && (cur->getColor() == getColor())){
        list.push_back(cur);
        cur = (cur->right != 0) ? cur->right->top : 0;
    }
    return list;
}
