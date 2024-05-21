#ifndef TEXT_EDITOR_PAGE_H_
#define TEXT_EDITOR_PAGE_H_

#include "column.h"
#include "glyph.h"
#include "glyph_container.h"
#include "row.h"

class Page : public GlyphContainer {
   public:
    using PagePtr = std::shared_ptr<Page>;

    // x and y can be used for saving position in document or can be ignored
    explicit Page(const int x, const int y, const int width, const int height);

    void Draw() override;

    void Insert(GlyphPtr& glyph) override;
    void InsertFront(GlyphPtr& glyph) override;
    void Remove(const GlyphPtr& glyph) override;

    std::shared_ptr<Glyph> clone() const override;

    size_t GetColumnsCount();
};

#endif  // TEXT_EDITOR_PAGE_H_