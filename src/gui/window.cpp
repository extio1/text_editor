#include "window.h"
#include "menu.h"
#include "./ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    this->setFixedSize(500, 1000);
    ui->setupUi(this);
    new Menu(this);

    addScrollArea();

}

Window::~Window()
{
    delete ui;
}

void Window::addScrollArea() {
    widget = new QWidget();
    scrollArea = new QScrollArea(this);
    vboxlayuot = new QVBoxLayout();
    textEdit = new QTextEdit();

    vboxlayuot->addWidget(textEdit);
    widget->setLayout(vboxlayuot);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidget(widget);
    setCentralWidget(scrollArea);
}

void Window::DrawText(int x, int y, std::string text){
    textEdit->setFocus();
    QTextCursor cursor = textEdit->textCursor();
    cursor.setPosition(x);
    cursor.setVerticalMovementX(y);
    textEdit->setTextCursor(cursor);
    cursor.insertText(QString::fromStdString(text));
}

/*void Window::DrawLine(int x1, int y1, int x2, int y2){

}*/

void Window::ClearGlyph(int x, int y, int width, int height){

}

