#ifndef CLICKLINESGAMEBUILDER_H
#define CLICKLINESGAMEBUILDER_H

#include "COMMON/INTERFACES/AbstractGameBuilder.h"

class ClickLinesGameBuilder : public AbstractGameBuilder
{
public:
    void createGame(AbstractColorLinesGame *&game, QWidget *&widget);
    QString getName() const;
    QIcon getIcon() const;
};

#endif // CLICKLINESGAMEBUILDER_H
