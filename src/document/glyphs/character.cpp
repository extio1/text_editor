#include "document/glyphs/character.h"

Character::Character(const int x, const int y, const int width,
                     const int height, char c)
    : Glyph(x, y, width, height), symbol(c) {}

void Character::Draw() {
    std::cout << "Character::Draw() " << symbol << std::endl;
    // TO DO
}

void Character::SetChar(char c) { symbol = c; }
char Character::GetChar() const { return symbol; }

Glyph::GlyphPtr Character::GetFirstGlyph() { return nullptr; }

Glyph::GlyphPtr Character::GetNextGlyph(GlyphPtr& glyph) { return nullptr; }

std::shared_ptr<Glyph> Character::clone() const {
    Character* copy = new Character(this->x, this->y, this->width, this->height,
                                    this->symbol);
    return std::make_shared<Character>(*copy);
}