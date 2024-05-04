#include "glyphs/glyph_container.h"

#include <cassert>

#include <algorithm>
#include <iterator>

#include "glyphs/utils/point.h"


GlyphContainer::GlyphContainer(const int x, const int y, const int width, const int height):
        Glyph(x, y, width, height) {
    std::cout << "GlyphContainer::Constructor()" << std::endl;
}

size_t GlyphContainer::GetGlyphPosition(const GlyphPtr& glyph)
{
    auto res = std::find_if(components.cbegin(), components.cend(), [&](const auto& it){
      return it == glyph;
    });
    assert((res != components.cend()) && "GlyphContainer doesn't contain this glyph");
    return std::distance(components.cbegin(), res);
}

Glyph::GlyphPtr GlyphContainer::Find(const Point& point) {
    for(auto& it: components) {
        if (it->Intersects(point)) {
            return it;
        }
    }
    return nullptr;
}

void GlyphContainer::Draw() {
    std::cout << "GlyphContainer::Draw()" << std::endl;
    for (auto component: components) {
        component->Draw();
    }
}

void GlyphContainer::Add(GlyphPtr glyph) {
    components.push_back(std::move(glyph));
}

void GlyphContainer::Insert(GlyphPtr glyph, int pos) {
    if (pos >= components.size()) {
        components.push_back(std::move(glyph));
    } else {
        auto iter = components.begin();
        std::advance(iter, pos); // iter += pos
        components.insert(iter, std::move(glyph));
    }
}

void GlyphContainer::MoveGlyph(int x, int y) {
    Glyph::MoveGlyph(x, y);
    for (auto component: components) {
        component->MoveGlyph(x, y);
    }
}