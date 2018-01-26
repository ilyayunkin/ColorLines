#ifndef CLICKLINESGAME_H
#define CLICKLINESGAME_H

#include "COMMON/INTERFACES/AbstractColorLinesGame.h"

#include <QSharedPointer>

#include "COMMON/MAP/ColorLinesTileMap.h"

struct ClickLinesGameData;

class ClickLinesGame : public AbstractColorLinesGame
{
    Q_OBJECT 

    QSharedPointer<ClickLinesGameData> data;
    /// Роняет тайлы, находящиеся над пустотами.
    void dropDown();
    /// Сдвигает влево тайлы, находящиеся правее пустот.
    /// Должна вызываться после dropDown();
    void moveLeft();
    void lose();

public:
    explicit ClickLinesGame(QObject *parent = 0);
    int getRowCount() const;
    int getColCount() const;
    int getCoins() const;
    const QString &getStatistics() const;
    ColorLinesTile *getRootTile() const;
    ColorLinesTile *getSelectedTile() const;
    QList<ColorLinesTile *> const&getPath() const;
public slots:
    void tileClicked(int col, int row);
};

#endif // CLICKLINESGAME_H
