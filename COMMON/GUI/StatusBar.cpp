#include "StatusBar.h"

#include <QTimer>

StatusBar::StatusBar(AbstractColorLinesGame *game, QWidget *parent) :
    QLabel(parent),
    game(game)
{
    QTimer *t = new QTimer(this);
    t->start(100);

    connect(t, SIGNAL(timeout()), SLOT(update()));
}

void StatusBar::update()
{
    setText(game->getStatistics());
}
