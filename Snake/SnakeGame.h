/** @file
  * @author Yunkin Ilya.
  */
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "COMMON/INTERFACES/AbstractColorLinesGame.h"

#include <QSharedPointer>

struct SnakeGameData;

/// Игра в змейку.
/// Использованы механизмы игры "Цветные линии":
/// Фишки - яблоки. Путь - змейка.
class SnakeGame : public AbstractColorLinesGame
{
    Q_OBJECT

    /// Приватная реализация
    QSharedPointer<SnakeGameData> data;
    /// Обработка поражения
    void lose();
    /// Вбросить новое яблоко на поле.
    void addApple(); 
    bool paused;
public:
    explicit SnakeGame(QObject *parent = 0);
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
    void pauseToggle();
};

#endif // SNAKEGAME_H
