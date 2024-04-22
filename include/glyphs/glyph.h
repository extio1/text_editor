#ifndef TEXT_EDITOR_GLYPH
#define TEXT_EDITOR_GLYPH

#include <memory>
#include <iostream>
#include "window.h"
#include "utils/point.h"

/**
 * Base class for graphical elements.
 */
class Glyph {
public:
    using GlyphPtr = std::shared_ptr<Glyph>;

    explicit Glyph(const int _x, const int _y, const int _width, const int _height);
    Glyph(int _x, int _y, int _width, int _height);
    virtual ~Glyph() = default;

    virtual void Draw(Window*) = 0;
    virtual void DrawAt(Window* w, const Point& point);
    virtual void ReDraw(Window* w);
    void ClearGlyph(Window* w);

    bool Intersects(const Point& p) const noexcept;

    bool Intersects(const int _x, const int _y, const int _width, const int _height) const;

    virtual void Insert(GlyphPtr, int) = 0;
    virtual void Add(GlyphPtr glyph) = 0;

    void SetPosition(const Point& p);

    void SetPosition(int x, int y);

    virtual void MoveGlyph(int x, int y);

    void SetGlyphParams(const int _x, const int _y, const int _width, const int _height);

    int GetWidth() const;
    int GetHeight() const;

    Point GetPosition() const;

    int GetBottomBorder() const noexcept;
    int GetRightBorder() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Glyph& glyph);

protected:
    // glyph is set by the coordinates of the upper-left corner, width and height
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
};

#endif  // TEXT_EDITOR_GLYPH