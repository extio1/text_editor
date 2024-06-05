#include "executor/command/remove_character.h"

#include <utility>

#include "document/glyphs/character.h"

<<<<<<< HEAD
RemoveCharacter::RemoveCharacter(std::shared_ptr<IDocument> doc, int x, int y)
    : doc(std::move(doc)),
      character(std::make_shared<Character>(x, y, 0, 0, 0))  // Constuctor OK?
{}

void RemoveCharacter::Execute() { doc->Remove(character); }

void RemoveCharacter::Unexecute() { doc->Insert(character); }
=======
RemoveCharacter::RemoveCharacter(std::shared_ptr<IDocument> doc)
    : doc(std::move(doc))
{}

void RemoveCharacter::Execute() { character = doc->RemoveChar(); }

void RemoveCharacter::Unexecute() { doc->InsertChar(character); }
>>>>>>> origin/up-30

RemoveCharacter::~RemoveCharacter() {}