#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "JustAnotherLines.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(JustAnotherLines *game, QWidget *parent = 0);

signals:

public slots:
};

#endif // MAINWIDGET_H
