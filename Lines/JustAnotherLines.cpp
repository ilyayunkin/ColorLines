/** @file
  * @author Yunkin Ilya.
  */
#include "JustAnotherLines.h"

#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <QMessageBox>
#include <QTimer>
#include <QApplication>

#include "COMMON/GUI/ChampionsTable.h"
#include "COMMON/MAP/ColorLinesTileMap.h"

#include "GameData.h"

class AdapterData
{
public:
    AdapterData();
    ColorLinesTileMap tileMap;
    QList<ColorLinesTile *> path;
};

AdapterData::AdapterData() :
    tileMap(BALLS_IN_STEP, 1)
{

}

Adapter::Adapter(JustAnotherLines *game, QObject *parent) :
    AbstractColorLinesGame(parent),
    data(new AdapterData),
    game(game)
{
    QTimer *t =  new QTimer;
    t->start(10);
    QObject::connect(t, SIGNAL(timeout()), this, SLOT(update()));
}

Adapter::~Adapter()
{

}

void Adapter::update()
{
    assert(!data.isNull());

    ColorLinesTile *tile = data->tileMap.topLeft;
    NextColors nextColors = game->getNextColors();
    for(int i = 0; i < data->tileMap.getColCount(); i++){
        data->tileMap.set(tile, nextColors.color[i]);
        tile = tile->getRightTile();
    }
}

int Adapter::getRowCount() const
{
    assert(!data.isNull());
    return data->tileMap.getRowCount();
}
int Adapter::getColCount() const
{
    assert(!data.isNull());
    return data->tileMap.getColCount();
}
ColorLinesTile *Adapter::getRootTile() const
{
    assert(!data.isNull());
    return data->tileMap.topLeft;
}
ColorLinesTile *Adapter::getSelectedTile() const
{
    return 0;
}
QList<ColorLinesTile *> const& Adapter::getPath() const
{
    assert(!data.isNull());
    return data->path;
}

JustAnotherLines::JustAnotherLines(QObject *parent)
    : AbstractColorLinesGame(parent),
      data(new ColorLinesGameData(this))
{    
    srand(time(0));
    data->placeBalls();

    QTimer *t = new QTimer(this);
    QObject::connect(t, SIGNAL(timeout()), this, SLOT(update()));
    t->start(100);
}

void JustAnotherLines::lose()
{
    assert(!data.isNull());

    ChampionsTable t("Ilya Yunkin", "Just Another Lines");
    t.setCoins(data->coins);
    QMessageBox::StandardButton b =
            QMessageBox::question(0, tr("Game over!"), tr("Do you want to replay?"));
    if(b == QMessageBox::Yes)
    {
        data = QSharedPointer<ColorLinesGameData>(new ColorLinesGameData(this));
        data->placeBalls();
    }else{
        emit quitToMenu();
    }
}

AbstractColorLinesGame *JustAnotherLines::getAdapter()
{
    return new Adapter(this);
}


int JustAnotherLines::getRowCount() const
{
    return DIMENSION;
}

int JustAnotherLines::getColCount() const
{
    return DIMENSION;
}

int JustAnotherLines::getCoins() const
{
    assert(!data.isNull());
    return data->coins;
}

int JustAnotherLines::getCombo() const
{
    assert(!data.isNull());
    return data->combo;
}

const QString &JustAnotherLines::getStatistics() const
{
    assert(!data.isNull());
    return data->statistics;
}

ColorLinesTile *JustAnotherLines::getRootTile() const
{
    assert(!data.isNull());
    return data->tileMap.topLeft;
}

ColorLinesTile *JustAnotherLines::getSelectedTile() const
{
    assert(!data.isNull());
    return data->selection;
}

QList<ColorLinesTile *> const&JustAnotherLines::getPath() const
{
    assert(!data.isNull());
    return data->path;
}

void JustAnotherLines::tileClicked(int col, int row)
{
    assert(!data.isNull());
    data->currentState->tileClicked(col, row);
}

void JustAnotherLines::update()
{
    assert(!data.isNull());
    if(data->isLose()){
        lose();
    }else{
        data->currentState->update();
    }
}

NextColors JustAnotherLines::getNextColors()
{
    assert(!data.isNull());
    return data->nextColors;
}

