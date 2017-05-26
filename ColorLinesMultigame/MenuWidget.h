/** @file
  * @author Yunkin Ilya.
  */
#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = 0);

signals:
    void runColorLines();
    void runSnake();
    void runTetris();
};

#endif // MENUWIDGET_H
