#include <algorithm>
#include <numeric>
#include <optional>
#include "glyphs/row.h"

Row::Row(const int x, const int y, const int width, const int height): Composition(x, y, width, height) {}

Row::Row(const int x, const int y, const int width, const int height, Composition::GlyphList&& list):
    Composition(x, y, width, height){
    Insert(0, std::move(list));
}

void Row::Remove(const GlyphPtr& ptr) {
    auto it = std::find(components.begin(), components.end(), ptr);
    if(it != components.end()) {
        Remove(it);
    }
}

void Row::Remove(Composition::GlyphList::iterator& it) {
    auto charWidth = (*it)->GetWidth();
    it = components.erase(it);
    for(; it != components.end(); ++it) {
        auto& nextChar = (*it);
        nextChar->SetPosition({nextChar->GetPosition().x - charWidth, y});
    }
    usedWidth -= charWidth;
    ReDraw();
}

void Row::Insert(RowPtr& row) {
    auto insertPosition = components.empty() ? x : components.back()->GetRightBorder();
    auto list = row->components;
    return Insert(insertPosition, std::move(list));
}

void Row::InsertBack(std::list<GlyphPtr>&& list) {
    auto insertPosition = x;
    if(!components.empty()) {
        insertPosition = components.back()->GetRightBorder();
    }
    return Insert(insertPosition, std::move(list));
}

void Row::Insert(size_t insertPosition, std::list<GlyphPtr>&& itemsToInsert) {
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
    UpdateRestElements(insertionElement, itemsToInsertWidth);

    usedWidth += itemsToInsertWidth;
    if (usedWidth > width) {
        auto lastElement = std::find_if(components.begin(), components.end(),
            [&](const auto& element) { return element->GetRightBorder() > GetRightBorder(); });

        Composition::GlyphList list;
        list.splice(list.begin(), components, lastElement);
    }
    ReDraw();
    return;
}

void Row::UpdateRestElements(GlyphList::iterator& it, const int updateValue) {
    for(; it != components.end(); ++it) {
        const auto& currentPos = (*it)->GetPosition();
        (*it)->SetPosition(currentPos.x + updateValue, currentPos.y);
    }
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