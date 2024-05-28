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


//    auto simp = new SimpleCompositor();
//    auto d = new Document(simpleCompositor);
    Window *w = new Window();

    w->show();

    w->DrawText(3, 0, "hello");


//    auto doc = new Document(simpleCompositor);

//    delete d;
//    delete simp;
    return a.exec();
}
