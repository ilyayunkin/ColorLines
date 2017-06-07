#include "COMMON/GUI/ColorLinesWidget.h"
#include <QApplication>
#include "ClickLinesGameBuilder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSharedPointer<AbstractColorLinesGame> gameP;
    QSharedPointer<QWidget> widgetP;

    {
        AbstractColorLinesGame *game;
        QWidget *w;
        ClickLinesGameBuilder b;
        b.createGame(game, w);
        gameP = QSharedPointer<AbstractColorLinesGame>(game);
        widgetP = QSharedPointer<QWidget>(w);
    }

    widgetP->show();

    return a.exec();
}
