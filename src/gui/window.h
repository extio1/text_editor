#ifndef WINDOW_H_
#define WINDOW_H_

#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPoint>
#include <QTextCursor>
#include <QPainter>
#include <iostream>
#include <string>
#include <QGraphicsView>
#include <QString>
#include <QGraphicsTextItem>
#include <QColor>

#include "document/document.h"

#include "compositor/simple_compositor/simple_compositor.h"

#include "executor/executor.h"
#include "executor/command/insert_character.h"
#include "executor/command/remove_character.h"
#include "executor/command/save_document.h"
#include "executor/command/load_document.h"
#include "executor/command/copy.h"
#include "executor/command/paste.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr, std::unique_ptr<Executor> controller = nullptr, std::shared_ptr<IDocument> document = nullptr);
    ~Window();

    void DrawChar(char symbol, int x, int y, int size); // координата y вверху страницы равна 0, вниз увеличивается, x как обычно
    void DrawCursor(int x, int y); // x, y - координаты верхней точки курсора
    void Clear(); // очистить все
    void DrawPage(int width, int height);
    

    void addScrollArea();

    Ui::Window *ui;
    QScrollArea *scrollArea;
    QVBoxLayout * vboxlayuot;
    std::unique_ptr<Executor> controller;
    std::shared_ptr<IDocument> document;
    QWidget *widget;
    QPainter *painter;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QGraphicsTextItem *cursor;
    QColor def;
    char *path;
};
#endif // WINDOW_H_
