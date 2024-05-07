#include "document/glyphs/glyph_container.h"

#include <algorithm>
#include <cassert>
#include <iterator>

#include "utils/point.h"

GlyphContainer::GlyphContainer(const int x, const int y, const int width,
                               const int height)
    : Glyph(x, y, width, height) {
    std::cout << "GlyphContainer::Constructor()" << std::endl;
}

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

// what if more than one glyphs intersects point???
Glyph::GlyphPtr GlyphContainer::Find(const Point& point) {
    for (auto& it : components) {
        if (it->Intersects(point)) {
            return it;
        }
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

void GlyphContainer::Insert(GlyphPtr glyph, int index) {
    assert(index >= 0 && "Invalid position for inserting glyph");
    if (index >= components.size()) {
        components.push_back(glyph);
    } else {
        auto iter = components.begin();
        std::advance(iter, index);
        components.insert(iter, glyph);
    }
}

void GlyphContainer::MoveGlyph(int x, int y) {
    Glyph::MoveGlyph(x, y);
    for (auto component : components) {
        component->MoveGlyph(x, y);
    }
}