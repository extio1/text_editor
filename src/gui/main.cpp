#include "window.h"

#include "document/document.h"

#include "compositor/simple_compositor/simple_compositor.h"

#include "executor/executor.h"
#include "executor/command/insert_character.h"
#include "executor/command/remove_character.h"
#include "executor/command/save_document.h"
#include "executor/command/load_document.h"
#include "executor/command/copy.h"
#include "executor/command/paste.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto d = std::make_shared<Document>(std::make_shared<SimpleCompositor>());
    auto document = std::dynamic_pointer_cast<IDocument>(d);
    auto controller = std::make_unique<Executor>(2);


    Window *w = new Window(nullptr, std::move(controller), document);

    w->show();

    w->DrawChar('A', 0, 0, 12);
    w->DrawChar('B', 500, 0, 12);
    w->DrawChar('C', 0, 1000, 12);
    w->DrawCursor(0, 0);
    w->DrawCursor(500, 0);
    w->DrawPage(520, 1020);
    w->DrawChar('A', 0, 0, 12);
    w->DrawChar('B', 500, 0, 12);
    w->DrawChar('C', 0, 1000, 12);
    w->DrawCursor(0, 0);
    w->DrawCursor(500, 0);

    return a.exec();
}
