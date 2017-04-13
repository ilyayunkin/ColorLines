/** @file
  * @author Yunkin Ilya.
  */
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "JustAnotherLines.h"

/// Color Lines game window
class MainWidget : public QWidget
{
    Q_OBJECT
public:
     MainWidget(JustAnotherLines *game, QWidget *parent = 0);
};

#endif // MAINWIDGET_H
