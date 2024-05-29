#include "document/glyphs/glyph.h"

#include <cassert>

#include "utils/point.h"

Glyph::Glyph(const int x, const int y, const int width, const int height)
    : x(x), y(y), width(width), height(height) {}

bool Glyph::Intersects(const Point& p) const noexcept {
    if (p.x >= this->x && p.x <= this->x + this->width) {
        if (p.y >= this->y && p.y <= this->y + this->height) {
            return true;
        }
    }
    return false;
}

bool Glyph::Intersects(const GlyphPtr& glyph) const {
    bool res =
        Intersects({glyph->GetPosition().x, glyph->GetPosition().y}) ||
        Intersects({glyph->GetPosition().x + glyph->GetWidth(),
                    glyph->GetPosition().y}) ||
        Intersects({glyph->GetPosition().x,
                    glyph->GetPosition().y + glyph->GetHeight()}) ||
        Intersects({glyph->GetPosition().x + glyph->GetWidth(),
                    glyph->GetPosition().y + glyph->GetHeight()})

        || glyph->Intersects({this->x, this->y}) ||
        glyph->Intersects({this->x + this->width, this->y}) ||
        glyph->Intersects({this->x, this->y + this->height}) ||
        glyph->Intersects({this->x + this->width, this->y + this->height});
    return res;
}

void Glyph::MoveGlyph(int x, int y) {
    assert((x >= -this->x && y >= -this->y) &&
           "Cannot move glyph due to these coordinates");
    SetPosition(this->x + x, this->y + y);
}

void Glyph::SetPosition(const Point& p) {
    assert((p.x >= 0 && p.y >= 0) && "Invalid position of glyph");
    this->x = p.x;
    this->y = p.y;
}

void Glyph::SetPosition(int x, int y) {
    assert((x >= 0 && y >= 0) && "Invalid position of glyph");
    this->x = x;
    this->y = y;
}

void Glyph::SetWidth(int width) {
    assert(width >= 0 && "Invalid width of glyph");
    this->width = width;
}

void Glyph::SetHeight(int height) {
    assert(height >= 0 && "Invalid height of glyph");
    this->height = height;
}

void Glyph::SetGlyphParams(const int x, const int y, const int width,
                           const int height) {
    assert((x >= 0 && y >= 0 && width >= 0 && height >= 0) &&
           "Invalid params of glyph");
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

int Glyph::GetWidth() const { return this->width; }
int Glyph::GetHeight() const { return this->height; }

Point Glyph::GetPosition() const { return {this->x, this->y}; }

int Glyph::GetBottomBorder() const noexcept { return this->y + height; }
int Glyph::GetRightBorder() const noexcept { return this->x + width; }

std::ostream& operator<<(std::ostream& os, const Glyph& glyph) {
    os << "x: " << glyph.x << " y: " << glyph.y << " width: " << glyph.width
       << " height: " << glyph.height;
    return os;
}