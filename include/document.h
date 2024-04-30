#ifndef TEXT_EDITOR_DOCUMENT_H_
#define TEXT_EDITOR_DOCUMENT_H_

#include <functional>

#include "glyphs/page.h"
#include "glyphs/glyph.h"

const int pageHeight = 1000;

class Page;

class Document {
    using PagePtr = std::shared_ptr<Page>;

public:
    explicit Document(const int x, const int y, const int width, const int height);

    void SetCurrentPage(std::shared_ptr<Page> page);
    Document::PagePtr GetCurrentPage();

    size_t GetPageCount() const;
    size_t GetPageHeight() const;

    void AddPage(const Glyph::GlyphPtr& page);
    PagePtr GetNextPage(const Page* page);

private:
    std::shared_ptr<Page> currentPage;
    std::list<Glyph::GlyphPtr> visiblePages;
    std::list<Glyph::GlyphPtr> pages;
};

#endif  // TEXT_EDITOR_DOCUMENT_H_