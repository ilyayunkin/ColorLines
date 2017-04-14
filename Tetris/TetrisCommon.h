#ifndef TETRISCOMMON_H
#define TETRISCOMMON_H

#include "Lines/ColorLinesTile.h"

enum
{
    PLOT_ROW_CNT = 20,
    PLOT_COL_CNT = 10,

    TIMER_PERIOD = 10,
    MIN_DOWN_PERIOD = 3,
    HORIZONTAL_MOVING_PERIOD = 10,
    DOWN_PERIOD_DECREMENT = 2
};

#define blockColor ColorLinesTile::CYAN
#define buildingColor ColorLinesTile::BLACK

#endif // TETRISCOMMON_H
