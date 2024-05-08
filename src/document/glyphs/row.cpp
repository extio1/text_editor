#include "document/glyphs/row.h"

#include <algorithm>
#include <numeric>

Row::Row(const int x, const int y, const int width, const int height)
    : GlyphContainer(x, y, width, height) {}

void Row::Insert(RowPtr& row) {
    auto insertPosition =
        components.empty() ? x : components.back()->GetRightBorder();
    auto list = row->components;
    return Insert(insertPosition, std::move(list));
}

void Row::InsertBack(GlyphContainer::GlyphList&& list) {
    auto insertPosition = x;
    if (!components.empty()) {
        insertPosition = components.back()->GetRightBorder();
    }
    return Insert(insertPosition, std::move(list));
}

GlyphContainer::GlyphList Row::Insert(GlyphPtr& glyph) {
    GlyphContainer::GlyphList excessGlyphs;  // cannot be placed in this row so
                                             // will be replaced to the next one

    if (components.empty()) {
        if (glyph->GetWidth() <= this->GetWidth()) {
            components.push_back(glyph);
            usedWidth += glyph->GetWidth();
            ReDraw();
        } else {
            excessGlyphs.push_back(glyph);
        }
        return excessGlyphs;
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

    UpdateRestGlyphs(intersectedGlyphIt, glyph->GetWidth());

    usedWidth += glyph->GetWidth();
    if (usedWidth > width) {
        auto firstExcessGlyphIt = std::find_if(
            components.begin(), components.end(), [&](const auto& component) {
                return component->GetRightBorder() > this->GetRightBorder();
            });

        excessGlyphs.splice(excessGlyphs.begin(), components,
                            firstExcessGlyphIt);
        for (auto& excessGlyph : excessGlyphs) {
            usedWidth -= excessGlyph->GetWidth();
        }
    }
    ReDraw();
    return excessGlyphs;
}

void Row::UpdateRestGlyphs(GlyphList::iterator& it, const int updateValue) {
    for (; it != components.end(); ++it) {
        const auto& currentPos = (*it)->GetPosition();
        (*it)->SetPosition(currentPos.x + updateValue, currentPos.y);
    }
}

void Row::Insert(int insertPosition,
                 GlyphContainer::GlyphList&& itemsToInsert) {
    auto updateElements = [&](int offset) {
        for (auto& it : itemsToInsert) {
            it->SetPosition(offset, y);
            offset += it->GetWidth() + 1;
        }
    };

    int itemsToInsertWidth =
        std::accumulate(itemsToInsert.begin(), itemsToInsert.end(), 0,
                        [](auto& init, const auto& item) {
                            init += item->GetWidth();
                            return init;
                        });

    if (components.empty()) {
        updateElements(x);
        std::swap(components, itemsToInsert);
        usedWidth += itemsToInsertWidth;
        ReDraw();
        return;
    }

    auto insertionElement = std::find_if(
        components.begin(), components.end(), [&](const auto& glyph) {
            return glyph->Intersects(Point(insertPosition, y));
        });

    if ((*insertionElement)->GetRightBorder() == insertPosition) {
        insertionElement++;
    }

    int offset = (*std::prev(insertionElement))->GetRightBorder() + 1;
    updateElements(offset);

    components.insert(insertionElement, itemsToInsert.begin(),
                      itemsToInsert.end());

    // update rest of elements
    UpdateRestGlyphs(insertionElement, itemsToInsertWidth);

    usedWidth += itemsToInsertWidth;
    if (usedWidth > width) {
        auto lastElement = std::find_if(
            components.begin(), components.end(), [&](const auto& element) {
                return element->GetRightBorder() > GetRightBorder();
            });

        GlyphContainer::GlyphList list;
        list.splice(list.begin(), components, lastElement);
    }
    ReDraw();
    return;
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

Glyph::GlyphPtr Row::GetFirstGlyph() const {
    return components.empty() ? nullptr : components.front();
}

Glyph::GlyphPtr Row::GetLastGlyph() const {
    return components.empty() ? nullptr : components.back();
}