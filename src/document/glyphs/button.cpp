#include "document/glyphs/button.h"

Button::Button(const int x, const int y, const int width, const int height,
               const std::string& name)
    : Glyph(x, y, width, height) {
    this->name = name;
}

bool Button::IsPressed() const { return isPressed; }

void Button::Draw() {
    std::cout << "Button::Draw()" << std::endl;
    // TO DO
}

Glyph::GlyphPtr Button::GetFirstGlyph() { return nullptr; }
Glyph::GlyphPtr Button::GetLastGlyph() { return nullptr; }

Glyph::GlyphPtr Button::GetNextGlyph(GlyphPtr& glyph) { return nullptr; }
Glyph::GlyphPtr Button::GetPreviousGlyph(GlyphPtr& glyph) { return nullptr; }

std::shared_ptr<Glyph> Button::Clone() const {
    Button* copy =
        new Button(this->x, this->y, this->width, this->height, this->name);
    return std::make_shared<Button>(*copy);
}