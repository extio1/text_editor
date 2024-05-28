#include "executor/command/insert_character.h"

#include <utility>

#include "document/glyphs/character.h"

InsertCharacter::InsertCharacter(std::shared_ptr<IDocument> doc, int x, int y, int width,
                                 int height, char symbol)
    : doc(std::move(doc)),
      character(std::make_shared<Character>(x, y, width, height, symbol))
{}

void InsertCharacter::Execute() { doc->Insert(character); }

void InsertCharacter::Unexecute() { doc->Remove(character); }

InsertCharacter::~InsertCharacter() {}