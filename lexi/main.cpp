#include "window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window *w = new Window();
    w->DrawLine(1, 1, 2, 1);
    w->show();

    return a.exec();
}
