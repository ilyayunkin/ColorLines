/** @file
  * @author Yunkin Ilya.
  */
#include "MainWidget.h"

#include "ColorLinesWidget.h"

#include <QVBoxLayout>

MainWidget::MainWidget(JustAnotherLines *game, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    /// Виджет с подсказкой о фишках, которые выпадут в следующий ход
    ColorLinesWidget *linesSmallWidget = new ColorLinesWidget(game->getAdapter());

    linesSmallWidget->setElementType(ColorLinesWidget::CIRCLE);
    linesSmallWidget->setElementWidth(0.6);
    mainLayout->addWidget(linesSmallWidget);
    linesSmallWidget->setFixedHeight(50);

    /// Виджет игрового поля
    ColorLinesWidget *linesWidget = new ColorLinesWidget(game);

    linesWidget->setElementType(ColorLinesWidget::CIRCLE);
    linesWidget->setElementWidth(0.6);
    mainLayout->addWidget(linesWidget);
}

