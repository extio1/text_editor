#include "document/glyphs/row.h"

#include <algorithm>
#include <numeric>

Row::Row(const int x, const int y, const int width, const int height)
    : GlyphContainer(x, y, width, height) {}

void Row::Insert(GlyphPtr& glyph) {
    if (components.empty()) {
        components.push_back(glyph);
        usedWidth += glyph->GetWidth();
        return;
    }

    auto intersectedGlyphIt = std::find_if(
        components.begin(), components.end(),
        [&](const auto& component) { return component->Intersects(glyph); });

    // if glyph is closer to the right border of intersected glyph then insert
    // it after else before
    if (abs((*intersectedGlyphIt)->GetRightBorder() - glyph->GetPosition().x) <=
        abs(((*intersectedGlyphIt)->GetRightBorder() -
             (*intersectedGlyphIt)->GetWidth()) -
            glyph->GetPosition().x)) {
        ++intersectedGlyphIt;
    }

    components.insert(intersectedGlyphIt, glyph);
    usedWidth += glyph->GetWidth();
}

void Row::Remove(const GlyphPtr& ptr) {
    auto it = std::find(components.begin(), components.end(), ptr);
    if (it != components.end()) {
        usedWidth -= (*it)->GetWidth();
        components.erase(it);
    }
}

bool Row::IsEmpty() const { return components.empty(); }
bool Row::IsFull() const { return usedWidth >= width; }
int Row::GetFreeSpace() const { return width - usedWidth; }
int Row::GetUsedSpace() const { return usedWidth; }