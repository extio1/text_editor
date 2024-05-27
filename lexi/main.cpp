#include "window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window *w = new Window();
    w->show();

    w->DrawText(3, 0, "hello");
    return a.exec();
}
