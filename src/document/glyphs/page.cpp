#include "document/glyphs/page.h"

#include <algorithm>
#include <cassert>

#include "document/document.h"
#include "utils/find_all_if.h"

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

Glyph::GlyphList Page::Select(const Glyph::GlyphPtr& area) {
    auto intersectedColumns = find_all_if(
        components.begin(), components.end(),
        [&](const auto& component) { return component->Intersects(area); });

    Glyph::GlyphList list;

    for (auto column : intersectedColumns) {
        Glyph::GlyphList glyphsFromCurrentColumn = (*column)->Select(area);
        list.insert(list.end(), glyphsFromCurrentColumn.begin(),
                    glyphsFromCurrentColumn.end());
    }
    return list;
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

std::shared_ptr<Glyph> Page::Clone() const {
    Page* copy = new Page(this->x, this->y, this->width, this->height);
    return std::make_shared<Page>(*copy);
}