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

    /**
     * @brief           Creates glyph with specified position and size.
     * @param x         Horizontal coordinate.
     * @param x         Vertical coordinate.
     * @param width     Glyph width.
     * @param height    Glyph height.
     */
    explicit Glyph(const int x, const int y, const int width, const int height);
    virtual ~Glyph() = default;

    /**
     * @brief           Calls a method from the GUI to render itself.
     * @param window    Window param will be added.
     */
    virtual void Draw() = 0;

    /**
     * @brief           Redraws itself.
     * @param window    Window param will be added.
     */
    virtual void ReDraw();

    /**
     * @brief           Calls a method from the GUI to clear the area occupied by the glyph.
     * @param window    Window param will be added.
     */
    void ClearGlyph();

    /**
     * @brief           Checks whether the point falls into the rectangle occupied by the glyph.
     * @param p         A two-dimensional point.
     */
    bool Intersects(const Point& p) const noexcept;

    /**
     * @brief           Checks if the glyphs have intersecting points.
     * @param glyph     Pointer to the glyph.
     */
    bool Intersects(const GlyphPtr& glyph) const;

    /**
     * @brief           Inserts by index another glyph into the glyph passed by the pointer. 
     *                  Defined only for container glyphs.
     * @param glyph     Pointer to the glyph.
     * @param index     The ordinal index of the glyph in the container.
     */
    virtual void Insert(GlyphPtr, int index) = 0;

    /**
     * @brief           Adds the glyph passed by the pointer to the end. 
     *                  Defined only for container glyphs.
     * @param glyph     Pointer to the glyph.
     */
    virtual void Add(GlyphPtr glyph) = 0;

    /**
     * @brief           Changes the position of the glyph according to the transmitted offsets. 
     * @param x         Horizontal offset.
     * @param y         Vertical offset.
     */
    virtual void MoveGlyph(int x, int y);

    void SetPosition(const Point& p);
    void SetPosition(int x, int y); 
    void SetWidth(int width);
    void SetHeight(int height);
    void SetGlyphParams(const int x, const int y, const int width, const int height);

    int GetWidth() const;
    int GetHeight() const;
    Point GetPosition() const;

    /**
     * @brief           Calculates and returns the vertical coordinate of the lower border of the glyph.
     * @return          Vertical coordinate.
     */
    int GetBottomBorder() const noexcept;

    /**
     * @brief           Calculates and returns the horizontal coordinate of the right border of the glyph.
     * @return          Horizontal coordinate.
     */
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