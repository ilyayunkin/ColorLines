#include "COMMON/GUI/ColorLinesWidget.h"
#include <QApplication>
#include <memory>

#include "ClickLinesGameBuilder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AbstractColorLinesGame *game;
    QWidget *w;
    ClickLinesGameBuilder b;
    b.createGame(game, w);
    std::unique_ptr<AbstractColorLinesGame> gameP(game);
    std::unique_ptr<QWidget> widgetP(w);

    widgetP->show();

    return a.exec();
}
