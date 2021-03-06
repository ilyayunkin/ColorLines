/** @file
  * @author Yunkin Ilya.
  */
#include "SnakeGame.h"

#include <assert.h>
#include <time.h>
#include <random>

#include <QMessageBox>
#include <QTimer>
#include <QQueue>

#include "COMMON/GUI/ChampionsTable.h"
#include "COMMON/MAP/ColorLinesTileMap.h"
#include "COMMON/MISC/container_convenience.h"

static const ColorLinesTile::Color eatColor = ColorLinesTile::GREEN;

enum
{
    DIMENSIONS = 15,///< Количество строк и столбцов поля.
    APPLES_IN_STEP = 1,///< Количество яблок, появляющихся за один шаг.
    MINIMUM_MS = 30,///< Минимальный интервал между движениями змейки.
    PERIOD_DECREMENT_MS = 8 ///< Мера ускорения змейки после поедания яблока.
};

/// Варианты направлений движения.
enum Direction
{
    UP,
    LEFT,
    DOWN,
    RIGHT,

    COUNT
};

struct SnakeGameData
{
    explicit SnakeGameData(SnakeGame *game);
    Direction direction;
    QQueue<Direction> directionQueue;

    int period_ms;
    int apples;
    ColorLinesTileMap tileMap;
    std::vector<ColorLinesTile *> snake;
    std::vector<ColorLinesTile *> eaten;
    QString statistics;
    QTimer timer;
    std::default_random_engine randomEngine;    

    /// Выбор тайла, на который заползет змея на следующем ходе.
    ColorLinesTile *getNextHeadPosition(ColorLinesTile *head);
    ColorLinesTile *getHeadTurned(ColorLinesTile *head, Direction &turnedDirection);
    ColorLinesTile *getTile(ColorLinesTile *head, Direction direction) const;
    Direction getOppositeDirection(Direction direction) const;

private:
    SnakeGameData();
    explicit SnakeGameData(SnakeGameData&);
    SnakeGameData &operator =(const SnakeGameData&);
    /// Поместить пока еще короткую змейку на поле.
    void initSnakeOnField();
};

SnakeGameData::SnakeGameData(SnakeGame *game)
    : direction(UP),
      period_ms(500),
      apples(0),
      tileMap(DIMENSIONS, DIMENSIONS),
      randomEngine(time(NULL))
{
    initSnakeOnField();
    QObject::connect(&timer, SIGNAL(timeout()), game, SLOT(update()));
    timer.setSingleShot(true);
    timer.start(period_ms);
}

void SnakeGameData::initSnakeOnField()
{
    snake.push_back(tileMap.topLeft->getTile(DIMENSIONS / 2, DIMENSIONS / 2));
    snake.push_back(tileMap.topLeft->getTile(DIMENSIONS / 2, DIMENSIONS / 2 + 1));
}


ColorLinesTile *SnakeGameData::getNextHeadPosition(ColorLinesTile *head)
{
    if(!directionQueue.empty()){
        Direction tmp = directionQueue.takeFirst();
        if((getTile(head, tmp) != 0) && (tmp != getOppositeDirection(direction))){
            direction = tmp;
        }
    }

    ColorLinesTile *next = getTile(head, direction);
    bool isWall = (next == 0);

    if(isWall){
        Direction newDirection;
        next = getHeadTurned(head, newDirection);
        direction = newDirection;
    }else{
        // Next is already ok
    }

    return next;
}

ColorLinesTile *SnakeGameData::getTile(ColorLinesTile *head,
                                       Direction direction) const
{
    ColorLinesTile *next = 0;

    switch (direction) {
    case UP: next = head->getTopTile();
        break;
    case RIGHT: next = head->getRightTile();
        break;
    case DOWN: next = head->getBottomTile();
        break;
    case LEFT: next = head->getLeftTile();
        break;
    default:
        break;
    }

    return next;
}

ColorLinesTile *SnakeGameData::getHeadTurned(ColorLinesTile *head,
                                             Direction &turnedDirection)
{
    ColorLinesTile *next = 0;
    for(int i = 0; i < COUNT; i++){
        Direction candidateDirection = Direction((direction + i) % COUNT);
        bool notWall = getTile(head, candidateDirection) != 0;
        bool notBack = getOppositeDirection(direction) != candidateDirection;
        bool notDir = candidateDirection != direction;

        if(notWall && notBack && notDir){
            next = getTile(head, candidateDirection);
            turnedDirection = candidateDirection;
            break;
        }
    }

    assert(next != 0);
    return next;
}

Direction SnakeGameData::getOppositeDirection(Direction direction) const
{
    return Direction(((int)direction + 2) % COUNT);
}

SnakeGame::SnakeGame(QObject *parent)
    : AbstractColorLinesGame(parent), data(new SnakeGameData(this)), paused(false)
{        
    data.reset(new SnakeGameData(this));
    addApple();
}

SnakeGame::~SnakeGame()
{
}

void SnakeGame::keyPressed(int key, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers);
    assert(data);

    Direction tmpDirection = data->direction;
    switch (key) {
    case Qt::Key_Up:
        tmpDirection = UP;
        break;
    case Qt::Key_Down:
        tmpDirection = DOWN;
        break;
    case Qt::Key_Left:
        tmpDirection = LEFT;
        break;
    case Qt::Key_Right:
        tmpDirection = RIGHT;
        break;
    default:
        break;
    }
    if(data->direction != data->getOppositeDirection(data->direction)){
        data->directionQueue.enqueue(tmpDirection);
    }
}

void SnakeGame::pauseToggle()
{
    paused = !paused;
}

int SnakeGame::getRowCount() const
{
    return DIMENSIONS;
}
int SnakeGame::getColCount() const
{
    return DIMENSIONS;
}
int SnakeGame::getCoins() const
{
    assert(data);
    return data->apples;
}
const QString &SnakeGame::getStatistics() const
{
    assert(data);
    return data->statistics;
}
ColorLinesTile *SnakeGame::getRootTile() const
{
    assert(data);
    return data->tileMap.topLeft;
}
ColorLinesTile *SnakeGame::getSelectedTile() const
{
    return 0;
}
std::vector<ColorLinesTile *> const &SnakeGame::getPath() const
{
    assert(data);
    return data->snake;
}

void SnakeGame::update()
{
    if(!paused){
        assert(data);

        std::vector<ColorLinesTile *> newPath;
        int i = 0;
        ColorLinesTile *prevCurrent = 0;

        while(!data->snake.empty()){
            ColorLinesTile *current = data->snake.front();
            data->snake.erase(data->snake.begin());
            ColorLinesTile *next =  (i == 0) ? data->getNextHeadPosition(current) : prevCurrent;
            if(Container::contains(data->snake, next)){
                lose();
                return;
            }
            prevCurrent = current;
            newPath.push_back(next);
            /// Голова на еде
            if((i == 0) && (current->getColor() == eatColor)){
                data->tileMap.free(current);
                data->apples++;
                data->period_ms = ((data->period_ms - PERIOD_DECREMENT_MS) > MINIMUM_MS) ?
                            (data->period_ms - PERIOD_DECREMENT_MS) :
                            MINIMUM_MS;
                data->eaten.push_back(current);
            }
            /// Хвост на месте съеденного яблока
            if(data->snake.empty() && Container::contains(data->eaten, current)){
                newPath.push_back(current);
                data->eaten.erase(std::remove(data->eaten.begin(), data->eaten.end(), current), data->eaten.end());
            }
            i++;
        }
        data->snake = newPath;
        if(data->tileMap.ownedList.empty()){
            addApple();
        }
        data->statistics =
                QString("Apples=%1 Period=%2ms").arg(data->apples).arg(data->period_ms);
    }else {
        data->statistics = "Paused";
    }

    data->timer.start(data->period_ms);
}

void SnakeGame::lose()
{
    assert(data);

    ChampionsTable t("Ilya Yunkin", "Snake");
    t.setResult(data->apples);
    QMessageBox::StandardButton b =
            QMessageBox::question(0, tr("Game over!"), tr("Do you want to replay?"));
    if(b == QMessageBox::Yes)
    {
        data.reset(new SnakeGameData(this));
        data->timer.start(data->period_ms);

        addApple();
    }else{
        emit quitToMenu();
    }
}

void SnakeGame::addApple()
{
    assert(data);

    int freeCells = data->tileMap.freeList.size();
    int applesToAdd = std::min(freeCells, (int)APPLES_IN_STEP);
    if(applesToAdd == 0){
        lose();
    }else{
        int i = 0;
        while(i < applesToAdd)
        {
            int cell = data->randomEngine() % freeCells;
            ColorLinesTile *tile = data->tileMap.freeList[cell];
            if(!Container::contains(data->snake, tile)){
                data->tileMap.set(tile, ColorLinesTile::GREEN);
                --freeCells;
                i++;
            }
        }
        if(data->tileMap.ownedList.empty()){// Чтобы с пустым полем не остаться
            addApple();
        }
    }
    freeCells = data->tileMap.freeList.size();

    if(freeCells == 0){
        lose();
    }
}
