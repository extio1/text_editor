#ifndef TEXT_EDITOR_MONOGLYPH_H_
#define TEXT_EDITOR_MONOGLYPH_H_

#include "glyph.h"
#include "utils/point.h"

/**
 * The class is a glyph that stores a reference to the only component to which
 * all requests are forwarded.
 */
class MonoGlyph : public Glyph {
   public:
    /**
     * @brief           Creates a glyph that stores a single glyph inside
     * itself.
     * @param glyph     A two-dimensional point.
     */
    explicit MonoGlyph(GlyphPtr& glyph);

    Glyph::GlyphList Select(const Glyph::GlyphPtr& area) override;

    void Insert(GlyphPtr& glyph) override;
    void Remove(const GlyphPtr& glyph) override;
    void Add(GlyphPtr glyph) override;

    GlyphPtr GetFirstGlyph() override;
    GlyphPtr GetLastGlyph() override;
    GlyphPtr GetNextGlyph(GlyphPtr& glyph) override;
    GlyphPtr GetPreviousGlyph(GlyphPtr& glyph) override;

    std::shared_ptr<Glyph> Clone() const override;

   protected:
    GlyphPtr component;
};

#endif  // TEXT_EDITOR_MONOGLYPH_H_