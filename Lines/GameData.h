/** @file
  * @author Yunkin Ilya.
  */
#ifndef ColorLinesGameData_H
#define ColorLinesGameData_H

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
    ColorLinesGameData *data;
public:
    explicit ElementMovingState(ColorLinesGameData *data);
    void update();
    void tileClicked(int col, int row);
};

class WaitingState : public AbstractGameState
{
    ColorLinesGameData *data;
public:
    explicit WaitingState(ColorLinesGameData *data);
    void update();
    void tileClicked(int col, int row);
};

class ColorLinesGameData: public QObject
{
    Q_OBJECT

    bool lose;
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

    explicit ColorLinesGameData(JustAnotherLines *game);
private:
    JustAnotherLines *game;
    ColorLinesGameData();
    explicit ColorLinesGameData(ColorLinesGameData&);
    ColorLinesGameData &operator =(const ColorLinesGameData&);

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

    bool isLose();
};

#endif // ColorLinesGameData_H
