#include <memory>
#include <iostream>
#include "utils/glyph_params.h"

/**
 * Base class for graphical elements.
 */
class Glyph {
public:
    explicit Glyph(const GlyphParams& _params) : params(_params) {}
    Glyph(int x, int y, int width, int height) : params({x, y, width, height}) {}
    virtual ~Glyph() = default;

    virtual void Draw(Window*) = 0;
    virtual void ReDraw(Window* w) {
        ClearGlyph(w);
        Draw(w);
    }
    void ClearGlyph(Window* w);

    bool Intersects(const Point& p) { 
        return params.Intersects(p); 
    }

    virtual void Insert(std::shared_ptr<Glyph>, int) {}
    virtual void Add(std::shared_ptr<Glyph> glyph) {}

    void SetPosition(const Point& p) {
        params.x = p.x;
        params.y = p.y;
    }

    void SetPosition(int x, int y) {
        params.x = x;
        params.y = y;
    }

    virtual void MoveGlyph(int x, int y) {
        SetPosition(params.x + x, params.y + y);
    }

    void SetGlyphParams(const GlyphParams& _params) { params = _params; }
    const GlyphParams& GetGlyphParams() const { return params; }

    int GetWidth() const { return params.width; }
    int GetHeight() const { return params.height; }

    Point GetPosition() const { return { params.x, params.y }; }

    int GetBottomBorder() const noexcept { return params.y + params.height; }
    int GetRightBorder() const noexcept { return params.x + params.width; }

protected:
    // glyph is set by the coordinates of the upper-left corner, width and height
    GlyphParams params;
};
