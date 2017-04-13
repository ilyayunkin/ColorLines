/** @file
  * @author Yunkin Ilya.
  */
#include <QApplication>
#include "TetrisGame.h"
#include "Lines/ColorLinesWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TetrisGame game;
    ColorLinesWidget w(&game);
    w.show();

    return a.exec();
}
