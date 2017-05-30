/** @file
  * @author Yunkin Ilya.
  */
#include "MenuWidget.h"

#include <QPushButton>
#include <QVBoxLayout>

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *lay = new QVBoxLayout;
    setLayout(lay);
    setMinimumSize(200, 300);
}


void MenuWidget::addButton(QPushButton *button)
{
    layout()->addWidget(button);
}
