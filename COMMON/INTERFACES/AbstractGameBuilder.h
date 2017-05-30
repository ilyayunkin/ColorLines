/** @file
  * @author Yunkin Ilya.
  */
#ifndef ABSTRACTGAMEBUILDER_H
#define ABSTRACTGAMEBUILDER_H

#include <QWidget>
#include <QIcon>

#include "AbstractColorLinesGame.h"

class AbstractGameBuilder
{
public:
    virtual ~AbstractGameBuilder() = 0;
    virtual void createGame(AbstractColorLinesGame *&game, QWidget *&widget) = 0;
    virtual QString getName() const = 0;
    virtual QIcon getIcon() const = 0;
};

#endif // ABSTRACTGAMEBUILDER_H
