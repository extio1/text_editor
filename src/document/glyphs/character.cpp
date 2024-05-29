#include "document/glyphs/character.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
BOOST_CLASS_EXPORT_IMPLEMENT(Character)

Character::Character(const int x, const int y, const int width,
                     const int height, char c)
    : Glyph(x, y, width, height), symbol(c) {}

void Character::SetChar(char c) { symbol = c; }
char Character::GetChar() const { return symbol; }

Glyph::GlyphPtr Character::GetFirstGlyph() { return nullptr; }
Glyph::GlyphPtr Character::GetLastGlyph() { return nullptr; }

Glyph::GlyphPtr Character::GetNextGlyph(GlyphPtr& glyph) { return nullptr; }
Glyph::GlyphPtr Character::GetPreviousGlyph(GlyphPtr& glyph) { return nullptr; }

std::shared_ptr<Glyph> Character::Clone() const {
    Character* copy = new Character(this->x, this->y, this->width, this->height,
                                    this->symbol);
    return std::make_shared<Character>(*copy);
}

std::ostream& operator<<(std::ostream& os, const Character& character) {
    os << "x: " << character.x << " y: " << character.y
       << " width: " << character.width << " height: " << character.height
       << " symbol: " << character.symbol << std::endl;
    return os;
}