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

    explicit Composition(const GlyphParams params);
    ~Composition() override = default;

    void Draw(Window* window) override;
    void DrawAt(Window* window, const Point& point) override;

    void Add(std::shared_ptr<Glyph> glyph) override;
    void Insert(std::shared_ptr<Glyph> glyph, int pos) override;

    size_t GetGlyphPosition(const std::shared_ptr<Glyph>& glyph);
    std::shared_ptr<Glyph> Find(const Point& point);

    void MoveGlyph(int x, int y) override;

protected:
    std::list<std::shared_ptr<Glyph>> components;
};

#endif  // TEXT_EDITOR_COMPOSITION