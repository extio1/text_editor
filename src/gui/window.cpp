#include "window.h"
#include "menu.h"
#include "dialog.h"

#include "./ui_window.h"

Window::Window(QWidget *parent, std::unique_ptr<Executor> controller, std::shared_ptr<IDocument> document)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    this->document = document;
    this->controller = std::move(controller);
    cursor = nullptr;

    this->setFixedSize(550, 1050);
    ui->setupUi(this);
    
    addScrollArea();
    this->installEventFilter(this);
}

Window::~Window()
{
    delete ui;
}

void Window::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A && event->modifiers() == Qt::ShiftModifier) {
        shiftPressed = true;
        controller->Do(std::make_shared<MoveCursorLeft>(document));
        qDebug() << "left";
    } else if (event->key() == Qt::Key_D && event->modifiers() == Qt::ShiftModifier){
        shiftPressed = true;
        controller->Do(std::make_shared<MoveCursorRight>(document));
        qDebug() << "right";
    } else if (event->key() == Qt::Key_C && event->modifiers() == Qt::ControlModifier)
    {
        if (!memorized.empty())
        {
            auto start = Point(memorized.front()->pos().toPoint().x(), memorized.front()->pos().toPoint().y());
            auto end = Point(memorized.back()->pos().toPoint().x(), memorized.back()->pos().toPoint().y());
            controller->Do(std::make_shared<Copy>(document, start,end));
        }
    }
    else if (event->key() == Qt::Key_V && event->modifiers() == Qt::ControlModifier)
    {
        if (cursor)
        {
            controller->Do(std::make_shared<Paste>(document,Point(cursor->pos().toPoint().x(), cursor->pos().toPoint().y())));
        }
    }
    else if (event->key() == Qt::Key_Backspace)
    {
        controller->Do(std::make_shared<RemoveCharacter>(document));
        qDebug() << "delete";   
    }
    else if (event->key() == Qt::Key_Z && event->modifiers() == Qt::ControlModifier)
    {
        controller->Undo();
        qDebug() << "undo";  
    }
    else if (event->key() == Qt::Key_Y && event->modifiers() == Qt::ControlModifier)
    {
        controller->Redo();
        qDebug() << "redo";  
    }
    else if (event->key() == Qt::Key_E && event->modifiers() == Qt::ShiftModifier)
    {
        qDebug() << "ENTER";
    }
    else if (event->key() == Qt::Key_L && event->modifiers() == Qt::ControlModifier)
    {
        InputDialog* dialog = new InputDialog(this);
        QString path;
        dialog->show();
        if (dialog->exec() == QDialog::Accepted) {
            path = dialog->getText();
            QMessageBox::information(this, "Input", "You entered: " + path);
        }
        controller->Do(std::make_shared<LoadDocument>(&document, path.toStdString()));
        qDebug() << "load file";  
    }
    else if (event->key() == Qt::Key_S && event->modifiers() == Qt::ControlModifier)
    {
        InputDialog* dialog = new InputDialog(this);
        QString path;
        dialog->show();
        if (dialog->exec() == QDialog::Accepted) {
            path = dialog->getText();
            QMessageBox::information(this, "Input", "You entered: " + path);
        }
        controller->Do(std::make_shared<SaveDocument>(document, path.toStdString()));
        qDebug() << "load file";  
    }
    else if (!event->text().isEmpty() && event->text().at(0).isPrint())
    {
        controller->Do(std::make_shared<InsertCharacter>(document,event->text().toStdString().at(0)));
    }

    QMainWindow::keyPressEvent(event); // Call base class implementation
}

void Window::addScrollArea() {
    scrollArea = new QScrollArea(this);
    
    graphicsView = new QGraphicsView();
    graphicsView->setFixedSize(520,1020);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);

    // vboxlayuot = new QVBoxLayout(graphicsView);
    // vboxlayuot->setSizeConstraint(vboxlayuot->SetNoConstraint);

    QWidget* techArea = new QWidget;
    widget = techArea;
    techArea->setObjectName("techarea");
    // techArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    techArea->setLayout(new QVBoxLayout(techArea));

    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    // scrollArea->setWidget(graphicsView);
    scrollArea->setWidget(techArea);
    techArea->layout()->addWidget(graphicsView);

    setCentralWidget(scrollArea);    
    scene->setSceneRect(520, 1020, -520, -1020);
    
    new Menu(this, std::move(controller), document, graphicsView);
}

// координата y вверху страницы равна 0, вниз увеличивается, x как обычно
void Window::DrawChar(char symbol, int x_, int y_, int size)
{     
    QString str = QString(symbol);
    QGraphicsTextItem *text = new QGraphicsTextItem(str);
    qreal x = x_;  // replace with your desired x position
    qreal y = y_;   // replace with your desired y position
    text->setPos(x, y);
    text->setFont(QFont("Arial", size));
    scene->addItem(text);
} 

// x, y - координаты верхней точки курсора
void Window::DrawCursor(int x, int y)
{
    if (cursor == nullptr) 
    {
        auto item = scene->views().first()->itemAt(QPoint(qreal(x), qreal(y)));
        auto text = static_cast<QGraphicsTextItem*>(item);
        cursor = text;
        def = text->defaultTextColor();
        text->setDefaultTextColor(QColor(255,0,0));
        std::cout << text->toPlainText().toStdString();
    }
    else 
    {
        cursor->setDefaultTextColor(def);
        auto item = scene->views().first()->itemAt(QPoint(qreal(x), qreal(y)));
        auto text = static_cast<QGraphicsTextItem*>(item);
        cursor = text;
        text->setDefaultTextColor(QColor(255,0,0));
        std::cout << text->toPlainText().toStdString();
    }
} 

// очистить все
void Window::Clear()
{
    QWidget* techArea = new QWidget;
    widget = techArea;
    techArea->setObjectName("techarea");
    // techArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    techArea->setLayout(new QVBoxLayout(techArea));

    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    // scrollArea->setWidget(graphicsView);
    scrollArea->setWidget(techArea);
    graphicsView = new QGraphicsView();
    graphicsView->setFixedSize(520,1020);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    techArea->layout()->addWidget(graphicsView);
}

// создается пустая страница где-то ниже, теперь уже ее верхний левый угол - начало координат
void Window::DrawPage(int width, int height)
{
    auto test = new QGraphicsView();
    auto scene2 = new QGraphicsScene(this);
    test->setScene(scene2);
    test->setFixedSize(width,height);
    widget->layout()->addWidget(test);
    scene = scene2;
    scene->setSceneRect(520, 1020, -520, -1020);
}

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
    /*QRect rect;
    QTextCursor cursor = textEdit->textCursor();
    rect = textEdit->cursorRect(cursor);
    int x1, x2, y1, y2;
    rect.getCoords(&x1, &y1, &x2, &y2);
    std:: cout << "\n" << x1 << "\n";
    std:: cout <<  y1 << "\n";
    //controller->Do(std::make_shared<Paste>(document, Point(43, 5)));*/
}

void Menu::onActEditCancelTriggered()
{
    std::cout << "File open action triggered!";
}

void Menu::onActEditRepeatTriggered()
{
    std::cout << "File open action triggered!";
}
