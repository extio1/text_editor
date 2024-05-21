#include "document/glyphs/row.h"

#include <algorithm>
#include <cassert>
#include <numeric>

Row::Row(const int x, const int y, const int width, const int height)
    : GlyphContainer(x, y, width, height) {}

void Row::Insert(GlyphPtr& glyph) {
    if (components.empty()) {
        components.push_back(glyph);
        usedWidth += glyph->GetWidth();
        if (glyph->GetHeight() > this->height) {
            this->height = glyph->GetHeight();
        }
        return;
    }

    auto intersectedGlyphIt = std::find_if(
        components.begin(), components.end(),
        [&](const auto& component) { return component->Intersects(glyph); });

    assert(intersectedGlyphIt != components.end() &&
           "No suitable character for inserting next to");

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
    if (glyph->GetHeight() > this->height) {
        this->height = glyph->GetHeight();
    }
}

void Row::InsertFront(GlyphPtr& glyph) {
    glyph->SetPosition(Point(this->GetPosition().x, this->GetPosition().y));
    this->Insert(glyph);
}

void Row::Remove(const GlyphPtr& ptr) {
    assert(ptr != nullptr && "Cannot remove glyph by nullptr");
    auto it = std::find(components.begin(), components.end(), ptr);

    assert(it != components.end() && "No suitable character for removing");

    usedWidth -= (*it)->GetWidth();
    components.erase(it);
}

bool Row::IsEmpty() const { return components.empty(); }
bool Row::IsFull() const { return usedWidth >= width; }
int Row::GetFreeSpace() const { return width - usedWidth; }
int Row::GetUsedSpace() const { return usedWidth; }

std::shared_ptr<Glyph> Row::clone() const {
    Row* copy = new Row(this->x, this->y, this->width, this->height);
    return std::make_shared<Row>(*copy);
}