#ifndef SNAKEGAMEBUILDER_H
#define SNAKEGAMEBUILDER_H

#include "COMMON/INTERFACES/AbstractGameBuilder.h"

class SnakeGameBuilder : public AbstractGameBuilder
{
public:
    void createGame(AbstractColorLinesGame *&game, QWidget *&widget);
};

#endif // SNAKEGAMEBUILDER_H