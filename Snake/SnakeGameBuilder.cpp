/** @file
  * @author Yunkin Ilya.
  */
#include "SnakeGameBuilder.h"

#include <QVBoxLayout>

#include "SnakeGame.h"
#include "COMMON/GUI/ColorLinesWidget.h"
#include "COMMON/GUI/StatusBar.h"

void SnakeGameBuilder::createGame(AbstractColorLinesGame *&game,
                                  QWidget *&widget)
{
    SnakeGame *newGame = new SnakeGame;
    game = newGame;

    QWidget *w = new QWidget;
    widget = w;

    QVBoxLayout *mainLayout = new QVBoxLayout(w);

    StatusBar *bar = new StatusBar(game);
    mainLayout->addWidget(bar);

    ColorLinesWidget *linesWidget = new ColorLinesWidget(newGame);
    linesWidget->setElementType(ColorLinesWidget::CIRCLE);
    linesWidget->setElementWidth(0.8);
    linesWidget->show();
    mainLayout->addWidget(linesWidget);

    mainLayout->setMargin(0);
}
