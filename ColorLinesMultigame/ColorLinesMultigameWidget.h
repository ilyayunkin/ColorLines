/** @file
  * @author Yunkin Ilya.
  */
#ifndef COLORLINESMULTIGAMEWIDGET_H
#define COLORLINESMULTIGAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>

#include <map>
#include <memory>

#include "COMMON/INTERFACES/AbstractGameBuilder.h"
#include "MenuWidget.h"

class ColorLinesMultigameWidget : public QWidget
{
    Q_OBJECT

    std::unique_ptr<AbstractColorLinesGame> game;
    QWidget *gameWidget;
    MenuWidget *menuWidget;

    typedef std::map<QObject *, std::unique_ptr<AbstractGameBuilder> > ButtonToBuilderMap;
    ButtonToBuilderMap buttonToBuilderMap;

    void runGame(AbstractGameBuilder *builder);
    void addBuilder(AbstractGameBuilder *builder);
    void setDefaultWindowTitle();
    void setDefaultWindowIcon();

public:
    explicit ColorLinesMultigameWidget(QWidget *parent = 0);
    ~ColorLinesMultigameWidget();

private slots:
    void runGameClicked();

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

    void quitToMenu();
};

#endif // COLORLINESMULTIGAMEWIDGET_H
