#include "document/document.h"

#include <algorithm>
#include <cassert>

#include "compositor/compositor.h"
#include "compositor/simple_compositor/simple_compositor.h"
#include "document/glyphs/glyph.h"
#include "document/glyphs/page.h"

Document::Document() {
    currentPage = std::make_shared<Page>(0, 0, pageWidth, pageHeight);
    AddPage(currentPage);
}

void Document::SetCompositor(std::shared_ptr<Compositor> compositor) {
    this->compositor = compositor;
    compositor->SetDocument(this);
    compositor->Compose();
}

void Document::Insert(Glyph::GlyphPtr& glyph) {
    std::cout << "Document::Insert()" << std::endl;
    currentPage->Insert(glyph);
    compositor->Compose();
    // glyph->Draw();
}

void Document::Remove(Glyph::GlyphPtr& glyph) {
    // what if this glyph is not from current page ???? glyph won't be found and
    // assertion will failed
    std::cout << std::endl;
    assert(glyph != nullptr && "Cannot remove glyph by nullptr");
    currentPage->Remove(glyph);
    compositor->Compose();
}

void Document::SetCurrentPage(Page::PagePtr page) {
    currentPage = std::move(page);
}

Page::PagePtr Document::GetCurrentPage() { return currentPage; }

size_t Document::GetPagesCount() const { return pages.size(); }

size_t Document::GetPageWidth() const { return pageWidth; }

size_t Document::GetPageHeight() const { return pageHeight; }

void Document::AddPage(const Page::PagePtr& page) {
    pages.push_back(page);
    if (compositor) {
        compositor->Compose();  // page can be non-formated
    }
}

Page::PagePtr Document::GetFirstPage() { return *(pages.begin()); }

Page::PagePtr Document::GetNextPage(const Page::PagePtr& pagePtr) {
    auto currentPage =
        std::find_if(pages.begin(), pages.end(),
                     [&](const auto& elem) { return elem == pagePtr; });

    assert(currentPage != pages.end());

    auto nextPage = std::next(currentPage);
    if (nextPage == pages.end()) {
        return nullptr;
    }
    return std::static_pointer_cast<Page>(*nextPage);
}

void Document::SelectGlyphs(GlyphContainer::GlyphList& glyphs) {
    selectedGlyphs.clear();
    for (auto& glyph : glyphs) {
        selectedGlyphs.push_back(glyph);
    }
}

void Document::PasteGlyphs(int x, int y) {
    // TO DO
}

void Document::CutGlyphs(GlyphContainer::GlyphList& glyphs) {
    // TO DO
}