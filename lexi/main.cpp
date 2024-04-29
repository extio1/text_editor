#include "mainwindow.h"

#include <QApplication>
#include <QScrollArea>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
