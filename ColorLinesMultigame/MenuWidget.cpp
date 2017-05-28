/** @file
  * @author Yunkin Ilya.
  */
#include "MenuWidget.h"

#include <QPushButton>
#include <QVBoxLayout>

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *lay = new QVBoxLayout(this);
    {
        QPushButton *b = new QPushButton(QIcon(":/icons/icons/lines_ico.png"),
                                         "Color Lines");
        lay->addWidget(b);
        connect(b, SIGNAL(clicked()), SIGNAL(runColorLines()));
    }
    {
        QPushButton *b = new QPushButton(QIcon(":/icons/icons/snake_ico.png"),
                                         "Snake");
        lay->addWidget(b);
        connect(b, SIGNAL(clicked()), SIGNAL(runSnake()));
    }
    {
        QPushButton *b = new QPushButton(QIcon(":/icons/icons/tetris_ico.png"),
                                         "Tetris");
        lay->addWidget(b);
        connect(b, SIGNAL(clicked()), SIGNAL(runTetris()));
    }
    setMinimumSize(200, 300);
}
