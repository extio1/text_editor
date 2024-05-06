#include "document/glyphs/monoglyph.h"


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

void MonoGlyph::Add(GlyphPtr glyph) {
    std::cout << "Monoglyph::Add()" << std::endl;
    component->Add(glyph);
}

void MonoGlyph::Insert(GlyphPtr glyph, int pos) {
    std::cout << "Monoglyph::Insert()" << std::endl;
    component->Insert(glyph, pos);
}