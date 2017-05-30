/** @file
  * @author Yunkin Ilya.
  */
#ifndef TETRISGAMEBUILDER_H
#define TETRISGAMEBUILDER_H

#include "COMMON/INTERFACES/AbstractGameBuilder.h"

class TetrisGameBuilder : public AbstractGameBuilder
{
public:
    void createGame(AbstractColorLinesGame *&game, QWidget *&widget);
    QString getName() const;
    QIcon getIcon() const;
};

#endif // TETRISGAMEBUILDER_H
