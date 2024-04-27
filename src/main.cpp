#include <iostream>
#include <memory>
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
    std::shared_ptr<Glyph> charPtr = std::make_shared<Character>(c);
    

    Button b = Button(2, 2, 2, 2, "MyButton");
    std::cout << b << std::endl;
    std::cout << "button is pressed: " << b.IsPressed() << std::endl;

    std::shared_ptr<Glyph> buttonPtr = std::make_shared<Button>(b);
    MonoGlyph m = MonoGlyph(buttonPtr);
    m.Draw();

    Composition comp = Composition(3, 3, 3, 3);
    comp.Add(charPtr);
    comp.Insert(buttonPtr, 1);
    std::cout << "char position: " << comp.GetGlyphPosition(std::static_pointer_cast<Glyph>(charPtr)) << std::endl;
    std::cout << "button position: " << comp.GetGlyphPosition(std::static_pointer_cast<Glyph>(buttonPtr)) << std::endl;
    comp.Draw();
    comp.MoveGlyph(1, 2);

    // check Composition::Find()
    Glyph::GlyphPtr p = comp.Find(Point(4, 3));
    std::cout << "Found glyph: " << std::endl;
    if (p != nullptr) {
        p->Draw();
    } else {
        std::cout << "nullptr" << std::endl;
    }

    // check Composition::Find() for point which is not in composition
    Glyph::GlyphPtr p2 = comp.Find(Point(1000, 1000));
    std::cout << "Found glyph: " << std::endl;
    if (p2 != nullptr) {
        p2->Draw();
    } else {
        std::cout << "nullptr" << std::endl;
    }

    Row r = Row(0, 0, 100, 100);
    std::cout << "row is empty: " << r.IsEmpty() << std::endl;
    if (r.GetFirstGlyph()) r.GetFirstGlyph()->Draw();
    if (r.GetLastGlyph()) r.GetLastGlyph()->Draw();
    
    std::list<Glyph::GlyphPtr> list;
    Character charA = Character(0, 0, 0, 0, 'A');
    Character charB = Character(1, 0, 0, 0, 'B');
    Character charC = Character(2, 0, 0, 0, 'C');
    list.push_back(std::make_shared<Character>(charA));
    list.push_back(std::make_shared<Character>(charB));
    list.push_back(std::make_shared<Character>(charC));
    r.InsertBack(std::move(list));

    std::cout << "row is empty: " << r.IsEmpty() << std::endl;
    if (r.GetFirstGlyph()) r.GetFirstGlyph()->Draw();
    if (r.GetLastGlyph()) r.GetLastGlyph()->Draw();
    return 0;
}