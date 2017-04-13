/** @file
  * @author Yunkin Ilya.
  */
#ifndef TETRISGAME_H
#define TETRISGAME_H

#include <QSharedPointer>

#include "Lines/AbstractColorLinesGame.h"

struct Block;
struct GameData;

class TetrisGame : public AbstractColorLinesGame
{
    Q_OBJECT
    friend class GameData;

    QSharedPointer<GameData> data;

    void lose();
    bool clearIfLined(int row);
    bool clearIfLined();
    void dropAfterLined(int row);
    void rotate();
    bool isCaput();
    Block *createBlock();
    bool paused;
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
