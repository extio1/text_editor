#include <iostream>
#include "../include/glyphs/glyph.h"
#include "../include/glyphs/character.h"
#include "../include/glyphs/button.h"
#include "../include/glyphs/monoglyph.h"
#include "../include/glyphs/composition.h"
#include "../include/glyphs/row.h"

int main() {
    std::cout << "Hello" << std::endl;
    Character c = Character(1, 1, 1, 1, 'A');
    std::cout << c << std::endl;
    c.Draw();
    c.ClearGlyph();

    Button b = Button(2, 2, 2, 2, "MyButton");
    std::cout << b << std::endl;
    std::cout << b.IsPressed() << std::endl;

    std::shared_ptr<Glyph> buttonPtr = std::make_shared<Button>(b);
    MonoGlyph m = MonoGlyph(buttonPtr);
    m.Draw();

    Composition comp = Composition(3, 3, 3, 3);
    comp.Add(std::make_shared<Character>(c));
    comp.Insert(std::make_shared<Button>(b), 1);
    std::cout << comp.GetGlyphPosition(std::make_shared<Character>(c)) << std::endl;
    std::cout << comp.GetGlyphPosition(std::make_shared<Button>(b)) << std::endl;
    comp.Draw();
    comp.MoveGlyph(1, 2);
    Glyph::GlyphPtr p = comp.Find(Point(4, 3));
    std::cout << "Found glyph: " << std::endl;
    p->Draw();

    Row r = Row(0, 0, 100, 100);
    // std::list<Glyph::GlyphPtr> list;
    // list.push_back(std::make_shared<Character>(Character(0, 0, 0, 0, 'A')));
    // list.push_back(std::make_shared<Character>(Character(1, 0, 0, 0, 'B')));
    // list.push_back(std::make_shared<Character>(Character(2, 0, 0, 0, 'C')));
    // r.InsertBack(list);

    // std::cout << r.IsEmpty() << std::endl;

    // r.GetFirstGlyph()->Draw();
    // r.GetLastGlyph()->Draw();
    return 0;
}