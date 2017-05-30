/** @file
  * @author Yunkin Ilya.
  */
#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPushButton>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = 0);
    void addButton(QPushButton *button);
};

#endif // MENUWIDGET_H
