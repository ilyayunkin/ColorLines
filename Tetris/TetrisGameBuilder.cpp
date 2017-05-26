/** @file
  * @author Yunkin Ilya.
  */
#include "TetrisGameBuilder.h"

#include "TetrisGame.h"
#include "COMMON/GUI/ColorLinesWidget.h"

void TetrisGameBuilder::createGame(AbstractColorLinesGame *&game,
                                   QWidget *&widget)
{
    TetrisGame *gameNew = new TetrisGame;
    game = gameNew;

    widget = new ColorLinesWidget(game);
}
