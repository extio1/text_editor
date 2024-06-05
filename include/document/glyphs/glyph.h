#ifndef TEXT_EDITOR_GLYPH_H_
#define TEXT_EDITOR_GLYPH_H_

#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <iostream>
<<<<<<< HEAD
#include <boost/serialization/export.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/shared_ptr.hpp>
=======
>>>>>>> origin/up-30

#include "utils/point.h"

/**
 * Base class for graphical elements.
 */
class Glyph {
   public:
    using GlyphPtr = std::shared_ptr<Glyph>;
    using GlyphList = std::list<Glyph::GlyphPtr>;

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
     * @brief           Checks whether the point falls into the rectangle
     * occupied by the glyph.
     * @param p         A two-dimensional point.
     */
    bool Intersects(const Point& p) const noexcept;

    /**
     * @brief           Checks if the glyphs have intersecting points.
     * @param glyph     Pointer to the glyph.
     */
    bool Intersects(const GlyphPtr& glyph) const;

    virtual GlyphList Select(const Glyph::GlyphPtr& area) = 0;

    /**
     * @brief           Inserts by index another glyph into the glyph passed by
     * the pointer.
     * @param glyph     Pointer to the glyph.
     */
    virtual void Insert(GlyphPtr& glyph) = 0;

    /**
     * @brief           Removes the glyph passed by the pointer from the
     * document.
     * @param glyph     Pointer to the glyph.
     */
    virtual void Remove(const GlyphPtr& glyph) = 0;

    /**
     * @brief           Adds the glyph passed by the pointer to the end.
     * @param glyph     Pointer to the glyph.
     */
    virtual void Add(GlyphPtr glyph) = 0;

    /**
     * @brief           Changes the position of the glyph according to the
     * transmitted offsets.
     * @param x         Horizontal offset.
     * @param y         Vertical offset.
     */
    virtual void MoveGlyph(int x, int y);

    virtual GlyphPtr GetFirstGlyph() = 0;
    virtual Glyph::GlyphPtr GetLastGlyph() = 0;
    virtual GlyphPtr GetNextGlyph(GlyphPtr& glyph) = 0;
    virtual GlyphPtr GetPreviousGlyph(GlyphPtr& glyph) = 0;

    /**
     * @brief           Creates a copy of the glyph and wraps it in a smart
     * pointer.
     * @return          Shared pointer to the copy of glyph.
     */
    virtual std::shared_ptr<Glyph> Clone() const = 0;

    void SetPosition(const Point& p);
    void SetPosition(int x, int y);
    void SetWidth(int width);
    void SetHeight(int height);
    void SetGlyphParams(const int x, const int y, const int width,
                        const int height);

    int GetWidth() const;
    int GetHeight() const;
    Point GetPosition() const;

    /**
     * @brief           Calculates and returns the vertical coordinate of the
     * lower border of the glyph.
     * @return          Vertical coordinate.
     */
    int GetBottomBorder() const noexcept;

    /**
     * @brief           Calculates and returns the horizontal coordinate of the
     * right border of the glyph.
     * @return          Horizontal coordinate.
     */
    int GetRightBorder() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Glyph& glyph);

   protected:
    // glyph is set by the coordinates of the upper-left corner, width and
    // height
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    explicit Glyph() {}

<<<<<<< HEAD
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
=======
   private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
>>>>>>> origin/up-30
        std::cout << "0 Glyph\n";
        ar & x & y & width & height;
        std::cout << "1 Glyph\n";
    }
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Glyph)

#endif  // TEXT_EDITOR_GLYPH_H_