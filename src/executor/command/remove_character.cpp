#include "executor/command/remove_character.h"

#include "document/glyphs/character.h"

RemoveCharacter::RemoveCharacter(IDocument& doc, int x, int y)
    : doc(doc),
      character(std::make_shared<Character>(x, y, 0, 0, 0))  // Constuctor OK?
{}

void RemoveCharacter::Execute() { doc.Remove(character); }

void RemoveCharacter::Unexecute() { doc.Insert(character); }

RemoveCharacter::~RemoveCharacter() {}