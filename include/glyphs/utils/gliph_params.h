#include <iostream>
#include "point.h"

struct GlyphParams
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    GlyphParams() = default;
    GlyphParams(int _x, int _y, int _width, int _height): x(_x), y(_y), width(_width), height(_height) {}

    bool Intersects(const Point& p) const noexcept {
        if (p.x >= x && p.x <= x + width) {
            if (p.y >= y && p.y <= y + height) {
                return true;
            }
        }
        return false;
    }

    bool Intersects(const GlyphParams& params) const {
        return Intersects({params.x, params.y}) 
            || Intersects({params.x + params.width, params.y}) 
            || Intersects({params.x, params.y + params.height}) 
            || Intersects({params.x + params.width, params.y + params.height});
    }

    operator Point() const { return {x, y}; }

    friend std::ostream& operator<<(std::ostream& os, const GlyphParams& params)
    {
        os << "x: " << params.x << " y: " << params.y << " width: " << params.width << " height: " << params.height;
        return os;
    }
};