/** @file
  * @author Yunkin Ilya.
  */
#ifndef COLORLINESBUILDER_H
#define COLORLINESBUILDER_H

#include "COMMON/INTERFACES/AbstractGameBuilder.h"

class ColorLinesBuilder : public AbstractGameBuilder
{
public:
    void createGame(AbstractColorLinesGame *&game, QWidget *&widget);
    QString getName() const;
    QIcon getIcon() const;
};

#endif // COLORLINESBUILDER_H
