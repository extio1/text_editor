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

    int offset = 0;
    if (intersectedGlyphIt != components.begin()) {
        offset =
            std::min(abs((*intersectedGlyphIt)->GetRightBorder() -
                         glyph->GetPosition().x),
                     abs((*std::prev(intersectedGlyphIt))->GetRightBorder() -
                         glyph->GetPosition().x));
    } else {
        offset = std::min(abs((*intersectedGlyphIt)->GetRightBorder() -
                              glyph->GetPosition().x),
                          abs(((*intersectedGlyphIt)->GetRightBorder() -
                               (*intersectedGlyphIt)->GetWidth()) -
                              glyph->GetPosition().x));
    }
    if ((offset > 0) ||
        ((*intersectedGlyphIt)->GetRightBorder() == glyph->GetPosition().x)) {
        ++intersectedGlyphIt;
    }
    glyph->SetPosition(glyph->GetPosition().x + offset, glyph->GetPosition().y);

    components.insert(intersectedGlyphIt, glyph);

    usedWidth += glyph->GetWidth();
}

void Row::Remove(const GlyphPtr& ptr) {
    auto it = std::find(components.begin(), components.end(), ptr);
    if (it != components.end()) {
        Remove(it);
    }
}

void Row::Remove(GlyphContainer::GlyphList::iterator& it) {
    auto glyphWidth = (*it)->GetWidth();
    it = components.erase(
        it);  // returns iterator following the last removed element
    for (; it != components.end(); ++it) {
        auto& nextGlyph = (*it);
        nextGlyph->SetPosition({nextGlyph->GetPosition().x - glyphWidth,
                                nextGlyph->GetPosition().y});
    }
    usedWidth -= glyphWidth;
    ReDraw();
}

bool Row::IsEmpty() const { return components.empty(); }
bool Row::IsFull() const { return usedWidth >= width; }
int Row::GetFreeSpace() const { return width - usedWidth; }
int Row::GetUsedSpace() const { return usedWidth; }