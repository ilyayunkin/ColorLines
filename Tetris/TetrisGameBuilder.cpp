/** @file
  * @author Yunkin Ilya.
  */
#include "TetrisGameBuilder.h"

#include <QVBoxLayout>

#include "TetrisGame.h"
#include "COMMON/GUI/ColorLinesWidget.h"
#include "COMMON/GUI/StatusBar.h"

void TetrisGameBuilder::createGame(AbstractColorLinesGame *&game,
                                   QWidget *&widget)
{
    TetrisGame *gameNew = new TetrisGame;
    game = gameNew;

    QWidget *w = new QWidget;
    widget = w;

    QVBoxLayout *mainLayout = new QVBoxLayout(w);

    StatusBar *bar = new StatusBar(game);
    mainLayout->addWidget(bar);

    mainLayout->addWidget(new ColorLinesWidget(game));

    mainLayout->setMargin(0);
}
