#include "document/glyphs/glyph_container.h"

#include <algorithm>
#include <cassert>
#include <iterator>

#include "utils/point.h"

GlyphContainer::GlyphContainer(const int x, const int y, const int width,
                               const int height)
    : Glyph(x, y, width, height) {}

size_t GlyphContainer::GetGlyphIndex(const GlyphPtr& glyph) {
    auto res = std::find_if(components.cbegin(), components.cend(),
                            [&](const auto& it) { return it == glyph; });
    assert((res != components.cend()) &&
           "GlyphContainer doesn't contain this glyph");
    return std::distance(components.cbegin(), res);
}

Glyph::GlyphPtr GlyphContainer::GetGlyphByIndex(int index) {
    assert(index >= 0 && "Invalid index of glyph");
    size_t count = 0;
    for (const auto& ptr : components) {
        if (count == index) {
            return ptr;
        }
        count++;
    }
    return nullptr;
}

void GlyphContainer::Draw() {
    std::cout << "GlyphContainer::Draw()" << std::endl;
    for (auto component : components) {
        component->Draw();
    }
}

void GlyphContainer::Add(GlyphPtr glyph) { components.push_back(glyph); }

void GlyphContainer::MoveGlyph(int x, int y) {
    Glyph::MoveGlyph(x, y);
    for (auto component : components) {
        component->MoveGlyph(x, y);
    }
}

Glyph::GlyphPtr GlyphContainer::GetFirstGlyph() {
    if (components.begin() == components.end()) {
        return nullptr;
    }
    return *(components.begin());
}

Glyph::GlyphPtr GlyphContainer::GetLastGlyph() {
    if (components.begin() == components.end()) {
        return nullptr;
    }
    return *(components.end()--);
}

Glyph::GlyphPtr GlyphContainer::GetNextGlyph(GlyphPtr& glyph) {
    auto currentGlyph =
        std::find_if(components.begin(), components.end(),
                     [&](const auto& elem) { return elem == glyph; });

    assert(currentGlyph != components.end());

    auto nextGlyph = std::next(currentGlyph);
    if (nextGlyph == components.end()) {
        return nullptr;
    }
    return *nextGlyph;
}

Glyph::GlyphPtr GlyphContainer::GetPreviousGlyph(GlyphPtr& glyph) {
    auto currentGlyph =
        std::find_if(components.begin(), components.end(),
                     [&](const auto& elem) { return elem == glyph; });

    assert(currentGlyph != components.end());

    if (currentGlyph == components.begin()) {
        return nullptr;
    }
    auto previousGlyph = std::prev(currentGlyph);
    return *previousGlyph;
}