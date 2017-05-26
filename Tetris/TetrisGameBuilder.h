#ifndef TETRISGAMEBUILDER_H
#define TETRISGAMEBUILDER_H

#include "COMMON/INTERFACES/AbstractGameBuilder.h"

class TetrisGameBuilder : public AbstractGameBuilder
{
public:
    void createGame(AbstractColorLinesGame *&game, QWidget *&widget);
};

#endif // TETRISGAMEBUILDER_H
