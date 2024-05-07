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