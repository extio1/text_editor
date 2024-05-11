#include "executor/command/remove_character.h"

#include "document/glyphs/character.h"

RemoveCharacter::RemoveCharacter(Document& doc, int x, int y)
    : character(std::make_shared<Character>(x, y, 0, 0, 0)),  // Constuctor OK?
      doc(doc) {}

void RemoveCharacter::Execute() { doc.Remove(character); }

void RemoveCharacter::Unexecute() { doc.Insert(character); }

RemoveCharacter::~RemoveCharacter() {}