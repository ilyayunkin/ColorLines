#include "ColorLinesMultigameWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ColorLinesMultigameWidget w;
    w.show();

    return a.exec();
}
