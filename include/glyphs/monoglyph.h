#ifndef TEXT_EDITOR_MONOGLYPH
#define TEXT_EDITOR_MONOGLYPH

#include "glyph.h"

/**
 * The class is a glyph that stores a reference to the only component to which all
 * requests are forwarded.
 */
class MonoGlyph: public Glyph {
public:

    explicit MonoGlyph(const GlyphParams params);
    ~MonoGlyph() override = default;

    void Draw(Window* window) { component->Draw(window); }
    void DrawAt(Window* window, const Point& point) { component->DrawAt(window, point); }

    void Add(std::shared_ptr<Glyph> glyph) override;
    void Insert(std::shared_ptr<Glyph> glyph, int pos) override;

    void MoveGlyph(int x, int y) override;

protected:
    std::shared_ptr<Glyph> component;
};

#endif  // TEXT_EDITOR_MONOGLYPH