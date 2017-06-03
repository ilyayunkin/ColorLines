/** @file
  * @author Yunkin Ilya.
  */
#include "PathSearchToWidth.h"


bool PathSearchToWidth::search(ColorLinesTile *from, ColorLinesTile *to, QList<ColorLinesTile *> &path)
{
    bool ret = false;
    tileParentMap.insert(from, 0);
    openQueue.enqueue(from);
    while(!openQueue.isEmpty()){
        ColorLinesTile *current = openQueue.takeFirst();
        if(current == to){
            /// Конструирование пути
            path.clear();
            ColorLinesTile *pathTile = current;
            while(pathTile != from){
                path.prepend(pathTile);
                pathTile = tileParentMap[pathTile];
            }
            path.prepend(from);
            ret = true;
            break;
        }else
        {
            enqueueChild(current->getLeftTile(), current);
            enqueueChild(current->getRightTile(), current);
            enqueueChild(current->getTopTile(), current);
            enqueueChild(current->getBottomTile(), current);
        }
    }
    return ret;
}

void PathSearchToWidth::enqueueChild(ColorLinesTile *child, ColorLinesTile *parent)
{
    bool childExists = (child != 0);

    if(childExists && isFree(child) && didntEnqued(child)){
        openQueue.enqueue(child);
        tileParentMap.insert(child,parent);
    }
}

bool PathSearchToWidth::isFree(ColorLinesTile *tile)
{
    return tile->getColor() == ColorLinesTile::NONE;
}

bool PathSearchToWidth::didntEnqued(ColorLinesTile *tile)
{
    return !tileParentMap.contains(tile);
}
