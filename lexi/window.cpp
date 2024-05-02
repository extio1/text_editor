#include "window.h"
#include "menu.h"
#include "./ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    new Menu(this);
    scrollArea = new QScrollArea();
    //scrollArea->setWidget(this);
}

Window::~Window()
{
    delete ui;
}
