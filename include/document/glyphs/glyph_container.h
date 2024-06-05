#ifndef TEXT_EDITOR_GLYPH_CONTAINER_H_
#define TEXT_EDITOR_GLYPH_CONTAINER_H_

#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/list.hpp>

#include "glyph.h"

/**
 * The class represents a complex glyph, i.e glyph that contains one or more
 * glyphs. Provides basic functionality to work with a list of Glyphs.
 */
class GlyphContainer : public Glyph {
   public:
    explicit GlyphContainer(const int x, const int y, const int width,
                            const int height);
    ~GlyphContainer() override = default;

    virtual void Insert(GlyphPtr& glyph) = 0;
    virtual void Remove(const GlyphPtr& glyph) = 0;
    void Add(GlyphPtr glyph) override;

    void MoveGlyph(int x, int y);

    size_t GetGlyphIndex(const GlyphPtr& glyph);
    Glyph::GlyphPtr GetGlyphByIndex(int index);

    GlyphPtr GetFirstGlyph() override;
    Glyph::GlyphPtr GetLastGlyph() override;
    GlyphPtr GetNextGlyph(GlyphPtr& glyph) override;
    GlyphPtr GetPreviousGlyph(GlyphPtr& glyph) override;

   protected:
    Glyph::GlyphList components;
    explicit GlyphContainer() {}

   private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        std::cout << "0 GlyphContainer\n";
        ar& boost::serialization::base_object<Glyph>(*this);
        ar & components;
        std::cout << "1 GlyphContainer\n";
    }
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(GlyphContainer)

#endif  // TEXT_EDITOR_GLYPH_CONTAINER_H_