#include <iostream>
#include <memory>
#include <string>

#include "document/document.h"

#include "compositor/simple_compositor/simple_compositor.h"

#include "executor/executor.h"
#include "executor/command/insert_character.h"
#include "executor/command/remove_character.h"
#include "executor/command/save_document.h"

int main() {
    auto document = std::make_shared<Document>();
    document->SetCompositor(std::make_shared<SimpleCompositor>());

    auto controller = std::make_unique<Executor>(2);

    controller->Do(std::make_shared<InsertCharacter>(*document, 0, 0, 10, 10, 'A'));
    controller->Do(std::make_shared<InsertCharacter>(*document, 10, 0, 10, 10, 'B'));
    controller->Do(std::make_shared<InsertCharacter>(*document, 20, 0, 10, 10, 'C'));
    controller->Do(std::make_shared<InsertCharacter>(*document, 30, 0, 10, 10, 'D'));
    controller->Undo();
    controller->Redo();

    controller->Do(std::make_shared<SaveDocument>(*document, "doc_save.file"));

    return 0;
}