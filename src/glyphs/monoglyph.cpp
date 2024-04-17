#include "../../include/glyphs/utils/point.h"
#include "../../include/glyphs/monoglyph.h"

explicit MonoGlyph::MonoGlyph(const int x, const int y, const int width, const int height) :
                Glyph(x, y, width, height) {
    // TO DO
}

void MonoGlyph::Draw(Window* window) { 
    component->Draw(window); 
}
void MonoGlyph::DrawAt(Window* window, const Point& point) { 
    component->DrawAt(window, point); 
}