/** @file
  * @author Yunkin Ilya.
  */
#ifndef JUSTANOTHERLINES_H
#define JUSTANOTHERLINES_H

#include "AbstractColorLinesGame.h"

#include <QSharedPointer>

class JustAnotherLines;
class AdapterData;

class Adapter : public AbstractColorLinesGame
{
    Q_OBJECT
    QSharedPointer<AdapterData> data;
    JustAnotherLines *game;
private slots:
    void update();
public:
    Adapter(JustAnotherLines *game, QObject *parent = 0);
    ~Adapter();
    int getRowCount() const;
    int getColCount() const;
    ColorLinesTile *getRootTile() const;
    ColorLinesTile *getSelectedTile() const;
    QList<ColorLinesTile *> const&getPath() const;
};

class GameData;

enum
{
    /// Количество фишек, появляющихся за один раз.
    BALLS_IN_STEP = 3,
};

struct NextColors
{
    ColorLinesTile::Color color[BALLS_IN_STEP];
};

class JustAnotherLines : public AbstractColorLinesGame
{
    Q_OBJECT

    QSharedPointer<GameData> data;
    /// Обрабатывает случай поражения.
public:
    explicit JustAnotherLines(QObject *parent = 0);
    int getRowCount() const;
    int getColCount() const;
    int getCoins() const;
    int getCombo() const;
    const QString &getStatistics() const;
    ColorLinesTile *getRootTile() const;
    ColorLinesTile *getSelectedTile() const;
    QList<ColorLinesTile *> const&getPath() const;
    void lose();
    AbstractColorLinesGame *getAdapter() { return new Adapter(this);}

    NextColors getNextColors();

private slots:
    void update();

public slots:
    void tileClicked(int col, int row);
};

#endif // JUSTANOTHERLINES_H
