#include "glyphs/button.h" 


Button::Button(const int _x, const int _y, const int _width, const int _height, const std::string& _name): 
        Glyph(_x, _y, _width, _height) {
    name = _name;
}

bool Button::IsPressed() const { 
    return isPressed; 
}

void Button::Draw() {
    std::cout << "Button::Draw()" << std::endl;
    // TO DO
}