#include "compositor/simple_compositor/simple_compositor.h"

#include <cmath>

int charHeight = 1;

void SimpleCompositor::Compose() {
    // std::cout << "SimpleCompositor::Compose()" << std::endl;
    GlyphContainer::GlyphList list = CutAllCharacters();

    Page::PagePtr page = document->GetFirstPage();
    while (page != nullptr) {
        if (list.empty() && page != document->GetFirstPage()) {
            Glyph::GlyphPtr pagePtr = std::static_pointer_cast<Glyph>(page);
            Page::PagePtr nextPage = document->GetNextPage(page);
            document->Remove(pagePtr);
            page = nextPage;
        } else {
            ComposePage(page, list);
            page = document->GetNextPage(page);
        }
    }

    while (!list.empty()) {
        Page::PagePtr newPage =
            std::make_shared<Page>(0, 0, pageWidth, pageHeight);
        document->AddPage(newPage);
        ComposePage(newPage, list);
    }
}

GlyphContainer::GlyphList SimpleCompositor::CutAllCharacters() {
    GlyphContainer::GlyphList charactersList;

    for (Page::PagePtr page = document->GetFirstPage(); page != nullptr;
         page = document->GetNextPage(page)) {
        for (Glyph::GlyphPtr column = page->GetFirstGlyph(); column != nullptr;
             column = page->GetNextGlyph(column)) {
            for (Glyph::GlyphPtr row = column->GetFirstGlyph(); row != nullptr;
                 row = column->GetNextGlyph(row)) {
                for (Glyph::GlyphPtr character = row->GetFirstGlyph();
                     character != nullptr;) {
                    charactersList.push_back(character);
                    Glyph::GlyphPtr nextCharacter =
                        row->GetNextGlyph(character);
                    row->Remove(character);
                    character = nextCharacter;
                }
            }
        }
    }

    return charactersList;
}

void SimpleCompositor::ComposePage(Page::PagePtr& page,
                                   GlyphContainer::GlyphList& list) {
    // std::cout << "Composing page: " << page << " " << *page << std::endl;

    size_t columnsCount = page->GetColumnsCount();

    // columns on page have the same width
    int columnWidth =
        floor((page->GetWidth() - leftIndent - rightIndent) / columnsCount);
    Glyph::GlyphPtr column = page->GetFirstGlyph();
    int currentX = leftIndent;
    while (column != nullptr) {
        if (list.empty() && column != page->GetFirstGlyph()) {
            Glyph::GlyphPtr nextColumn = page->GetNextGlyph(column);
            page->Remove(column);
            column = nextColumn;
        } else {
            ComposeColumn(column, currentX, topIndent, columnWidth,
                          page->GetHeight() - topIndent - bottomIndent, list);
            currentX += columnWidth;
            column = page->GetNextGlyph(column);
        }
    }
}

void SimpleCompositor::ComposeColumn(Glyph::GlyphPtr& column, int x, int y,
                                     int width, int height,
                                     GlyphContainer::GlyphList& list) {
    // std::cout << "Composing column: " << column << " " << *column <<
    // std::endl;
    column->SetPosition(Point(x, y));
    column->SetWidth(width);
    column->SetHeight(height);

    Glyph::GlyphPtr row = column->GetFirstGlyph();
    int currentY = topIndent;
    while (row != nullptr) {
        if (list.empty() && row != column->GetFirstGlyph()) {
            Glyph::GlyphPtr nextRow = column->GetNextGlyph(row);
            column->Remove(row);
            row = nextRow;
        } else {
            ComposeRow(row, x, currentY, width, list);
            currentY += row->GetHeight() + lineSpacing;
            row = column->GetNextGlyph(row);
        }
    }

    while (!list.empty()) {
        if (currentY + charHeight <= column->GetBottomBorder() - bottomIndent) {
            Glyph::GlyphPtr newRow =
                std::make_shared<Row>(0, 0, width, charHeight);
            column->Add(newRow);
            ComposeRow(newRow, x, currentY, width, list);
        } else {
            break;  // cannot add one more row
        }
    }
}

void SimpleCompositor::ComposeRow(Glyph::GlyphPtr& row, int x, int y, int width,
                                  GlyphContainer::GlyphList& list) {
    // std::cout << "Composing row: " << row << " " << *row << std::endl;
    row->SetPosition(Point(x, y));
    row->SetWidth(width);

    int currentX = 0;
    while (!list.empty()) {
        Glyph::GlyphPtr currentChar = list.front();
        // if character is bigger than row, we cannot insert it in any row in
        // document, so lessen character
        if (currentChar->GetWidth() > row->GetWidth()) {
            currentChar->SetWidth(row->GetWidth());
        }
        // while there is enough space in row add characters
        if (currentX + currentChar->GetWidth() <= row->GetWidth()) {
            ComposeCharacter(currentChar, currentX,
                             y);  // firstly set new position of char
            row->Insert(currentChar);
            currentX += currentChar->GetWidth();
            list.pop_front();
        } else {
            break;  // move to the next row
        }
    }

    // now compose all characters that was added to row due to format params
    switch (alignment) {
        case LEFT: {
            currentX = leftIndent;
            break;
        }
        case CENTER: {
            currentX =
                leftIndent + floor((pageWidth - leftIndent - rightIndent -
                                    GetNestedGlyphsWidth(row)) /
                                   2);
            break;
        }
        case RIGHT: {
            currentX = (pageWidth - rightIndent - GetNestedGlyphsWidth(row));
            break;
        }
        case JUSTIFIED: {
            currentX = leftIndent;
            break;
        }
    }
    // std::cout << "currentX " << currentX << " " << GetNestedGlyphsWidth(row)
    //           << std::endl;

    int characterSpacing;
    switch (alignment) {
        case LEFT: {
            characterSpacing = 0;
            break;
        }
        case CENTER: {
            characterSpacing = 0;
            break;
        }
        case RIGHT: {
            characterSpacing = 0;
            break;
        }
        case JUSTIFIED: {
            int glyphsCount = GetNestedGlyphsCount(row);
            if (glyphsCount == 0) {
                characterSpacing = 0;
            } else {
                characterSpacing = floor((pageWidth - leftIndent - rightIndent -
                                          GetNestedGlyphsWidth(row)) /
                                         glyphsCount);
            }
            break;
        }
    }

    // std::cout << "characterSpacing " << characterSpacing << std::endl;

    Glyph::GlyphPtr character = row->GetFirstGlyph();
    while (character != nullptr) {
        ComposeCharacter(character, currentX, y);
        currentX += character->GetWidth() + characterSpacing;
        character = row->GetNextGlyph(character);
    }
}

void SimpleCompositor::ComposeCharacter(Glyph::GlyphPtr& character, int x,
                                        int y) {
    // std::cout << "Composing character: " << character << " " << *character
    //           << std::endl;
    character->SetPosition(Point(x, y));
}

size_t SimpleCompositor::GetNestedGlyphsCount(Glyph::GlyphPtr& glyph) {
    size_t count = 0;
    Glyph::GlyphPtr current = glyph->GetFirstGlyph();
    while (current != nullptr) {
        ++count;
        current = glyph->GetNextGlyph(current);
    }
    return count;
}

int SimpleCompositor::GetNestedGlyphsWidth(Glyph::GlyphPtr& glyph) {
    int width = 0;
    Glyph::GlyphPtr current = glyph->GetFirstGlyph();
    while (current != nullptr) {
        width += current->GetWidth();
        current = glyph->GetNextGlyph(current);
    }
    return width;
}

int SimpleCompositor::GetNestedGlyphsHeight(Glyph::GlyphPtr& glyph) {
    int height = 0;
    Glyph::GlyphPtr current = glyph->GetFirstGlyph();
    while (current != nullptr) {
        height += current->GetHeight();
        current = glyph->GetNextGlyph(current);
    }
    return height;
}