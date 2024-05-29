#include "window.h"
#include "menu.h"

#include "./ui_window.h"

Window::Window(QWidget *parent, std::unique_ptr<Executor> controller, std::shared_ptr<IDocument> document)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    this->document = document;
    this->controller = std::move(controller);

    this->setFixedSize(500, 1000);
    ui->setupUi(this);
    
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
    painter = new QPainter();

    vboxlayuot->addWidget(painter);
    widget->setLayout(vboxlayuot);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidget(widget);
    setCentralWidget(scrollArea);

    new Menu(this, std::move(controller), document, textEdit);
}

void Window::DrawText(int x, int y, std::string text){
    textEdit->setFocus();
    QTextCursor cursor = textEdit->textCursor();
    cursor.setPosition(x);
    cursor.setVerticalMovementX(y);
    textEdit->setTextCursor(cursor);
    //auto font = textEdit->currentFont();
    //font.setPointSize(50);
    //textEdit->setFont(font);
    cursor.insertText(QString::fromStdString(text));
}

void Window::Redraw()
{

}

/*void Window::DrawLine(int x1, int y1, int x2, int y2){

}*/

/*void Window::ClearGlyph(int x, int y, int width, int height){

}*/

void Menu::onActFileOpenTriggered()
{
    std::cout << "File open action triggered!";
}

void Menu::onActFileSaveTriggered()
{
    std::cout << "File open action triggered!";
}

void Menu::onActEditCopyTriggered()
{
    std::cout << "File open action triggered!";
}

void Menu::onActEditPasteTriggered()
{
    QRect rect;
    QTextCursor cursor = textEdit->textCursor();
    rect = textEdit->cursorRect(cursor);
    int x1, x2, y1, y2;
    rect.getCoords(&x1, &y1, &x2, &y2);
    std:: cout << "\n" << x1 << "\n";
    std:: cout <<  y1 << "\n";
    //controller->Do(std::make_shared<Paste>(document, Point(43, 5)));
}

void Menu::onActEditCancelTriggered()
{
    std::cout << "File open action triggered!";
}

void Menu::onActEditRepeatTriggered()
{
    std::cout << "File open action triggered!";
}

