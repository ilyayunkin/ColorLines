#include <QApplication>
#include "JustAnotherLines.h"
#include "MainWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    JustAnotherLines jal;
    MainWidget w(&jal);
    w.show();

    return a.exec();
}
