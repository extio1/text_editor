#ifndef TEXT_EDITOR_CHARACTER_H_
#define TEXT_EDITOR_CHARACTER_H_

#include "glyph.h"

/**
 * A class representing any visible or invisible symbol.
 */
class Character : public Glyph {
   public:
    using CharPtr = std::shared_ptr<Character>;
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

    Glyph::GlyphList Select(const Glyph::GlyphPtr& area) override {}

    void Insert(GlyphPtr& glyph) override {}
    void Remove(const GlyphPtr& glyph) override {}
    void Add(GlyphPtr) override {}

    void SetChar(char c);
    char GetChar() const;

    GlyphPtr GetFirstGlyph() override;
    GlyphPtr GetLastGlyph() override;
    GlyphPtr GetNextGlyph(GlyphPtr& glyph) override;
    GlyphPtr GetPreviousGlyph(GlyphPtr& glyph) override;

    std::shared_ptr<Glyph> Clone() const override;

    friend std::ostream& operator<<(std::ostream& os,
                                    const Character& character);

   private:
    char symbol;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        std::cout << "0 Character\n";
        ar& boost::serialization::base_object<Glyph>(*this);
        ar & symbol;
        std::cout << "1 Character\n";
    }
    explicit Character() {}
};
BOOST_CLASS_EXPORT_KEY(Character)

#endif  // TEXT_EDITOR_CHARACTER_H_