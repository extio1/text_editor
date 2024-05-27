#ifndef TEXT_EDITOR_SIMPLECOMPOSITOR_H_
#define TEXT_EDITOR_SIMPLECOMPOSITOR_H_

#include <iostream>
#include <boost/serialization/export.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include "compositor/compositor.h"
#include "document/document.h"

class SimpleCompositor : public Compositor {
   public:
    explicit SimpleCompositor()
        : Compositor(5, 10, 3, 6,
                     LEFT, 5) {}

    explicit SimpleCompositor(int topIndent, int bottomIndent,
                              int leftIndent, int rightIndent,
                              Alignment alignment, int lineSpacing)
        : Compositor(topIndent, bottomIndent, leftIndent, rightIndent,
                     alignment, lineSpacing) {}

    ~SimpleCompositor() override = default;

    void Compose() override;

   private:
    void ComposePage(Page::PagePtr& page, GlyphContainer::GlyphList& list);
    void ComposeColumn(Glyph::GlyphPtr& column, int x, int y, int width,
                       int height, GlyphContainer::GlyphList& list);
    void ComposeRow(Glyph::GlyphPtr& row, int x, int y, int width,
                    GlyphContainer::GlyphList& list);
    void ComposeCharacter(Glyph::GlyphPtr& character, int x, int y);

    size_t GetNestedGlyphsCount(Glyph::GlyphPtr& glyph);
    int GetNestedGlyphsWidth(Glyph::GlyphPtr& glyph);
    int GetNestedGlyphsHeight(Glyph::GlyphPtr& glyph);

    GlyphContainer::GlyphList CutAllCharacters();

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        std::cout << "0 SimpleCompositor\n";
        ar & boost::serialization::base_object<Compositor>(*this);
        std::cout << "1 SimpleCompositor\n";
    }
};
BOOST_CLASS_EXPORT_KEY(SimpleCompositor)

#endif  // TEXT_EDITOR_SIMPLECOMPOSITOR_H_