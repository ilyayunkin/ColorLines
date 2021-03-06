/** @file
  * @author Yunkin Ilya.
  */
#ifndef COLORLINESBUILDER_H
#define COLORLINESBUILDER_H

#include "COMMON/INTERFACES/AbstractGameBuilder.h"

class ColorLinesBuilder : public AbstractGameBuilder
{
public:
    void createGame(AbstractColorLinesGame *&game, QWidget *&widget) override;
    QString getName() const override;
    QIcon getIcon() const override;
};

#endif // COLORLINESBUILDER_H
