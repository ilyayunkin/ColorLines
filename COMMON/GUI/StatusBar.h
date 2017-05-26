#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "../INTERFACES/AbstractColorLinesGame.h"

#include <QLabel>

class StatusBar : public QLabel
{
    Q_OBJECT

    AbstractColorLinesGame * game;
public:
    StatusBar(AbstractColorLinesGame * game, QWidget *parent = 0);

private slots:
    void update();
};

#endif // STATUSBAR_H
