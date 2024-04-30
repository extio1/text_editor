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

    explicit MonoGlyph(GlyphPtr glyph);
    ~MonoGlyph() override = default;

    void Draw();

    void Add(std::shared_ptr<Glyph> glyph) override;
    void Insert(std::shared_ptr<Glyph> glyph, int pos) override;

protected:
    std::shared_ptr<Glyph> component;
};

#endif  // TEXT_EDITOR_MONOGLYPH_H_