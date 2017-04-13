/** @file
  * @author Yunkin Ilya.
  */
#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <QSharedPointer>

#include "Lines/AbstractColorLinesGame.h"

struct GameData;

/// Реализация игры "Тетрис"
class TetrisGame : public AbstractColorLinesGame
{
    Q_OBJECT
    friend class GameData;

    /// Приватная реализация.
    QSharedPointer<GameData> data;

    /// Обработка поражения.
    void lose();
    /// Проверяет строку row  очищает ее, если она вся заполнена.
    bool clearIfLined(int row);
    /// Очищает все заполненные строки.
    bool clearIfLined();
    /// Опускает верхние строки на место образовавшихся пустот.
    void dropAfterLined(int row);
    /// Поворачивает двигающуюся фигуру.
    void rotate();
    /// Возвращает истину, если поле застроено до верхней границы
    bool isCaput();
public:
    TetrisGame();
    int getRowCount() const;
    int getColCount() const;
    int getCoins() const;
    const QString &getStatistics() const;
    ColorLinesTile *getRootTile() const;
    ColorLinesTile *getSelectedTile() const;
    QList<ColorLinesTile *> const&getPath() const;
private slots:
    void update();
public slots:
    void keyPressed(int key, Qt::KeyboardModifiers modifiers);
    void keyReleased(int key);
    void pauseToggle();
};

#endif // TETRISGAME_H
