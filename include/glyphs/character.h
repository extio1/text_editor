#ifndef TEXT_EDITOR_CHARACTER
#define TEXT_EDITOR_CHARACTER

#include "glyph.h"
#include "window.h"

/**
 * A class representing any visible or invisible symbol.
 */
class Character: public Glyph {
public:
    Character(const int x, const int y, const int width, const int height, char c);
    void Draw(Window* window) override;

    void SetChar(char c);
    char GetChar() const;

private:
    char symbol;
};

#endif  // TEXT_EDITOR_CHARACTER