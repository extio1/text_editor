#ifndef TEXT_EDITOR_GLYPH_CONTAINER_H_
#define TEXT_EDITOR_GLYPH_CONTAINER_H_

#include "glyph.h"

/**
 * The class represents a complex glyph, i.e glyph that contains one or more
 * glyphs. Provides basic functionality to work with a list of Glyphs.
 */
class GlyphContainer : public Glyph {
   public:
    explicit GlyphContainer(const int x, const int y, const int width,
                            const int height);
    ~GlyphContainer() override = default;

    void Draw() override;

    virtual void Insert(GlyphPtr& glyph) = 0;
    virtual void Remove(const GlyphPtr& glyph) = 0;
    void Add(GlyphPtr glyph) override;

    void MoveGlyph(int x, int y);

    size_t GetGlyphIndex(const GlyphPtr& glyph);
    Glyph::GlyphPtr GetGlyphByIndex(int index);

    GlyphPtr GetFirstGlyph() override;
    GlyphPtr GetNextGlyph(GlyphPtr& glyph) override;

   protected:
    Glyph::GlyphList components;
};

#endif  // TEXT_EDITOR_GLYPH_CONTAINER_H_