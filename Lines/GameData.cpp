#include "GameData.h"
#include "PathSearchToWidth.h"

GameData::GameData(JustAnotherLines *game)
    : combo(1),
      coins(0),
      tileMap(DIMENSION, DIMENSION),
      selection(0),
      elementMovingStatePointer(new ElementMovingState(this)),
      waitingStatePointer(new WaitingState(this)),
      currentState(waitingStatePointer.data()),
      game(game)
{
    statistics = QString("Coins=%1 Combo=%2").arg(coins).arg(combo);
    randomColors();
}

bool GameData::clearIfLined(ColorLinesTile *tile)
{
    QList<ColorLinesTile *> hList = tile->getHorizontalColorList();
    QList<ColorLinesTile *> vList = tile->getVerticalColorList();
    QList<ColorLinesTile *> d1List = tile->getDiagonal1ColorList();
    QList<ColorLinesTile *> d2List = tile->getDiagonal2ColorList();
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

int GameData::clearIfLined(QList<ColorLinesTile *> line)
{
    int cash = 0;
    if(line.size() >= MIN_LINE){
        cash+= combo * line.size();
        foreach (ColorLinesTile *t, line) {
            tileMap.free(t);
        }
    }
    return cash;
}

bool GameData::buildPath(ColorLinesTile *from, ColorLinesTile *to)
{
    PathSearchToWidth search;
    bool ret = search.search(from, to, path);
    return ret;
}

void GameData::placeBalls()
{
    int freeCells = tileMap.freeList.size();
    int ballsWeCanPlace = std::min(freeCells, (int)BALLS_IN_STEP);
    if(ballsWeCanPlace == 0){
        game->lose();
    }else{
        for(int i = 0; i < ballsWeCanPlace; i++){
            int cell = rand() % freeCells;
            ColorLinesTile *randomTile = tileMap.freeList[cell];
            tileMap.set(randomTile, nextColors.color[i]);
            clearIfLined(randomTile);
            --freeCells;
        }
        if(tileMap.ownedList.isEmpty()){// Чтобы с пустым полем не остаться
            placeBalls();
        }
        randomColors();
    }
    freeCells = tileMap.freeList.size();

    if(tileMap.freeList.size() == 0){
        game->lose();
    }
}

void GameData::randomColors()
{
    for(int i = 0; i < BALLS_IN_STEP; i++){
        int randomColor = rand() % ColorLinesTile::COUNT;
        nextColors.color[i] = (ColorLinesTile::Color) randomColor;
    }
}


void GameData::goToElementMovingState()
{
    currentState = elementMovingStatePointer.data();
}

void GameData::goToWaitingState()
{
    currentState = waitingStatePointer.data();
}

void GameData::pathClean()
{
    path.clear();
}

ElementMovingState::ElementMovingState(GameData *data) :
    data(data)
{
}

void ElementMovingState::update()
{
    if((data->pathIterator + 1) != data->path.end()){
        ColorLinesTile *tile = *data->pathIterator;
        ColorLinesTile::Color color = tile->getColor();
        data->tileMap.free(tile);
        data->pathIterator++;
        data->tileMap.set(*data->pathIterator, color);
    }else{
        data->goToWaitingState();
        ColorLinesTile *tile = data->path.last();
        data->pathClean();
        if(!data->clearIfLined(tile)){
            data->placeBalls();
        }else if(data->tileMap.ownedList.isEmpty()){// Чтобы с пустым полем не остаться
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

WaitingState::WaitingState(GameData *data) :
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
