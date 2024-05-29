#include "document/document.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
BOOST_CLASS_EXPORT_IMPLEMENT(Document)

#include <cassert>

#include "compositor/compositor.h"
#include "document/glyphs/character.h"
#include "document/glyphs/column.h"
#include "document/glyphs/glyph.h"
#include "document/glyphs/page.h"
#include "document/glyphs/row.h"

Document::Document(std::shared_ptr<Compositor> compositor) {
    currentPage = std::make_shared<Page>(0, 0, pageWidth, pageHeight);
    AddPage(currentPage);
    // set cursor on the first row on page
    selectedGlyph = this->GetFirstPage()->GetFirstGlyph()->GetFirstGlyph();

    this->compositor = compositor;
    compositor->SetDocument(this);
    compositor->Compose();
    this->DrawDocument();
}

void Document::SetCompositor(std::shared_ptr<Compositor> compositor) {
    this->compositor = compositor;
    compositor->SetDocument(this);
    compositor->Compose();
    this->DrawDocument();
}

std::shared_ptr<Compositor> Document::GetCompositor() {
    return this->compositor;
}

void Document::MoveCursorLeft() {
    Glyph::GlyphPtr leftGlyph = GetPreviousCharInDocument(selectedGlyph);
    // if cursor is in the beginning then don't move cursor
    if (leftGlyph == nullptr) {
        // set cursor in the first row of document
        selectedGlyph = this->GetFirstPage()->GetFirstGlyph()->GetFirstGlyph();
    } else {
        selectedGlyph = leftGlyph;
    }
}

void Document::MoveCursorRight() {
    // if row is selected then set cursor after first char in it
    Row::RowPtr selectedRow = std::dynamic_pointer_cast<Row>(selectedGlyph);
    if (selectedRow != nullptr) {
        if (selectedRow->GetFirstGlyph() != nullptr) {
            selectedGlyph = selectedRow->GetFirstGlyph();
        }
    } else {
        Glyph::GlyphPtr rightGlyph = GetNextCharInDocument(selectedGlyph);
        // if cursor is in the end then don't move cursor
        if (rightGlyph != nullptr) {
            selectedGlyph = rightGlyph;
        }
    }
}

Glyph::GlyphPtr Document::GetSelectedGlyph() { return selectedGlyph; }

Point Document::GetCursorPosition() {
    // check if selectedGlyph is a row or a character

    Row::RowPtr selectedRow = std::dynamic_pointer_cast<Row>(selectedGlyph);
    Point cursorPoint;
    if (selectedRow != nullptr) {
        // set cursor in the beginning of this row
        cursorPoint =
            Point(selectedRow->GetPosition().x, selectedRow->GetPosition().y);
    } else {
        Character::CharPtr selectedChar =
            std::dynamic_pointer_cast<Character>(selectedGlyph);
        assert(selectedChar != nullptr && "Selected glyph has invalid type");
        cursorPoint =
            Point(selectedChar->GetPosition().x + selectedChar->GetWidth(),
                  selectedChar->GetPosition().y);
    }
    return cursorPoint;
}

void Document::InsertChar(char symbol) {
    Point cursorPoint = GetCursorPosition();
    Character newChar = Character(cursorPoint.x, cursorPoint.y + 1,
                                  currentCharSize, currentCharSize, symbol);
    Glyph::GlyphPtr ptr = std::make_shared<Character>(newChar);

    this->Insert(ptr);
}

void Document::Insert(Glyph::GlyphPtr& glyph) {
    currentPage->Insert(glyph);

    selectedGlyph = glyph;
    compositor->Compose();
    this->DrawDocument();
}

char Document::RemoveChar() {
    char removed_char;
    if(auto c = std::dynamic_pointer_cast<Character>(selectedGlyph))
        removed_char = c->GetChar();

    this->Remove(selectedGlyph);

    return removed_char;
}

void Document::Remove(Glyph::GlyphPtr& glyph) {
    assert(glyph != nullptr && "Cannot remove glyph by nullptr");

    Glyph::GlyphPtr newSelectedGlyph;
    if (glyph == selectedGlyph) {
        newSelectedGlyph = GetPreviousCharInDocument(selectedGlyph);
        if (newSelectedGlyph == nullptr) {
            // if there is no character in document, set cursor into the first
            // row
            newSelectedGlyph =
                this->GetFirstPage()->GetFirstGlyph()->GetFirstGlyph();
        }
    }

    auto it = std::find(pages.begin(), pages.end(), glyph);
    if (it != pages.end()) {
        if (it != pages.begin()) pages.erase(it);
        return;
    }

    // what if this glyph is not from current page ???? glyph won't be found and
    // assertion will failed
    assert(glyph != nullptr && "Cannot remove glyph by nullptr");
    currentPage->Remove(glyph);

    if (glyph == selectedGlyph) {
        selectedGlyph = newSelectedGlyph;
    }
    compositor->Compose();
    this->DrawDocument();
}

void Document::SetCurrentPage(Page::PagePtr page) { currentPage = page; }

Page::PagePtr Document::GetCurrentPage() { return currentPage; }

size_t Document::GetPagesCount() const { return pages.size(); }

size_t Document::GetPageWidth() const { return pageWidth; }

size_t Document::GetPageHeight() const { return pageHeight; }

void Document::AddPage(const Page::PagePtr& page) {
    pages.push_back(page);
    // if (compositor) {
    // compositor->Compose();  // page can be non-formated
    // }
}

Page::PagePtr Document::GetFirstPage() { return *(pages.begin()); }

Page::PagePtr Document::GetNextPage(const Page::PagePtr& pagePtr) {
    auto currentPage =
        std::find_if(pages.begin(), pages.end(),
                     [&](const auto& elem) { return elem == pagePtr; });

    assert(currentPage != pages.end());

    auto nextPage = std::next(currentPage);
    if (nextPage == pages.end()) {
        return nullptr;
    }
    return std::static_pointer_cast<Page>(*nextPage);
}

void Document::SelectGlyphs(const Point& start, const Point& end) {
    Glyph::GlyphPtr area = std::make_shared<Column>(
        Column(start.x, start.y,
               (end.x > start.x ? end.x - start.x - 1 : end.x - start.x),
               (end.y > start.y ? end.y - start.y - 1 : end.y - start.y)));
    GlyphContainer::GlyphList list;
    Glyph::GlyphList glyphs = currentPage->Select(area);
    std::cout << "Selected glyphs:" << std::endl;
    for (auto glyph : glyphs) {
        std::cout << *glyph << std::endl;
    }

    selectedGlyphs.clear();
    for (auto& glyph : glyphs) {
        selectedGlyphs.push_back(glyph);
    }
}

Glyph::GlyphList Document::PasteGlyphs(const Point& to_point) {
    int currentX = to_point.x;
    int currentY = to_point.y;
    Glyph::GlyphPtr glyph;
    Glyph::GlyphList copiesList;
    for (auto& glyph : selectedGlyphs) {
        Glyph::GlyphPtr copy = glyph->Clone();
        copy->SetPosition(Point(currentX, currentY));  // set new position
        this->Insert(copy);
        copiesList.push_back(copy);
        currentX = copy->GetPosition().x +
                   copy->GetWidth();  // insert next glyph after this
        currentY =
            copy->GetPosition().y + 1;  // insert next glyph to the same row
    }
    // selected glyphs is not removed from selectedGlyphs, they can be pasted or
    // cut one more time
    return copiesList;
}

void Document::CutGlyphs(const Point& start, const Point& end) {
    SelectGlyphs(start, end);
    for (auto& glyph : selectedGlyphs) {
        this->Remove(glyph);
    }
}

GlyphContainer::GlyphList Document::GetCharactersList() {
    Glyph::GlyphList charactersList;

    for (Page::PagePtr page = this->GetFirstPage(); page != nullptr;
         page = this->GetNextPage(page)) {
        for (Glyph::GlyphPtr column = page->GetFirstGlyph(); column != nullptr;
             column = page->GetNextGlyph(column)) {
            for (Glyph::GlyphPtr row = column->GetFirstGlyph(); row != nullptr;
                 row = column->GetNextGlyph(row)) {
                for (Glyph::GlyphPtr character = row->GetFirstGlyph();
                     character != nullptr;
                     character = row->GetNextGlyph(character)) {
                    charactersList.push_back(character);
                }
            }
        }
    }

    return charactersList;
}

Glyph::GlyphPtr Document::GetNextCharInDocument(Glyph::GlyphPtr& glyph) {
    Glyph::GlyphList charactersList = GetCharactersList();
    auto it = std::find(charactersList.begin(), charactersList.end(), glyph);

    it++;
    if (it == charactersList.end()) {
        return nullptr;
    } else {
        return *it;
    }
}

Glyph::GlyphPtr Document::GetPreviousCharInDocument(Glyph::GlyphPtr& glyph) {
    Glyph::GlyphList charactersList = GetCharactersList();
    auto it = std::find(charactersList.begin(), charactersList.end(), glyph);

    if (it == charactersList.begin()) {
        return nullptr;
    } else {
        it--;
        return *it;
    }
}

void Document::DrawDocument() {
    std::cout << "-----DrawDocument()" << std::endl;
    // window->Clear();
    for (Page::PagePtr page = this->GetFirstPage(); page != nullptr;
         page = this->GetNextPage(page)) {
        std::cout << "DrawPage(): " << pageWidth << " " << pageHeight
                  << std::endl;
        // window->DrawPage(pageWidth, pageHeight);
        for (Glyph::GlyphPtr column = page->GetFirstGlyph(); column != nullptr;
             column = page->GetNextGlyph(column)) {
            for (Glyph::GlyphPtr row = column->GetFirstGlyph(); row != nullptr;
                 row = column->GetNextGlyph(row)) {
                // draw cursor in the brginning of selected row
                if (row == selectedGlyph) {
                    std::cout << "DrawCursor(): " << row->GetPosition().x << " "
                              << row->GetPosition().y << " " << row->GetHeight()
                              << std::endl;
                    // window->DrawCursor(row->GetPosition().x,
                    // row->GetPosition().y, row->GetHeight());
                }
                for (Glyph::GlyphPtr character = row->GetFirstGlyph();
                     character != nullptr;
                     character = row->GetNextGlyph(character)) {
                    Character::CharPtr charPtr =
                        std::dynamic_pointer_cast<Character>(character);
                    std::cout << "DrawChar(): " << *charPtr;
                    // window->DrawChar(charPtr->GetChar(),
                    // charPtr->GetPosition().x, charPtr->GetPosition().y,
                    // charPtr->GetHeight())

                    // draw cursor after selected character
                    if (character == selectedGlyph) {
                        std::cout << "DrawCursor(): "
                                  << character->GetPosition().x +
                                         character->GetWidth()
                                  << " " << character->GetPosition().y << " "
                                  << character->GetHeight() << std::endl;
                        // window->DrawCursor(character->GetPosition().x +
                        // character->GetWidth(), row->GetPosition().y,
                        // row->GetHeight());
                    }
                }
            }
        }
    }
}