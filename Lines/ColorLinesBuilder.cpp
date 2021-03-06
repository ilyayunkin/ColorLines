/** @file
  * @author Yunkin Ilya.
  */
#include "ColorLinesBuilder.h"

#include "JustAnotherLines.h"
#include "COMMON/GUI/ColorLinesWidget.h"
#include "COMMON/GUI/StatusBar.h"

#include <QVBoxLayout>

void ColorLinesBuilder::createGame(AbstractColorLinesGame *&game,
                                   QWidget *&widget)
{    
    JustAnotherLines *newGame = new JustAnotherLines;
    game = newGame;
    widget = new QWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout(widget);

    {
        StatusBar *bar = new StatusBar(game);
        mainLayout->addWidget(bar);
    }
    {
        /// Виджет с подсказкой о фишках, которые выпадут в следующий ход
        ColorLinesWidget *linesSmallWidget = new ColorLinesWidget(newGame->getAdapter());

        linesSmallWidget->setElementType(ColorLinesWidget::CIRCLE);
        linesSmallWidget->setElementWidth(0.6);
        mainLayout->addWidget(linesSmallWidget);
        linesSmallWidget->setFixedHeight(50);
    }
    {
        /// Виджет игрового поля
        ColorLinesWidget *linesWidget = new ColorLinesWidget(game);

        linesWidget->setElementType(ColorLinesWidget::CIRCLE);
        linesWidget->setElementWidth(0.6);
        mainLayout->addWidget(linesWidget);

        mainLayout->setMargin(0);
    }
}

QString ColorLinesBuilder::getName() const
{
    return "Color Lines";
}

QIcon ColorLinesBuilder::getIcon() const
{
    return QIcon(":/icons/icons/lines_ico.png");
}
