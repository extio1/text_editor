#include <iterator>
#include <algorithm>
#include <cassert>
#include "../../include/glyphs/utils/point.h"
#include "../../include/glyphs/composition.h"

Composition::Composition(const int x, const int y, const int width, const int height):
        Glyph(x, y, width, height) {
    std::cout << "Composition::Constructor()" << std::endl;
}

size_t Composition::GetGlyphPosition(const GlyphPtr& glyph)
{
    auto res = std::find_if(components.cbegin(), components.cend(), [&](const auto& it){
      return it == glyph;
    });
    assert((res != components.cend()) && "Composition doesn't contain this glyph");
    return std::distance(components.cbegin(), res);
}

Glyph::GlyphPtr Composition::Find(const Point& point){
    for(auto& it: components) {
        if (it->Intersects(point)) {
            return it;
        }
    }
    return nullptr;
}

void Composition::Draw() {
    std::cout << "Composition::Draw()" << std::endl;
    for (auto component: components) {
        component->Draw();
    }
}

void Composition::Add(GlyphPtr glyph) {
    components.push_back(std::move(glyph));
}

void Composition::Insert(GlyphPtr glyph, int pos) {
    if (pos >= components.size()) {
        components.push_back(std::move(glyph));
    } else {
        auto iter = components.begin();
        std::advance(iter, pos); // iter += pos
        components.insert(iter, std::move(glyph));
    }
}

void Composition::MoveGlyph(int x, int y) {
    Glyph::MoveGlyph(x, y);
    for (auto component: components) {
        component->MoveGlyph(x, y);
    }
}