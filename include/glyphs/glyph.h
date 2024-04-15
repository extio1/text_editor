#ifndef TEXT_EDITOR_GLYPH
#define TEXT_EDITOR_GLYPH

#include <memory>
#include <iostream>
#include "utils/glyph_params.h"
#include "window.h"

/**
 * Base class for graphical elements.
 */
class Glyph {
public:
    using GlyphPtr = std::shared_ptr<Glyph>;

    explicit Glyph(const int _x, const int _y, const int _width, const int _height) : 
    x(_x), y(_y), width(_width), height(_height) {}
    Glyph(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height) {}
    virtual ~Glyph() = default;

    virtual void Draw(Window*) = 0;
    virtual void DrawAt(Window* w, const Point& point) { Draw(w); }
    virtual void ReDraw(Window* w) {
        ClearGlyph(w);
        Draw(w);
    }
    void ClearGlyph(Window* w);

    bool Intersects(const Point& p) const noexcept {
        if (p.x >= x && p.x <= x + width) {
            if (p.y >= y && p.y <= y + height) {
                return true;
            }
        }
        return false;
    }

    bool Intersects(const int _x, const int _y, const int _width, const int _height) const {
        return Intersects({_x, _y}) 
            || Intersects({_x + _width, _y}) 
            || Intersects({_x, _y + _height}) 
            || Intersects({_x + _width, _y + _height});
    }

    virtual void Insert(GlyphPtr, int) {}
    virtual void Add(GlyphPtr glyph) {}

    void SetPosition(const Point& p) {
        x = p.x;
        y = p.y;
    }

    void SetPosition(int x, int y) {
        x = x;
        y = y;
    }

    virtual void MoveGlyph(int x, int y) {
        SetPosition(x + x, y + y);
    }

    void SetGlyphParams(const int _x, const int _y, const int _width, const int _height) { 
        x = _x;
        y = _y;
        width = _width;
        height = _height;
    }

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    Point GetPosition() const { return { x, y }; }

    int GetBottomBorder() const noexcept { return y + height; }
    int GetRightBorder() const noexcept { return x + width; }

    friend std::ostream& operator<<(std::ostream& os, const Glyph& glyph) {
        os << "x: " << glyph.x << " y: " << glyph.y << " width: " << glyph.width << " height: " << glyph.height;
        return os;
    }

protected:
    // glyph is set by the coordinates of the upper-left corner, width and height
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
};

#endif  // TEXT_EDITOR_GLYPH