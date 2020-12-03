/** @file
  * @author Yunkin Ilya.
  */
#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <memory>
#include <vector>

#include "COMMON/INTERFACES/AbstractColorLinesGame.h"

struct TetrisGameData;

/// Реализация игры "Тетрис"
class TetrisGame : public AbstractColorLinesGame
{
    Q_OBJECT
    friend class TetrisGameData;

    /// Приватная реализация.
    std::unique_ptr<TetrisGameData> data;

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
    bool isCaput() const;
public:
    TetrisGame();
    ~TetrisGame();
    int getRowCount() const override;
    int getColCount() const override;
    int getCoins() const;
    const QString &getStatistics() const override;
    ColorLinesTile *getRootTile() const override;
    ColorLinesTile *getSelectedTile() const override;
    std::vector<ColorLinesTile *> const&getPath() const override;
private slots:
    void update();
public slots:
    void keyPressed(int key, Qt::KeyboardModifiers modifiers) override;
    void keyReleased(int key) override;
    void pauseToggle() override;
};

#endif // TETRISGAME_H
