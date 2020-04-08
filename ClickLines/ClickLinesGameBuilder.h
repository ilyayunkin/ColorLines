#ifndef CLICKLINESGAMEBUILDER_H
#define CLICKLINESGAMEBUILDER_H

#include "COMMON/INTERFACES/AbstractGameBuilder.h"

class ClickLinesGameBuilder : public AbstractGameBuilder
{
public:
    void createGame(AbstractColorLinesGame *&game, QWidget *&widget) override;
    QString getName() const override;
    QIcon getIcon() const override;
};

#endif // CLICKLINESGAMEBUILDER_H
