#ifndef TEXT_EDITOR_PAGE_H_
#define TEXT_EDITOR_PAGE_H_

#include "column.h"
#include "glyph.h"
#include "glyph_container.h"
#include "row.h"

class Page : public GlyphContainer {
   public:
    using PagePtr = std::shared_ptr<Page>;

    explicit Page(const int x, const int y, const int width, const int height);

    void Draw() override;

    void Insert(GlyphPtr& glyph);
    void Remove(const GlyphPtr& glyph) override;
};

#endif  // TEXT_EDITOR_PAGE_H_