#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "document/glyphs/page.h"
BOOST_CLASS_EXPORT_IMPLEMENT(Page)

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
BOOST_CLASS_EXPORT_IMPLEMENT(Page)

#include <algorithm>
#include <cassert>

#include "document/document.h"
#include "document/glyphs/column.h"
#include "utils/find_all_if.h"
#include "document/glyphs/column.h"

Page::Page(const int x, const int y, const int width, const int height)
    : GlyphContainer(x, y, width, height) {
    Glyph::GlyphPtr firstColumnPtr =
        std::make_shared<Column>(Column(x, y, width, height));
    Add(firstColumnPtr);
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

void Page::Remove(const GlyphPtr& glyph) {
    assert(glyph != nullptr && "Cannot remove glyph by nullptr");
    auto it = std::find(components.begin(), components.end(), glyph);
    if (it != components.end()) {
        if (it != components.begin()) components.erase(it);
        return;
    }

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