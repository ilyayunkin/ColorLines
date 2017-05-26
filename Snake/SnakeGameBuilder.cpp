/** @file
  * @author Yunkin Ilya.
  */
#include "SnakeGameBuilder.h"

#include "SnakeGame.h"
#include "COMMON/GUI/ColorLinesWidget.h"

void SnakeGameBuilder::createGame(AbstractColorLinesGame *&game,
                                  QWidget *&widget)
{
    SnakeGame *newGame = new SnakeGame;
    game = newGame;

    ColorLinesWidget *w = new ColorLinesWidget(newGame);
    w->setElementType(ColorLinesWidget::CIRCLE);
    w->setElementWidth(0.8);
    w->show();

    widget = w;
}
