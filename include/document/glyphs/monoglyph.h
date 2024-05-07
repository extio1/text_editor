#ifndef TEXT_EDITOR_MONOGLYPH_H_
#define TEXT_EDITOR_MONOGLYPH_H_

#include "glyph.h"
#include "utils/point.h"


/**
 * The class is a glyph that stores a reference to the only component to which all
 * requests are forwarded.
 */
class MonoGlyph: public Glyph {
public:

    /**
     * @brief           Creates a glyph that stores a single glyph inside itself.
     * @param glyph     A two-dimensional point.
     */
    explicit MonoGlyph(GlyphPtr glyph);
    ~MonoGlyph() override = default;

    void Draw();

    void Add(GlyphPtr glyph) override;
    void Insert(GlyphPtr glyph, int pos) override;

protected:
    GlyphPtr component;
};

#endif  // TEXT_EDITOR_MONOGLYPH_H_