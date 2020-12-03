/** @file
  * @author Yunkin Ilya.
  */
#ifndef ABSTRACTCOLORLINESGAME_H
#define ABSTRACTCOLORLINESGAME_H

#include <vector>

#include <QObject>

#include "COMMON/MAP/ColorLinesTile.h"

/// Интерфейс для взаимодействия игры
/// и класса представления игрового поля с фишками.
class AbstractColorLinesGame : public QObject
{
    Q_OBJECT
    const QString emptyString;
public:
    explicit AbstractColorLinesGame(QObject *parent = 0);
    virtual ~AbstractColorLinesGame() = 0;
    /// Количество строк игрового поля.
    virtual int getRowCount() const = 0;
    /// Количество колонок игрового поля.
    virtual int getColCount() const = 0;
    /// Строка игровой статистики. Это могут быть очки, уровень и т.д.
    virtual const QString &getStatistics() const;
    /// Левый верхний квадрат игрового поля.
    virtual ColorLinesTile *getRootTile() const = 0;
    /// Выделенный квадрат.
    virtual ColorLinesTile *getSelectedTile() const = 0;
    /// Цепочка тайлов, составляющая путь из начальной точки в конечную.
    virtual std::vector<ColorLinesTile *> const&getPath() const = 0;

public slots:
    /// Обработчик нажатия на квадрат игрового поля.
    virtual void tileClicked(int col, int row);
    /// Обработчик нажатия клавиши клавиатуры.
    virtual void keyPressed(int key, Qt::KeyboardModifiers modifiers);
    /// Обработчик отжатия клавиши клавиатуры.
    /// @warning Нажатие кнопок Pause, Esc не приведет к вызову этого слота.
    virtual void keyReleased(int key);
    /// Обработчик нажатия на кнопку "Pause".
    virtual void pauseToggle();
    /// Обработчик нажатия на кнопку "Esc".
    virtual void escape();

signals:
    /// Сигнализирует о нежелании продолжать игру.
    void quitToMenu();
};

#endif // ABSTRACTCOLORLINESGAME_H
