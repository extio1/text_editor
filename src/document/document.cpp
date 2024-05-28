#include "document/document.h"

#include <algorithm>
#include <cassert>

#include "compositor/compositor.h"
#include "compositor/simple_compositor/simple_compositor.h"
#include "document/glyphs/glyph.h"
#include "document/glyphs/page.h"

Document::Document(std::shared_ptr<Compositor> compositor) {
    currentPage = std::make_shared<Page>(0, 0, pageWidth, pageHeight);
    AddPage(currentPage);
    this->compositor = compositor;
    compositor->SetDocument(this);
    compositor->Compose();
}

void Document::SetCompositor(std::shared_ptr<Compositor> compositor) {
    this->compositor = compositor;
    compositor->SetDocument(this);
    compositor->Compose();
}

std::shared_ptr<Compositor> Document::GetCompositor() {
    return this->compositor;
}

void Document::Insert(Glyph::GlyphPtr& glyph) {
    currentPage->Insert(glyph);
    compositor->Compose();
    // glyph->Draw();
}

void Document::Remove(Glyph::GlyphPtr& glyph) {
    assert(glyph != nullptr && "Cannot remove glyph by nullptr");
    auto it = std::find(pages.begin(), pages.end(), glyph);
    if (it != pages.end()) {
        if (it != pages.begin()) pages.erase(it);
        return;
    }

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
    // if (compositor) {
    // compositor->Compose();  // page can be non-formated
    // }
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

void Document::SelectGlyphs(const Point& start, const Point& end) {
    Glyph::GlyphPtr area = std::make_shared<Column>(
        Column(start.x, start.y,
               (end.x > start.x ? end.x - start.x - 1 : end.x - start.x),
               (end.y > start.y ? end.y - start.y - 1 : end.y - start.y)));
    GlyphContainer::GlyphList list;
    Glyph::GlyphList glyphs = currentPage->Select(area);
    std::cout << "Selected glyphs:" << std::endl;
    for (auto glyph : glyphs) {
        std::cout << *glyph << std::endl;
    }

    selectedGlyphs.clear();
    for (auto& glyph : glyphs) {
        selectedGlyphs.push_back(glyph);
    }
}

Glyph::GlyphList Document::PasteGlyphs(const Point& to_point) {
    int currentX = to_point.x;
    int currentY = to_point.y;
    Glyph::GlyphPtr glyph;
    Glyph::GlyphList copiesList;
    for (auto& glyph : selectedGlyphs) {
        Glyph::GlyphPtr copy = glyph->Clone();
        copy->SetPosition(Point(currentX, currentY));  // set new position
        this->Insert(copy);
        copiesList.push_back(copy);
        currentX = copy->GetPosition().x +
                   copy->GetWidth();  // insert next glyph after this
        currentY =
            copy->GetPosition().y + 1;  // insert next glyph to the same row
    }
    // selected glyphs is not removed from selectedGlyphs, they can be pasted or
    // cut one more time
    return copiesList;
}

void Document::CutGlyphs(const Point& start, const Point& end) {
    SelectGlyphs(start, end);
    for (auto& glyph : selectedGlyphs) {
        this->Remove(glyph);
    }
}