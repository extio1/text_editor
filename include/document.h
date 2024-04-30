#ifndef TEXT_EDITOR_DOCUMENT_H_
#define TEXT_EDITOR_DOCUMENT_H_

#include <functional>

#include "glyphs/page.h"
#include "glyphs/glyph.h"

const int pageWidth = 500;
const int pageHeight = 1000;

class Page;

class Document {
public:
    using PagePtr = std::shared_ptr<Page>;

    explicit Document();

    void SetCurrentPage(PagePtr page);
    PagePtr GetCurrentPage();

    size_t GetPageCount() const;
    size_t GetPageHeight() const;

    void AddPage(const Glyph::GlyphPtr& page);
    PagePtr GetNextPage(const Page* page);

private:
    PagePtr currentPage;
    Composition::GlyphList visiblePages;
    Composition::GlyphList pages;
};

#endif  // TEXT_EDITOR_DOCUMENT_H_