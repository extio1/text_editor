#include "document/glyphs/row.h"

#include <algorithm>
#include <numeric>


Row::Row(const int x, const int y, const int width, const int height): GlyphContainer(x, y, width, height) {}

void Row::Insert(RowPtr& row) {
    auto insertPosition = components.empty() ? x : components.back()->GetRightBorder();
    auto list = row->components;
    return Insert(insertPosition, std::move(list));
}

void Row::InsertBack(GlyphContainer::GlyphList&& list) {
    auto insertPosition = x;
    if(!components.empty()) {
        insertPosition = components.back()->GetRightBorder();
    }
    return Insert(insertPosition, std::move(list));
}

GlyphContainer::GlyphList Row::Insert(GlyphPtr& glyph) {
    GlyphContainer::GlyphList excessGlyphs; //can be placed in this row so will be replaced to the next one

    if (components.empty()) {
        if (glyph->GetWidth() <= this->GetWidth()) {
            components.push_back(glyph);
            usedWidth += glyph->GetWidth();
        } else {
            excessGlyphs.push_back(glyph);
        }
        ReDraw();
        return excessGlyphs;
    }

    auto intersectedGlyphIt = std::find_if(components.begin(), components.end(),
        [&](const auto& component) { return component->Intersects(glyph); });

    int offset = std::min((*intersectedGlyphIt)->GetRightBorder() - glyph->GetPosition().x,
                            (*std::prev(intersectedGlyphIt))->GetRightBorder() - glyph->GetPosition().x);
    if ((offset > 0) || ((*intersectedGlyphIt)->GetRightBorder() == glyph->GetPosition().x)) {
        ++intersectedGlyphIt;
    }
    glyph->SetWidth(glyph->GetWidth() + offset);

    components.insert(intersectedGlyphIt, glyph);

    UpdateRestGlyphs(intersectedGlyphIt, glyph->GetWidth());

    usedWidth += glyph->GetWidth();
    if (usedWidth > width) {
        auto firstExcessGlyphIt = std::find_if(components.begin(), components.end(),
            [&](const auto& component) { return component->GetRightBorder() > this->GetRightBorder(); });

        excessGlyphs.splice(excessGlyphs.begin(), components, firstExcessGlyphIt);
        for (auto& excessGlyph : excessGlyphs) {
            usedWidth -= excessGlyph->GetWidth();
        }
    }
    ReDraw();
    return excessGlyphs;
}

void Row::UpdateRestGlyphs(GlyphList::iterator& it, const int updateValue) {
    for(; it != components.end(); ++it) {
        const auto& currentPos = (*it)->GetPosition();
        (*it)->SetPosition(currentPos.x + updateValue, currentPos.y);
    }
}

void Row::Insert(int insertPosition, GlyphContainer::GlyphList&& itemsToInsert) {
    auto updateElements = [&](int offset){
      for (auto& it: itemsToInsert) {
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

    auto insertionElement = std::find_if(components.begin(), components.end(),
        [&](const auto& glyph) { return glyph->Intersects(Point(insertPosition, y)); });

    if ((*insertionElement)->GetRightBorder() == insertPosition) {
        insertionElement++;
    }

    int offset = (*std::prev(insertionElement))->GetRightBorder() + 1;
    updateElements(offset);

    components.insert(insertionElement, itemsToInsert.begin(), itemsToInsert.end());

    // update rest of elements
    UpdateRestGlyphs(insertionElement, itemsToInsertWidth);

    usedWidth += itemsToInsertWidth;
    if (usedWidth > width) {
        auto lastElement = std::find_if(components.begin(), components.end(),
            [&](const auto& element) { return element->GetRightBorder() > GetRightBorder(); });

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
    auto charWidth = (*it)->GetWidth();
    it = components.erase(it);
    for (; it != components.end(); ++it) {
        auto& nextChar = (*it);
        nextChar->SetPosition({nextChar->GetPosition().x - charWidth, y});
    }
    usedWidth -= charWidth;
    ReDraw();
}

bool Row::IsEmpty() const { 
    return components.empty(); 
}
bool Row::IsFull() const {
    return usedWidth + 1 >= width; //replace 1 with charWidth
}
int Row::GetFreeSpace() const { 
    return width - usedWidth; 
}
int Row::GetUsedSpace() const { 
    return usedWidth; 
}

Glyph::GlyphPtr Row::GetFirstGlyph() const {
    return components.empty() ? nullptr : components.front();
}

Glyph::GlyphPtr Row::GetLastGlyph() const {
    return components.empty() ? nullptr : components.back();
}