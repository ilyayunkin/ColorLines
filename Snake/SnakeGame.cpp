/** @file
  * @author Yunkin Ilya.
  */
#include "SnakeGame.h"

#include <assert.h>
#include <time.h>

#include <QMessageBox>
#include <QTimer>

#include "COMMON/GUI/ChampionsTable.h"
#include "COMMON/MAP/ColorLinesTileMap.h"

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

struct GameData
{
    GameData(SnakeGame *game);
    Direction direction;
    Direction newDirection;

    int period_ms;
    int apples;
    ColorLinesTileMap tileMap;
    QList<ColorLinesTile *> snake;
    QList<ColorLinesTile *> eaten;
    QString statistics;
    QTimer timer;
private:
    GameData();
    explicit GameData(GameData&);
    GameData &operator =(const GameData&);
    /// Поместить пока еще короткую змейку на поле.
    void initSnakeOnField();
};

GameData::GameData(SnakeGame *game)
    : direction(UP),
      newDirection(direction),
      period_ms(500),
      apples(0),
      tileMap(DIMENSIONS, DIMENSIONS)
{
    initSnakeOnField();
    QObject::connect(&timer, SIGNAL(timeout()), game, SLOT(update()));
    timer.setSingleShot(true);
    timer.start(period_ms);
}

void GameData::initSnakeOnField()
{
    snake.push_back(tileMap.topLeft->getTile(DIMENSIONS / 2, DIMENSIONS / 2));
    snake.push_back(tileMap.topLeft->getTile(DIMENSIONS / 2, DIMENSIONS / 2 + 1));
}

SnakeGame::SnakeGame(QObject *parent)
    : AbstractColorLinesGame(parent), data(new GameData(this)), paused(false)
{        
    srand(time(0));
    addApple();
}

void SnakeGame::keyPressed(int key, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers);
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
    if(data->direction != Direction(((int)tmpDirection + 2) % COUNT)){
        data->newDirection = tmpDirection;
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
    return data->apples;
}
const QString &SnakeGame::getStatistics() const
{
    return data->statistics;
}
ColorLinesTile *SnakeGame::getRootTile() const
{
    return data->tileMap.topLeft;
}
ColorLinesTile *SnakeGame::getSelectedTile() const
{
    return 0;
}
QList<ColorLinesTile *> const &SnakeGame::getPath() const
{
    return data->snake;
}

void SnakeGame::update()
{
    if(!paused){
        data->direction = data->newDirection;
        QList<ColorLinesTile *> newPath;
        int i = 0;
        ColorLinesTile *next = 0;
        ColorLinesTile *prevCurrent = 0;
        while(!data->snake.isEmpty()){
            ColorLinesTile *current = data->snake.takeFirst();
            next = (i == 0) ? getNextHeadPosition(current) : prevCurrent;
            if(data->snake.contains(next)){
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
            if(data->snake.isEmpty() && data->eaten.contains(current)){
                newPath.push_back(current);
                data->eaten.removeAll(current);
            }
            i++;
        }
        data->snake = newPath;
        if(data->tileMap.ownedList.isEmpty()){
            addApple();
        }
        data->statistics =
                QString("Apples=%1 Period=%2ms").arg(data->apples).arg(data->period_ms);
    }else {
        data->statistics = "Paused";
    }

    data->timer.start(data->period_ms);
}

ColorLinesTile *SnakeGame::getNextHeadPosition(ColorLinesTile *head)
{
    ColorLinesTile *next = 0;

    /// i - небольшой трюк, чтобы змея не сменила направление
    /// на противоположное и не захавала сегмент сразу за головой.
    int i = 1;
    while(next == 0){
        switch (data->direction) {
        case UP: next = head->getTopTile();
            break;
        case RIGHT: next = head->getRightTile();
            break;
        case DOWN: next = head->getBottomTile();
            break;
        case LEFT: next = head->getLeftTile();
            break;
        default:
            assert(false);
            break;
        }
        if((next == 0)){
            data->direction = data->newDirection =
                    Direction(((int)data->direction + i) % COUNT);
            i++;
        }
    }

    return next;
}

void SnakeGame::lose()
{
    ChampionsTable t("Ilya Yunkin", "Snake");
    t.setCoins(data->apples);
    QMessageBox::StandardButton b =
            QMessageBox::question(0, tr("Game over!"), tr("Do you want to replay?"));
    if(b == QMessageBox::Yes)
    {
        data = QSharedPointer<GameData>(new GameData(this));
        data->timer.start(data->period_ms);

        addApple();
    }
}

void SnakeGame::addApple()
{
    int freeCells = data->tileMap.freeList.size();
    int applesToAdd = std::min(freeCells, (int)APPLES_IN_STEP);
    if(applesToAdd == 0){
        lose();
    }else{
        int i = 0;
        while(i < applesToAdd)
        {
            int cell = rand() % freeCells;
            ColorLinesTile *tile = data->tileMap.freeList[cell];
            if(!data->snake.contains(tile)){
                data->tileMap.set(tile, ColorLinesTile::GREEN);
                --freeCells;
                i++;
            }
        }
        if(data->tileMap.ownedList.size() == 0){// Чтобы с пустым полем не остаться
            addApple();
        }
    }
    freeCells = data->tileMap.freeList.size();

    if(freeCells == 0){
        lose();
    }
}
