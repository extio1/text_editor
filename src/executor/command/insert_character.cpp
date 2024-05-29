#include "executor/command/insert_character.h"

#include <utility>

#include "document/glyphs/character.h"

InsertCharacter::InsertCharacter(std::shared_ptr<IDocument> doc, char symbol)
    : doc(std::move(doc)),
      character(symbol)
{}

void InsertCharacter::Execute() { doc->InsertChar(character); }

void InsertCharacter::Unexecute() { (void) doc->RemoveChar(); }

InsertCharacter::~InsertCharacter() {}