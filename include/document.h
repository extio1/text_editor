#ifndef TEXT_EDITOR_DOCUMENT_H_
#define TEXT_EDITOR_DOCUMENT_H_

#include <functional>

#include "glyphs/page.h"
#include "glyphs/glyph.h"

const int pageWidth = 500;
const int pageHeight = 1000;

class Document {
public:
    explicit Document();

<<<<<<< HEAD
    void Insert(Glyph::GlyphPtr glyph);
    void Remove(Glyph::GlyphPtr glyph);

=======
>>>>>>> c0e893651f2a7b6a023ecf456ff92d9c884a02b3
    void SetCurrentPage(Page::PagePtr page);
    Page::PagePtr GetCurrentPage();

    size_t GetPageCount() const;
    size_t GetPageHeight() const;

    void AddPage(const Glyph::GlyphPtr& page);
    Page::PagePtr GetNextPage(const Page* page);

private:
    Page::PagePtr currentPage;
    GlyphContainer::GlyphList visiblePages;
    GlyphContainer::GlyphList pages;
};

#endif  // TEXT_EDITOR_DOCUMENT_H_