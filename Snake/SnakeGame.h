/** @file
  * @author Yunkin Ilya.
  */
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "Lines/AbstractColorLinesGame.h"

#include <QSharedPointer>

struct GameData;

class SnakeGame : public AbstractColorLinesGame
{
    Q_OBJECT

    QSharedPointer<GameData> data;

    ColorLinesTile *getNextHeadPosition(ColorLinesTile *head);
    void lose();
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
