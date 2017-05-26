/** @file
  * @author Yunkin Ilya.
  */
#include <QApplication>
#include <QSharedPointer>

#include "SnakeGameBuilder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSharedPointer<AbstractColorLinesGame> gameP;
    QSharedPointer<QWidget> widgetP;

    {
        AbstractColorLinesGame *game;
        QWidget *w;
        SnakeGameBuilder b;
        b.createGame(game, w);
        gameP = QSharedPointer<AbstractColorLinesGame>(game);
        widgetP = QSharedPointer<QWidget>(w);
    }

    widgetP->show();

    return a.exec();
}
