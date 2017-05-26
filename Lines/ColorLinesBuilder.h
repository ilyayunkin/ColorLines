#ifndef COLORLINESBUILDER_H
#define COLORLINESBUILDER_H

#include "COMMON/INTERFACES/AbstractGameBuilder.h"

class ColorLinesBuilder : public AbstractGameBuilder
{
public:
    void createGame(AbstractColorLinesGame *&game, QWidget *&widget);
};

#endif // COLORLINESBUILDER_H
