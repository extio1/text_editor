#include "../../include/glyphs/monoglyph.h"

MonoGlyph::MonoGlyph(GlyphPtr glyph) :
                Glyph(glyph->GetPosition().x, glyph->GetPosition().y, 
                glyph->GetWidth(), glyph->GetHeight()) {
    std::cout << "Monoglyph::Constructor()" << std::endl;
    component = glyph;
}

void MonoGlyph::Draw() {
    std::cout << "Monoglyph::Draw()" << std::endl;
    component->Draw(); 
}

void MonoGlyph::Add(std::shared_ptr<Glyph> glyph) {
    std::cout << "Monoglyph::Add()" << std::endl;
    component->Add(glyph);
}

void MonoGlyph::Insert(std::shared_ptr<Glyph> glyph, int pos) {
    std::cout << "Monoglyph::Insert()" << std::endl;
    component->Insert(glyph, pos);
}