/** @file
  * @author Yunkin Ilya.
  */
#include <QApplication>
#include <memory>

#include "ColorLinesBuilder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AbstractColorLinesGame *game;
    QWidget *w;
    ColorLinesBuilder b;
    b.createGame(game, w);
    std::unique_ptr<AbstractColorLinesGame> gameP(game);
    std::unique_ptr<QWidget> widgetP(w);

    widgetP->show();

    return a.exec();
}
