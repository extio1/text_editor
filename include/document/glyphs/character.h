#ifndef TEXT_EDITOR_CHARACTER_H_
#define TEXT_EDITOR_CHARACTER_H_

#include "glyph.h"

/**
 * A class representing any visible or invisible symbol.
 */
class Character : public Glyph {
   public:
    /**
     * @brief           Creates a character with the specified parameters and
     * symbol.
     * @param x         Horizontal coordinate.
     * @param x         Vertical coordinate.
     * @param width     Character width.
     * @param height    Character height.
     * @param c         Symbol.
     */
    Character(const int x, const int y, const int width, const int height,
              char c);
    ~Character() {}
    void Draw() override;

    void Insert(GlyphPtr& glyph) override {}
    void InsertFront(GlyphPtr& glyph) override {}
    void Remove(const GlyphPtr& glyph) override {}
    void Add(GlyphPtr) override {}

    void SetChar(char c);
    char GetChar() const;

    GlyphPtr GetFirstGlyph() override;
    GlyphPtr GetNextGlyph(GlyphPtr& glyph) override;

    std::shared_ptr<Glyph> Clone() const override;

   private:
    char symbol;
};

#endif  // TEXT_EDITOR_CHARACTER_H_