#include "document/document.h"

#include <algorithm>
#include <cassert>

#include "compositor/simple_compositor/simple_compositor.h"
#include "document/glyphs/glyph.h"
#include "document/glyphs/page.h"

Document::Document() {
    // compositor = std::make_shared<Compositor>(SimpleCompositor());
    currentPage = std::make_shared<Page>(0, 0, pageWidth, pageHeight);
    pages.push_back(currentPage);
}

void Document::Insert(Glyph::GlyphPtr& glyph) {
    std::cout << "Document::Insert() ";
    currentPage->Insert(glyph);
    // compositor.Compose();
    glyph->Draw();
}

void Document::Remove(Glyph::GlyphPtr& glyph) {
    // what if this glyph is not from current page ????
    currentPage->Remove(glyph);
}

void Document::SetCurrentPage(Page::PagePtr page) {
    currentPage = std::move(page);
}

Page::PagePtr Document::GetCurrentPage() { return currentPage; }

size_t Document::GetPageCount() const { return pages.size(); }

size_t Document::GetPageWidth() const { return pageWidth; }

size_t Document::GetPageHeight() const { return pageHeight; }

void Document::AddPage(const Glyph::GlyphPtr& page) { pages.push_back(page); }

Page::PagePtr Document::GetNextPage(const Page* page) {
    auto currentPage =
        std::find_if(pages.begin(), pages.end(),
                     [&](const auto& elem) { return elem.get() == page; });

    assert(currentPage != pages.end());

    auto nextPage = std::next(currentPage);
    if (nextPage == pages.end()) {
        return nullptr;
    }
    return std::static_pointer_cast<Page>(*nextPage);
}