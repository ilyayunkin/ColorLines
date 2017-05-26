#include "MenuWidget.h"

#include <QPushButton>
#include <QVBoxLayout>

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *lay = new QVBoxLayout(this);
    {
        QPushButton *b = new QPushButton("Color Lines");
        lay->addWidget(b);
        connect(b, SIGNAL(clicked()), this, SIGNAL(runColorLines()));
    }
    {
        QPushButton *b = new QPushButton("Snake");
        lay->addWidget(b);
        connect(b, SIGNAL(clicked()), this, SIGNAL(runSnake()));
    }
    {
        QPushButton *b = new QPushButton("Tetris");
        lay->addWidget(b);
        connect(b, SIGNAL(clicked()), this, SIGNAL(runTetris()));
    }
}
