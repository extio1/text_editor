#ifndef TEXT_EDITOR_COMPOSITION
#define TEXT_EDITOR_COMPOSITION

#include <list>
#include "glyph.h"

/**
 * The class represents a complex glyph, i.e glyph that contains one or more glyphs.
 * Provides basic functionality to work with a list of Glyphs.
 */
class Composition: public Glyph {
public:
    using GlyphList = std::list<Glyph::GlyphPtr>;

    explicit Composition(const int x, const int y, const int width, const int height);
    ~Composition() override = default;

    void Draw() override;

    void Add(GlyphPtr glyph) override;
    void Insert(GlyphPtr glyph, int pos) override;
    void MoveGlyph(int x, int y);

    size_t GetGlyphPosition(const GlyphPtr& glyph);
    GlyphPtr Find(const Point& point);

protected:
    std::list<std::shared_ptr<Glyph>> components;
};

#endif  // TEXT_EDITOR_COMPOSITION