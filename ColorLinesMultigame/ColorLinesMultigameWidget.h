#ifndef COLORLINESMULTIGAMEWIDGET_H
#define COLORLINESMULTIGAMEWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include <QKeyEvent>

#include "COMMON/INTERFACES/AbstractGameBuilder.h"
#include "MenuWidget.h"

class ColorLinesMultigameWidget : public QWidget
{
    Q_OBJECT

    QSharedPointer<AbstractColorLinesGame> game;
    QWidget *gameWidget;
    MenuWidget *menuWidget;

    void runGame(AbstractGameBuilder *builder);
public:
    ColorLinesMultigameWidget(QWidget *parent = 0);
    ~ColorLinesMultigameWidget();

public slots:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

    void runColorLines();
    void runSnake();
    void runTetris();
};

#endif // COLORLINESMULTIGAMEWIDGET_H
