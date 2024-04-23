#include <iostream>
#include "../include/glyphs/glyph.h"
#include "../include/glyphs/character.h"
#include "../include/glyphs/button.h"

int main() {
    std::cout << "Hello" << std::endl;
    Character c = Character(1, 1, 1, 1, 'A');
    std::cout << c << std::endl;
    c.Draw();
    c.ClearGlyph();

    Button b = Button(2, 2, 2, 2, "MyButton");
    std::cout << b << std::endl;
    std::cout << b.IsPressed() << std::endl;
    return 0;
}