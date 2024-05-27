#include "document/glyphs/column.h"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <optional>

#include "document/glyphs/row.h"
#include "utils/find_all_if.h"

int charHeight = 1;  // temporary!!!

Column::Column(const int x, const int y, const int width, const int height)
    : GlyphContainer(x, y, width, height) {
    Glyph::GlyphPtr firstRowPtr =
        std::make_shared<Row>(Row(x, y, width, charHeight));
    this->Add(firstRowPtr);
}

Glyph::GlyphList Column::Select(const Glyph::GlyphPtr& area) {
    auto intersectedRows = find_all_if(
        components.begin(), components.end(),
        [&](const auto& component) { return component->Intersects(area); });

    Glyph::GlyphList list;

    for (auto row : intersectedRows) {
        Glyph::GlyphList glyphsFromCurrentRow = (*row)->Select(area);
        list.insert(list.end(), glyphsFromCurrentRow.begin(),
                    glyphsFromCurrentRow.end());
    }
    return list;
}

void Column::Insert(GlyphPtr& glyph) {
    auto intersectedGlyphIt = std::find_if(
        components.begin(), components.end(),
        [&](const auto& component) { return component->Intersects(glyph); });
    assert(intersectedGlyphIt != components.end() &&
           "No suitable row for inserting");

    (*intersectedGlyphIt)->Insert(glyph);
}

void Column::Remove(const GlyphPtr& glyph) {
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
           "No suitable row for removing");

    (*intersectedGlyphIt)->Remove(glyph);
}

bool Column::IsEmpty() const { return components.empty(); }
bool Column::IsFull() const { return usedHeight >= height; }
int Column::GetFreeSpace() const { return height - usedHeight; }
int Column::GetUsedSpace() const { return usedHeight; }

std::shared_ptr<Glyph> Column::Clone() const {
    Column* copy = new Column(this->x, this->y, this->width, this->height);
    return std::make_shared<Column>(*copy);
}