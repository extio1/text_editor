#include "../../include/glyphs/character.h"

Character::Character(const int x, const int y, const int width, const int height, char c): 
                            Glyph(x, y, width, height), symbol(c) {}

void Character::SetChar(char c) { symbol = c; }
char Character::GetChar() const { return symbol; }