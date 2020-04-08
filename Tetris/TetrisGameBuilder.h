/** @file
  * @author Yunkin Ilya.
  */
#ifndef TETRISGAMEBUILDER_H
#define TETRISGAMEBUILDER_H

#include "COMMON/INTERFACES/AbstractGameBuilder.h"

class TetrisGameBuilder : public AbstractGameBuilder
{
public:
    void createGame(AbstractColorLinesGame *&game, QWidget *&widget) override;
    QString getName() const override;
    QIcon getIcon() const override;
};

#endif // TETRISGAMEBUILDER_H
