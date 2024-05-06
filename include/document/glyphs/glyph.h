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

    explicit Glyph(const int x, const int y, const int width, const int height);
    virtual ~Glyph() = default;

    virtual void Draw() = 0;
    virtual void ReDraw();
    void ClearGlyph();

    bool Intersects(const Point& p) const noexcept;
    bool Intersects(const GlyphPtr& glyph) const;

    virtual void Insert(GlyphPtr, int) = 0;
    virtual void Add(GlyphPtr glyph) = 0;
    virtual void MoveGlyph(int x, int y);

    void SetPosition(const Point& p);
    void SetPosition(int x, int y); 
    void SetWidth(int width);
    void SetHeight(int height);
    void SetGlyphParams(const int x, const int y, const int width, const int height);

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