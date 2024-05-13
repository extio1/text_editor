#include "document/glyphs/page.h"

#include <algorithm>
#include <cassert>

#include "document/document.h"

Page::Page(const int x, const int y, const int width, const int height)
    : GlyphContainer(x, y, width, height) {
    Glyph::GlyphPtr firstColumnPtr =
        std::make_shared<Column>(Column(x, y, width, height));
    Add(firstColumnPtr);
}

void Page::Draw() {
    std::cout << "Page::Draw()" << std::endl;
    GlyphContainer::Draw();
}

void Page::Insert(GlyphPtr& glyph) {
    auto intersectedGlyphIt = std::find_if(
        components.begin(), components.end(),
        [&](const auto& component) { return component->Intersects(glyph); });
    assert((intersectedGlyphIt != components.end()) &&
           "No suitable column for inserting");

    (*intersectedGlyphIt)->Insert(glyph);
}

void Page::InsertFront(GlyphPtr& glyph) {
    // TO DO
}

void Page::Remove(const GlyphPtr& glyph) {
    auto intersectedGlyphIt = std::find_if(
        components.begin(), components.end(),
        [&](const auto& component) { return component->Intersects(glyph); });
    assert(intersectedGlyphIt != components.end() &&
           "No suitable column for removing");

    (*intersectedGlyphIt)->Remove(glyph);
}

size_t Page::GetColumnsCount() { return components.size(); }