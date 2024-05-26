#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>

#include "document/document.h"

#include "compositor/simple_compositor/simple_compositor.h"

#include "executor/executor.h"
#include "executor/command/insert_character.h"
#include "executor/command/remove_character.h"
#include "executor/command/save_document.h"
#include "executor/command/load_document.h"

int main() {
    auto d = std::make_shared<Document>();
    d->SetCompositor(std::make_shared<SimpleCompositor>());

    auto document = std::dynamic_pointer_cast<IDocument>(d);
    auto controller = std::make_unique<Executor>(2);

    controller->Do(std::make_shared<InsertCharacter>(document, 0, 0, 10, 10, 'A'));
    controller->Do(std::make_shared<InsertCharacter>(document, 10, 0, 10, 10, 'B'));
    controller->Do(std::make_shared<InsertCharacter>(document, 20, 0, 10, 10, 'C'));
    controller->Do(std::make_shared<InsertCharacter>(document, 30, 0, 10, 10, 'D'));

    controller->Undo();
    controller->Redo();

    std::cout << "Source: " << document << "\n";
    controller->Do(std::make_shared<SaveDocument>(document, "doc_save.file"));
    std::cout << "Saved: " << document << "\n";

    controller->Do(std::make_shared<RemoveCharacter>(document, 3, 5));
    controller->Do(std::make_shared<RemoveCharacter>(document, 13, 5));
    controller->Do(std::make_shared<RemoveCharacter>(document, 23, 5));
    controller->Do(std::make_shared<RemoveCharacter>(document, 33, 5));

    controller->Do(std::make_shared<LoadDocument>(&document, "doc_save.file"));
    std::cout << "Loaded: " << document << "\n";

    return 0;
}