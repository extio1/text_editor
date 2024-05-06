#include "document/document.h"

#include <cassert>
#include <algorithm>

#include "document/glyphs/glyph.h"
#include "document/glyphs/page.h"


Document::Document() {
    currentPage = std::make_shared<Page>(0, 0, pageWidth, pageHeight);
    pages.push_back(currentPage);
    visiblePages.push_back(currentPage);
}

void Document::Insert(Glyph::GlyphPtr& glyph) {
    // currentPage.Insert(glyph);
    // TO DO
    std::cout << "Document::Insert() ";
    glyph->Draw();
}

void Document::Remove(Glyph::GlyphPtr& glyph) {
    // TO DO
}

void Document::SetCurrentPage(Page::PagePtr page) {
    currentPage = std::move(page);
}

Page::PagePtr Document::GetCurrentPage() {
    return currentPage;
}

size_t Document::GetPageCount() const {
    return pages.size();
}

size_t Document::GetPageHeight() const {
    return pageHeight;
}

void Document::AddPage(const Glyph::GlyphPtr& page) {
    pages.push_back(page);
}

Page::PagePtr Document::GetNextPage(const Page* page) {
    auto currentPage = std::find_if(pages.begin(), pages.end(), [&](const auto& elem) {
        return elem.get() == page;
    });

    assert(currentPage != pages.end());

    auto nextPage = std::next(currentPage);
    if(nextPage == pages.end()) {
        return nullptr;
    }
    return std::static_pointer_cast<Page>(*nextPage);
}