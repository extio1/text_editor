#include "document/glyphs/column.h"

#include <algorithm>
#include <numeric>
#include <optional>

Column::Column(const int x, const int y, const int width, const int height)
    : GlyphContainer(x, y, width, height) {}

void Column::Remove(const GlyphPtr& ptr) {
    auto it = std::find(components.begin(), components.end(), ptr);
    if (it != components.end()) {
        Remove(it);
    }
}

void Column::Remove(GlyphContainer::GlyphList::iterator& it) {
    auto rowHeight = (*it)->GetHeight();
    it = components.erase(it);
    for (; it != components.end(); ++it) {
        auto& nextRow = (*it);
        nextRow->SetPosition({nextRow->GetPosition().x, y - rowHeight});
    }
    usedHeight -= rowHeight;
    ReDraw();
}

void Column::Insert(ColumnPtr& column) {
    auto insertPosition =
        components.empty() ? y : components.back()->GetBottomBorder();
    auto list = column->components;
    return Insert(insertPosition, std::move(list));
}

void Column::InsertBack(std::list<GlyphPtr>&& list) {
    auto insertPosition = x;
    if (!components.empty()) {
        insertPosition = components.back()->GetBottomBorder();
    }
    return Insert(insertPosition, std::move(list));
}

void Column::Insert(int insertPosition, std::list<GlyphPtr>&& itemsToInsert) {
    auto updateElements = [&](int offset) {
        for (auto& it : itemsToInsert) {
            it->SetPosition(offset, y);
            offset += it->GetHeight() + 1;
        }
    };

    int itemsToInsertHeight =
        std::accumulate(itemsToInsert.begin(), itemsToInsert.end(), 0,
                        [](auto& init, const auto& item) {
                            init += item->GetHeight();
                            return init;
                        });

    if (components.empty()) {
        updateElements(x);
        std::swap(components, itemsToInsert);
        usedHeight += itemsToInsertHeight;
        ReDraw();
        return;
    }

    auto insertionElement = std::find_if(
        components.begin(), components.end(), [&](const auto& glyph) {
            return glyph->Intersects(Point(x, insertPosition));
        });

    if ((*insertionElement)->GetBottomBorder() == insertPosition) {
        insertionElement++;
    }

    int offset = (*std::prev(insertionElement))->GetBottomBorder() + 1;
    updateElements(offset);

    components.insert(insertionElement, itemsToInsert.begin(),
                      itemsToInsert.end());

    // update rest of elements
    UpdateRestElements(insertionElement, itemsToInsertHeight);

    usedHeight += itemsToInsertHeight;
    if (usedHeight > height) {
        auto lastElement = std::find_if(
            components.begin(), components.end(), [&](const auto& element) {
                return element->GetBottomBorder() > GetBottomBorder();
            });

        GlyphContainer::GlyphList list;
        list.splice(list.begin(), components, lastElement);
    }
    ReDraw();
    return;
}

void Column::UpdateRestElements(GlyphList::iterator& it,
                                const int updateValue) {
    for (; it != components.end(); ++it) {
        const auto& currentPos = (*it)->GetPosition();
        (*it)->SetPosition(currentPos.x, currentPos.y + updateValue);
    }
}

bool Column::IsEmpty() const { return components.empty(); }
bool Column::IsFull() const {
    return usedHeight + 1 >= height;  // replace 1 with charHeight
}
int Column::GetFreeSpace() const { return height - usedHeight; }
int Column::GetUsedSpace() const { return usedHeight; }

Glyph::GlyphPtr Column::GetFirstGlyph() const {
    return components.empty() ? nullptr : components.front();
}

Glyph::GlyphPtr Column::GetLastGlyph() const {
    return components.empty() ? nullptr : components.back();
}

void Column::MoveUpRows(int height) {
    for (auto rowIt = components.begin(); rowIt != components.end(); ++rowIt) {
        auto& row = *rowIt;
        row->ClearGlyph();
        row->MoveGlyph(0, -height);
        row->Draw();
    }
}