#include <iostream>
#include <memory>

#include "document/document.h"
#include "document/glyphs/button.h"
#include "document/glyphs/character.h"
#include "document/glyphs/column.h"
#include "document/glyphs/glyph.h"
#include "document/glyphs/glyph_container.h"
#include "document/glyphs/monoglyph.h"
#include "document/glyphs/page.h"
#include "document/glyphs/row.h"

#include "executor/executor.h"
#include "executor/command/insert_character.h"
#include "executor/command/remove_character.h"

#include "compositor/simple_compositor/simple_compositor.h"

int main() {
    auto document = std::make_shared<Document>();
    document->SetCompositor(std::make_shared<SimpleCompositor>());

    auto controller = std::make_unique<Executor>(5);

    controller->Do(std::make_shared<InsertCharacter>(*document, 0, 0, 10, 10, 'A'));
    controller->Do(std::make_shared<InsertCharacter>(*document, 10, 0, 10, 10, 'B'));
    controller->Do(std::make_shared<InsertCharacter>(*document, 20, 0, 10, 10, 'C'));
    controller->Undo();
    controller->Redo();

    return 0;
}