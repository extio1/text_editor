#include "glyphs/utils/point.h"
#include "glyphs/glyph.h"
#include "glyphs/glyph.h"

Glyph::Glyph(const int _x, const int _y, const int _width, const int _height) : 
    x(_x), y(_y), width(_width), height(_height) {}

void Glyph::ReDraw() {
    ClearGlyph();
    Draw();
}

void Glyph::ClearGlyph() {
    std::cout << "Glyph::ClearGlyph()" << std::endl;
    // TO DO
}

bool Glyph::Intersects(const Point& p) const noexcept {
    if (p.x >= x && p.x <= x + width) {
        if (p.y >= y && p.y <= y + height) {
            return true;
        }
    }
    return false;
}

bool Glyph::Intersects(const int _x, const int _y, const int _width, const int _height) const {
    return Intersects({_x, _y}) 
        || Intersects({_x + _width, _y}) 
        || Intersects({_x, _y + _height}) 
        || Intersects({_x + _width, _y + _height});
}

void Glyph::MoveGlyph(int _x, int _y) {
    SetPosition(x + _x, y + _y);
}

void Glyph::SetPosition(const Point& p) {
    x = p.x;
    y = p.y;
}

void Glyph::SetPosition(int x, int y) {
    x = x;
    y = y;
}

void Glyph::SetGlyphParams(const int _x, const int _y, const int _width, const int _height) { 
    x = _x;
    y = _y;
    width = _width;
    height = _height;
}

int Glyph::GetWidth() const { return width; }
int Glyph::GetHeight() const { return height; }

Point Glyph::GetPosition() const { return { x, y }; }

int Glyph::GetBottomBorder() const noexcept { return y + height; }
int Glyph::GetRightBorder() const noexcept { return x + width; }

std::ostream &operator<<(std::ostream& os, const Glyph& glyph) {
    os << "x: " << glyph.x << " y: " << glyph.y << " width: " << glyph.width << " height: " << glyph.height;
    return os;
}