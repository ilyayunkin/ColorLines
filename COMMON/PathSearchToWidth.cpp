/** @file
  * @author Yunkin Ilya.
  */
#include "PathSearchToWidth.h"
#include "MISC/container_convenience.h"

bool PathSearchToWidth::search(ColorLinesTile *from, ColorLinesTile *to, std::vector<ColorLinesTile *> &path)
{
    bool ret = false;
    tileParentMap.insert(from, 0);
    openQueue.enqueue(from);
    while(!openQueue.empty()){
        ColorLinesTile *current = openQueue.takeFirst();
        if(current == to){
            /// Конструирование пути
            path.clear();
            ColorLinesTile *pathTile = current;
            while(pathTile != from){
                path.push_back(pathTile);
                pathTile = tileParentMap[pathTile];
            }
            path.push_back(from);
            ret = true;
            std::reverse(path.begin(), path.end());
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

    if(childExists && isFree(child) && notEnqued(child)){
        openQueue.enqueue(child);
        tileParentMap.insert(child,parent);
    }
}

bool PathSearchToWidth::isFree(ColorLinesTile *tile)
{
    return tile->getColor() == ColorLinesTile::NONE;
}

bool PathSearchToWidth::notEnqued(ColorLinesTile *tile)
{
    return !Container::contains(tileParentMap, tile);
}
