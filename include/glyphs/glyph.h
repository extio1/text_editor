#ifndef TEXT_EDITOR_GLYPH_H_
#define TEXT_EDITOR_GLYPH_H_

#include <memory>
#include <iostream>
#include "utils/point.h"

/**
 * Base class for graphical elements.
 */
class Glyph {
public:
    using GlyphPtr = std::shared_ptr<Glyph>;

    explicit Glyph(const int _x, const int _y, const int _width, const int _height);
    virtual ~Glyph() = default;

    virtual void Draw() = 0;
    virtual void ReDraw();
    void ClearGlyph();

    bool Intersects(const Point& p) const noexcept;
    bool Intersects(const int _x, const int _y, const int _width, const int _height) const;

    virtual void Insert(GlyphPtr, int) = 0;
    virtual void Add(GlyphPtr glyph) = 0;
    virtual void MoveGlyph(int x, int y);

    void SetPosition(const Point& p);
    void SetPosition(int x, int y); 
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

#endif  // TEXT_EDITOR_GLYPH_H_