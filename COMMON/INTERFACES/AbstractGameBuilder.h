#ifndef ABSTRACTGAMEBUILDER_H
#define ABSTRACTGAMEBUILDER_H

#include <QWidget>
#include "AbstractColorLinesGame.h"

class AbstractGameBuilder
{
public:
    virtual ~AbstractGameBuilder() = 0;
    virtual void createGame(AbstractColorLinesGame *&game, QWidget *&widget) = 0;
};

#endif // ABSTRACTGAMEBUILDER_H
