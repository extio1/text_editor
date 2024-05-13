#ifndef TEXT_EDITOR_SIMPLECOMPOSITOR_H_
#define TEXT_EDITOR_SIMPLECOMPOSITOR_H_

#include <iostream>

#include "compositor/compositor.h"
#include "document/document.h"

class SimpleCompositor : public Compositor {
   public:
    explicit SimpleCompositor(int topIndent = 5, int bottomIndent = 10,
                              int leftIndent = 3, int rightIndent = 6,
                              Alignment alignment = LEFT, int lineSpacing = 5)
        : Compositor(topIndent, bottomIndent, leftIndent, rightIndent,
                     alignment, lineSpacing) {}

    ~SimpleCompositor() override = default;

    void Compose() override;

   private:
    void ComposePage(Page::PagePtr& page);
    void ComposeColumn(Glyph::GlyphPtr& column, int x, int y, int width,
                       int height);
    void ComposeRow(Glyph::GlyphPtr& row, int x, int y, int width);
    void ComposeCharacter(Glyph::GlyphPtr& character, int x, int y);

    size_t GetNestedGlyphsCount(Glyph::GlyphPtr& glyph);
    int GetNestedGlyphsWidth(Glyph::GlyphPtr& glyph);
    int GetNestedGlyphsHeight(Glyph::GlyphPtr& glyph);
};

#endif  // TEXT_EDITOR_SIMPLECOMPOSITOR_H_