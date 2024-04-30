#include <iostream>
#include <memory>
#include "../include/glyphs/glyph.h"
#include "../include/glyphs/character.h"
#include "../include/glyphs/button.h"
#include "../include/glyphs/monoglyph.h"
#include "../include/glyphs/composition.h"
#include "../include/glyphs/row.h"
#include "../include/glyphs/column.h"
#include "../include/document.h"
#include "../include/glyphs/page.h"

int main() {
    std::cout << "Hello" << std::endl;
    Character c = Character(1, 1, 1, 1, 'A');
    std::cout << c << std::endl;
    c.Draw();
    c.ClearGlyph();
    Glyph::GlyphPtr charPtr = std::make_shared<Character>(c);
    

    Button b = Button(2, 2, 2, 2, "MyButton");
    std::cout << b << std::endl;
    std::cout << "button is pressed: " << b.IsPressed() << std::endl;

    Glyph::GlyphPtr buttonPtr = std::make_shared<Button>(b);
    MonoGlyph m = MonoGlyph(buttonPtr);
    m.Draw();

    Composition comp = Composition(3, 3, 3, 3);
    comp.Add(charPtr);
    comp.Insert(buttonPtr, 1);
    std::cout << "char position: " << comp.GetGlyphPosition(charPtr) << std::endl;
    std::cout << "button position: " << comp.GetGlyphPosition(buttonPtr) << std::endl;
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
    std::cout << "!";
    if (r.GetFirstGlyph()) r.GetFirstGlyph()->Draw();
    if (r.GetLastGlyph()) r.GetLastGlyph()->Draw();
    
    Composition::GlyphList list;
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


    Column col = Column(0, 0, 100, 100);
    std::cout << "column is empty: " << col.IsEmpty() << std::endl;
    if (col.GetFirstGlyph()) col.GetFirstGlyph()->Draw();
    if (col.GetLastGlyph()) col.GetLastGlyph()->Draw();
    

    Composition::GlyphList list2;
    list2.push_back(std::make_shared<Row>(r));
    col.InsertBack(std::move(list2));

    std::cout << "column is empty: " << col.IsEmpty() << std::endl;
    if (col.GetFirstGlyph()) col.GetFirstGlyph()->Draw();
    if (col.GetLastGlyph()) col.GetLastGlyph()->Draw();


    //Document and Page tests
    Document doc = Document(0, 0, 100, 100);
    Document::PagePtr page = doc.GetCurrentPage();
    std::cout << page->IsEmpty() << " " << page->IsFull() << std::endl;
    page->Add(std::make_shared<Column>(col));
    std::cout << page->IsEmpty() << " " << page->IsFull() << std::endl;
    page->Draw();

    std::cout << page->RowCanBeAdded(10) << " " << page->ColumnCanBeAdded(10) << std::endl;

    Row::RowPtr rowPtr = page->RemoveFirstRow();
    Column::ColumnPtr columnPtr = page->RemoveFirstColumn();
    std::cout << "      Removed row: " << std::endl;
    if (rowPtr) rowPtr->Draw();
    std::cout << "      Removed column: " << std::endl;
    if (columnPtr) columnPtr->Draw();
    return 0;
}