#include <iterator>
#include <algorithm>
#include "../../include/glyphs/utils/point.h"
#include "../../include/glyphs/composition.h"

Composition::Composition(const int x, const int y, const int width, const int height):
        Glyph(x, y, width, height) {
    std::cout << "Composition::Constructor()" << std::endl;
}

// size_t Composition::GetGlyphPosition(const GlyphPtr& glyph) {
//     for (auto it = components.begin(); it != components.end(); it++) {
//         if (*it == glyph) {
//             return std::distance(components.begin(), it);
//         }
//     }
//     return 5; // change
// }

size_t Composition::GetGlyphPosition(const GlyphPtr& glyph) {
    size_t position = 0;
    for (const auto& component : components) {
        if (component == glyph) {
            return position; // to fix
        }
        ++position;
    }
    return components.size(); // Return components.size() if glyph is not found
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