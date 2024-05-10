#include "document/glyphs/column.h"

#include <algorithm>
#include <numeric>
#include <optional>

Column::Column(const int x, const int y, const int width, const int height)
    : GlyphContainer(x, y, width, height) {}

void Column::Remove(const GlyphPtr& ptr) {
    auto it = std::find(components.begin(), components.end(), ptr);
    if (it != components.end()) {
        usedHeight -= (*it)->GetHeight();
        components.erase(it);
    }
}

void Column::Insert(GlyphPtr& glyph) {
    if (components.empty()) {
        components.push_back(glyph);
        usedHeight += glyph->GetHeight();
        return;
    }

    auto intersectedGlyphIt = std::find_if(
        components.begin(), components.end(),
        [&](const auto& component) { return component->Intersects(glyph); });

    int offset = 0;
    if (intersectedGlyphIt != components.begin()) {
        offset =
            std::min(abs((*intersectedGlyphIt)->GetBottomBorder() -
                         glyph->GetPosition().y),
                     abs((*std::prev(intersectedGlyphIt))->GetBottomBorder() -
                         glyph->GetPosition().y));
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

    usedHeight += glyph->GetWidth();
}

// void Column::Insert(int insertPosition, std::list<GlyphPtr>&& itemsToInsert)
// {
//     auto updateElements = [&](int offset) {
//         for (auto& it : itemsToInsert) {
//             it->SetPosition(offset, y);
//             offset += it->GetHeight() + 1;
//         }
//     };

//     int itemsToInsertHeight =
//         std::accumulate(itemsToInsert.begin(), itemsToInsert.end(), 0,
//                         [](auto& init, const auto& item) {
//                             init += item->GetHeight();
//                             return init;
//                         });

//     if (components.empty()) {
//         updateElements(x);
//         std::swap(components, itemsToInsert);
//         usedHeight += itemsToInsertHeight;
//         ReDraw();
//         return;
//     }

//     auto insertionElement = std::find_if(
//         components.begin(), components.end(), [&](const auto& glyph) {
//             return glyph->Intersects(Point(x, insertPosition));
//         });

//     if ((*insertionElement)->GetBottomBorder() == insertPosition) {
//         insertionElement++;
//     }

//     int offset = (*std::prev(insertionElement))->GetBottomBorder() + 1;
//     updateElements(offset);

//     components.insert(insertionElement, itemsToInsert.begin(),
//                       itemsToInsert.end());

//     // update rest of elements
//     UpdateRestElements(insertionElement, itemsToInsertHeight);

//     usedHeight += itemsToInsertHeight;
//     if (usedHeight > height) {
//         auto lastElement = std::find_if(
//             components.begin(), components.end(), [&](const auto& element) {
//                 return element->GetBottomBorder() > GetBottomBorder();
//             });

//         GlyphContainer::GlyphList list;
//         list.splice(list.begin(), components, lastElement);
//     }
//     ReDraw();
//     return;
// }

bool Column::IsEmpty() const { return components.empty(); }
bool Column::IsFull() const { return usedHeight >= height; }
int Column::GetFreeSpace() const { return height - usedHeight; }
int Column::GetUsedSpace() const { return usedHeight; }
