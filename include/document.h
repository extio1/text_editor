#ifndef TEXT_EDITOR_DOCUMENT_H_
#define TEXT_EDITOR_DOCUMENT_H_

#include <functional>

#include "glyphs/page.h"
#include "glyphs/glyph.h"

const int pageHeight = 1000;

class Page;

class Document {
public:
    using PagePtr = std::shared_ptr<Page>;

    explicit Document(const int x, const int y, const int width, const int height);

    void SetCurrentPage(PagePtr page);
    PagePtr GetCurrentPage();

    size_t GetPageCount() const;
    size_t GetPageHeight() const;

    void AddPage(const Glyph::GlyphPtr& page);
    PagePtr GetNextPage(const Page* page);

private:
    PagePtr currentPage;
    std::list<Glyph::GlyphPtr> visiblePages;
    std::list<Glyph::GlyphPtr> pages;
};

#endif  // TEXT_EDITOR_DOCUMENT_H_