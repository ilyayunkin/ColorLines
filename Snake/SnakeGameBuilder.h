/** @file
  * @author Yunkin Ilya.
  */
#ifndef SNAKEGAMEBUILDER_H
#define SNAKEGAMEBUILDER_H

#include "COMMON/INTERFACES/AbstractGameBuilder.h"

class SnakeGameBuilder : public AbstractGameBuilder
{
public:
    void createGame(AbstractColorLinesGame *&game, QWidget *&widget);
    QString getName() const;
    QIcon getIcon() const;
};

#endif // SNAKEGAMEBUILDER_H
