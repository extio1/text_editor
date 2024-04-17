#ifndef TEXT_EDITOR_MONOGLYPH
#define TEXT_EDITOR_MONOGLYPH

#include "glyph.h"
#include "window.h"
#include "utils/point.h"

/**
 * The class is a glyph that stores a reference to the only component to which all
 * requests are forwarded.
 */
class MonoGlyph: public Glyph {
public:

    explicit MonoGlyph(const int x, const int y, const int width, const int height);
    ~MonoGlyph() override = default;

    void Draw(Window* window);
    void DrawAt(Window* window, const Point& point);

    void Add(std::shared_ptr<Glyph> glyph) override;
    void Insert(std::shared_ptr<Glyph> glyph, int pos) override;

    void MoveGlyph(int x, int y) override;

protected:
    std::shared_ptr<Glyph> component;
};

#endif  // TEXT_EDITOR_MONOGLYPH