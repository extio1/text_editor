#include "executor/command/remove_character.h"

#include <utility>

#include "document/glyphs/character.h"

RemoveCharacter::RemoveCharacter(std::shared_ptr<IDocument> doc, int x, int y)
    : doc(std::move(doc)),
      character(std::make_shared<Character>(x, y, 0, 0, 0))  // Constuctor OK?
{}

void RemoveCharacter::Execute() { doc->Remove(character); }

void RemoveCharacter::Unexecute() { doc->Insert(character); }

RemoveCharacter::~RemoveCharacter() {}