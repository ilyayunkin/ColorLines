/** @file
  * @author Yunkin Ilya.
  */
#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QObject>

#include "JustAnotherLines.h"
#include "COMMON/MAP/ColorLinesTileMap.h"

enum
{
    /// Количество тайлов в строке или столбце.
    DIMENSION = 9,
    /// Минимальная длина линии одного цвета.
    MIN_LINE = 5,
};

class AbstractGameState
{
public:
    virtual void update() = 0;
    virtual void tileClicked(int col, int row) = 0;
    virtual ~AbstractGameState(){};
};

class ElementMovingState : public AbstractGameState
{
    GameData *data;
public:
    explicit ElementMovingState(GameData *data);
    void update();
    void tileClicked(int col, int row);
};

class WaitingState : public AbstractGameState
{
    GameData *data;
public:
    explicit WaitingState(GameData *data);
    void update();
    void tileClicked(int col, int row);
};

class GameData: public QObject
{
    Q_OBJECT

    /// Последний успешно проделанный путь между тайлами.
public:
    QList<ColorLinesTile *> path;
    /// Коэффициент, на который умножатся очки за ход в случае еще одного
    /// удачного хода подряд.
    int combo;
    /// Набранные очки.
    int coins;

    ColorLinesTileMap tileMap;
    /// Выделенный тайл с фишкой.
    ColorLinesTile *selection;
    QString statistics;
    QList<ColorLinesTile *>::iterator pathIterator;

    QSharedPointer<ElementMovingState> elementMovingStatePointer;
    QSharedPointer<WaitingState> waitingStatePointer;
    AbstractGameState *currentState;

    NextColors nextColors;

    explicit GameData(JustAnotherLines *game);
private:
    JustAnotherLines *game;
    GameData();
    explicit GameData(GameData&);
    GameData &operator =(const GameData&);

public slots:
    /**
     * @brief Очистка последнего пути в памяти.
     */
    void pathClean();
public:
    /**
     * @brief Очищает горизонтальную, вертикальную и две диагональных линии
     * одного цвета достаточной длины, проходящие через тайл.
     * @param tile Проверяемый тайл, относительно которого построятся
     * @return True если удалена линия.
     */
    bool clearIfLined(ColorLinesTile *tile);
    /**
     * @brief Сравнивает длину линии с минимальной требуемой,
     * если длина достаночна, очищает тайлы.
     * @param list Список тайлов одного цвета, выстроенных в одну линию.
     * @return  Начисленные очки.
     */
    int clearIfLined(QList<ColorLinesTile *> line);
    /**
     * @brief Добавляет случайные финки в случайные свободные тайлы.
     */
    void placeBalls();

    void randomColors();
    /**
     * @brief Проверяет наличие пути между тайлами через свободные ячейки.
     * @param from Начальная точка.
     * @param to Конечная точка.
     * @return true если такой путь существует.
     */
    bool buildPath(ColorLinesTile *from, ColorLinesTile *to);

    void goToWaitingState();
    void goToElementMovingState();
};

#endif // GAMEDATA_H
