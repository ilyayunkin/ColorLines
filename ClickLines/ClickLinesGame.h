#ifndef CLICKLINESGAME_H
#define CLICKLINESGAME_H

#include "COMMON/INTERFACES/AbstractColorLinesGame.h"

#include <memory>
#include <vector>

#include "COMMON/MAP/ColorLinesTileMap.h"

struct ClickLinesGameData;

class ClickLinesGame : public AbstractColorLinesGame
{
    Q_OBJECT 

    std::unique_ptr<ClickLinesGameData> data;
    /// Роняет тайлы, находящиеся над пустотами.
    void dropDown();
    /// Сдвигает влево тайлы, находящиеся правее пустот.
    /// Должна вызываться после dropDown();
    void moveLeft();
    void lose();

public:
    explicit ClickLinesGame(QObject *parent = 0);
    ~ClickLinesGame();
    int getRowCount() const override;
    int getColCount() const override;
    int getCoins() const;
    const QString &getStatistics() const override;
    ColorLinesTile *getRootTile() const override;
    ColorLinesTile *getSelectedTile() const override;
    std::vector<ColorLinesTile *> const&getPath() const override;
public slots:
    void tileClicked(int col, int row) override;
};

#endif // CLICKLINESGAME_H
