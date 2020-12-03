/** @file
  * @author Yunkin Ilya.
  */
#include "GameData.h"

#include <time.h>

#include "COMMON/PathSearchToWidth.h"

ColorLinesGameData::ColorLinesGameData(JustAnotherLines *game)
    : lose(false),
      randomEngine(time(NULL)),
      combo(1),
      coins(0),
      tileMap(DIMENSION, DIMENSION),
      selection(0),
      elementMovingStatePointer(new ElementMovingState(this)),
      waitingStatePointer(new WaitingState(this)),
      currentState(waitingStatePointer.get()),
      game(game)
{
    statistics = QString("Coins=%1 Combo=%2").arg(coins).arg(combo);
    randomColors();
}

bool ColorLinesGameData::clearIfLined(ColorLinesTile *tile)
{
    std::vector<ColorLinesTile *> hList = tile->getHorizontalColorList();
    std::vector<ColorLinesTile *> vList = tile->getVerticalColorList();
    std::vector<ColorLinesTile *> d1List = tile->getDiagonal1ColorList();
    std::vector<ColorLinesTile *> d2List = tile->getDiagonal2ColorList();
    int cash = clearIfLined(hList) +
            clearIfLined(vList) +
            clearIfLined(d1List) +
            clearIfLined(d2List);
    if(cash > 0){
        coins+= cash;
        combo++;
    }else{
        combo = 1;
    }

    return cash > 0;
}

int ColorLinesGameData::clearIfLined(std::vector<ColorLinesTile *> line)
{
    int cash = 0;
    if(line.size() >= MIN_LINE){
        cash+= combo * line.size();
	for (ColorLinesTile *t: line) {
            tileMap.free(t);
        }
    }
    return cash;
}

bool ColorLinesGameData::buildPath(ColorLinesTile *from, ColorLinesTile *to)
{
    PathSearchToWidth search;
    bool ret = search.search(from, to, path);
    return ret;
}

void ColorLinesGameData::placeBalls()
{
    int freeCells = tileMap.freeList.size();
    int ballsWeCanPlace = std::min(freeCells, (int)BALLS_IN_STEP);
    if(ballsWeCanPlace == 0){
        lose = true;
    }else{
        for(int i = 0; i < ballsWeCanPlace; i++){
            int cell = randomEngine() % freeCells;
            ColorLinesTile *randomTile = tileMap.freeList[cell];
            tileMap.set(randomTile, nextColors.color[i]);
            clearIfLined(randomTile);
            --freeCells;
        }
        if(tileMap.ownedList.empty()){// Чтобы с пустым полем не остаться
            placeBalls();
        }
        randomColors();
    }

    if(tileMap.freeList.empty()){
        lose = true;
    }
}

void ColorLinesGameData::randomColors()
{
    for(int i = 0; i < BALLS_IN_STEP; i++){
        int randomColor = randomEngine() % ColorLinesTile::COUNT;
        nextColors.color[i] = (ColorLinesTile::Color) randomColor;
    }
}


void ColorLinesGameData::goToElementMovingState()
{
    currentState = elementMovingStatePointer.get();
}

void ColorLinesGameData::goToWaitingState()
{
    currentState = waitingStatePointer.get();
}

void ColorLinesGameData::pathClean()
{
    path.clear();
}

ElementMovingState::ElementMovingState(ColorLinesGameData *data) :
    data(data)
{
}

void ElementMovingState::update()
{
    if((data->pathIterator + 1) != data->path.end()){
        ColorLinesTile *tile = *data->pathIterator;
        ColorLinesTile::Color color = tile->getColor();
        data->tileMap.free(tile);
        ++data->pathIterator;
        data->tileMap.set(*data->pathIterator, color);
    }else{
        data->goToWaitingState();
        ColorLinesTile *tile = data->path.back();
        data->pathClean();
        if(!data->clearIfLined(tile)){
            data->placeBalls();
        }else if(data->tileMap.ownedList.empty()){// Чтобы с пустым полем не остаться
            data->placeBalls();
        }
        data->selection = 0;
        data->statistics = QString("Coins=%1 Combo=%2").arg(data->coins).arg(data->combo);
    }
}

void ElementMovingState::tileClicked(int col, int row)
{
    Q_UNUSED(col);
    Q_UNUSED(row);
}

WaitingState::WaitingState(ColorLinesGameData *data) :
    data(data)
{
}

void WaitingState::update()
{

}

void WaitingState::tileClicked(int col, int row)
{
    ColorLinesTile *tile = data->tileMap.topLeft->getTile(col, row);
    if(data->selection == 0){
        if(tile->getColor() != ColorLinesTile::NONE){
            data->selection = tile;
        }
    }else{
        if(tile->getColor() != ColorLinesTile::NONE){
            data->selection = tile;
        }else{
            if(data->buildPath(data->selection, tile)){
                data->goToElementMovingState();
                data->pathIterator = data->path.begin();
            }
        }
    }

}

bool ColorLinesGameData::isLose()
{
    return lose;
}
