#ifndef WINDOW_H_
#define WINDOW_H_

#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPoint>
#include <QTextCursor>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

    void DrawText(int x, int y, std::string text);
    //void DrawLine(int x1, int y1, int x2, int y2);
    void ClearGlyph(int x, int y, int width, int height);

    void addScrollArea();

    Ui::Window *ui;
    QScrollArea *scrollArea;
    QVBoxLayout * vboxlayuot;
    QWidget *widget;
    QTextEdit *textEdit;
};
#endif // WINDOW_H_
