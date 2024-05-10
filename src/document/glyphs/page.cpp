#include "document/glyphs/page.h"

#include <algorithm>
#include <cassert>

#include "document/document.h"

int charHeight = 1;  // temporary!!!

Page::Page(const int x, const int y, const int width, const int height)
    : GlyphContainer(x, y, width, height) {
    Glyph::GlyphPtr firstColumnPtr =
        std::make_shared<Column>(Column(x, y, width, height));
    Insert(firstColumnPtr);
    Glyph::GlyphPtr firstRowPtr =
        std::make_shared<Row>(Row(x, y, width, charHeight));
    firstColumnPtr->Insert(firstRowPtr);
}

void Page::Draw() {
    std::cout << "Page::Draw()" << std::endl;
    GlyphContainer::Draw();
}

void Page::Insert(GlyphPtr& glyph) {
    auto intersectedGlyphIt = std::find_if(
        components.begin(), components.end(),
        [&](const auto& component) { return component->Intersects(glyph); });
    assert(intersectedGlyphIt == components.end() &&
           "No suitable column for inserting");

    (*intersectedGlyphIt)->Insert(glyph);
}

void Page::Remove(const GlyphPtr& ptr) {
    auto it = std::find(components.begin(), components.end(), ptr);
    if (it != components.end()) {
        it = components.erase(it);
    }
}
