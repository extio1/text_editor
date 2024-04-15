#ifndef TEXT_EDITOR_CHARACTER
#define TEXT_EDITOR_CHARACTER

#include "glyph.h"
#include "window.h"

/**
 * A class representing any visible or invisible symbol.
 */
class Character: public Glyph {
public:
    Character(const GlyphParams& params, char c): Glyph(params), symbol(c) {}
    void Draw(Window* window) override;

    void SetChar(char c) { symbol = c; }
    char GetChar() const { return symbol; }

private:
    char symbol;
};

#endif  // TEXT_EDITOR_CHARACTER