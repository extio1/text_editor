#include "executor/command/remove_character.h"

#include <utility>

#include "document/glyphs/character.h"

RemoveCharacter::RemoveCharacter(std::shared_ptr<IDocument> doc)
    : doc(std::move(doc))
{}

void RemoveCharacter::Execute() { character = doc->RemoveChar(); }

void RemoveCharacter::Unexecute() { doc->InsertChar(character); }

RemoveCharacter::~RemoveCharacter() {}