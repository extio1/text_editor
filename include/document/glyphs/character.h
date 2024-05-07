#ifndef TEXT_EDITOR_CHARACTER_H_
#define TEXT_EDITOR_CHARACTER_H_

#include "glyph.h"


/**
 * A class representing any visible or invisible symbol.
 */
class Character: public Glyph {
public:
    /**
     * @brief           Creates a character with the specified parameters and symbol. 
     * @param x         Horizontal coordinate.
     * @param x         Vertical coordinate.
     * @param width     Character width.
     * @param height    Character height.
     * @param c         Symbol.
     */
    Character(const int x, const int y, const int width, const int height, char c);
    ~Character() {}
    void Draw() override;

    void Insert(GlyphPtr, int) {}
    void Add(GlyphPtr) {}

    void SetChar(char c);
    char GetChar() const;

private:
    char symbol;
};

#endif  // TEXT_EDITOR_CHARACTER_H_