/** @file
  * @author Yunkin Ilya.
  */
#include <QApplication>

#include "SnakeGame.h"
#include "Lines/ColorLinesWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnakeGame game;
    ColorLinesWidget w(&game);
    w.setElementType(ColorLinesWidget::CIRCLE);
    w.setElementWidth(0.8);
    w.show();

    return a.exec();
}
