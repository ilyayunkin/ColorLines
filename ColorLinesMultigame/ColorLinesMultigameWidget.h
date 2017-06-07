/** @file
  * @author Yunkin Ilya.
  */
#ifndef COLORLINESMULTIGAMEWIDGET_H
#define COLORLINESMULTIGAMEWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include <QKeyEvent>
#include <QMap>

#include "COMMON/INTERFACES/AbstractGameBuilder.h"
#include "MenuWidget.h"

class ColorLinesMultigameWidget : public QWidget
{
    Q_OBJECT

    QSharedPointer<AbstractColorLinesGame> game;
    QWidget *gameWidget;
    MenuWidget *menuWidget;

    typedef QMap<QObject *, QSharedPointer<AbstractGameBuilder> > ButtonToBuilderMap;
    ButtonToBuilderMap buttonToBuilderMap;

    void runGame(AbstractGameBuilder *builder);
    void addBuilder(AbstractGameBuilder *builder);
    void setDefaultWindowTitle();
    void setDefaultWindowIcon();

public:
    ColorLinesMultigameWidget(QWidget *parent = 0);
    ~ColorLinesMultigameWidget();

private slots:
    void runGameClicked();

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

    void quitToMenu();
};

#endif // COLORLINESMULTIGAMEWIDGET_H
