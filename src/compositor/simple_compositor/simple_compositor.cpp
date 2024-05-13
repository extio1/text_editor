#include "compositor/simple_compositor/simple_compositor.h"

#include <cmath>

int charHeight = 1;

void SimpleCompositor::Compose() {
    std::cout << "SimpleCompositor::Compose()" << std::endl;
    std::cout << document->GetPagesCount() << std::endl;
    Page::PagePtr page = document->GetFirstPage();
    while (page != nullptr) {
        ComposePage(page);
        page = document->GetNextPage(page);
    }
}

void SimpleCompositor::ComposePage(Page::PagePtr& page) {
    std::cout << "Composing page: " << page << " " << *page << std::endl;

    size_t columnsCount = page->GetColumnsCount();
    GlyphContainer::GlyphList cutRows;

    // columns on page have the same width
    int columnWidth =
        floor((page->GetWidth() - leftIndent - rightIndent) / columnsCount);
    std::cout << columnsCount << " columns " << columnWidth << " width"
              << std::endl;
    Glyph::GlyphPtr column = page->GetFirstGlyph();
    int currentX = leftIndent;
    while (column != nullptr) {
        for (auto& row : cutRows) {
            column->InsertFront(row);
        }
        cutRows.clear();
        cutRows = ComposeColumn(column, currentX, topIndent, columnWidth,
                                page->GetHeight() - topIndent - bottomIndent);
        currentX += columnWidth;
        column = page->GetNextGlyph(column);
    }

    if (!cutRows.empty()) {
        Page::PagePtr newPage = std::make_shared<Page>(
            Page(page->GetPosition().x, page->GetPosition().y, page->GetWidth(),
                 page->GetHeight()));
        for (auto& row : cutRows) {
            newPage->InsertFront(row);  // what if not all cut rows can be
                                        // replaced in new page???
        }
        document->AddPage(page);
    }
}

GlyphContainer::GlyphList SimpleCompositor::ComposeColumn(
    Glyph::GlyphPtr& column, int x, int y, int width, int height) {
    std::cout << "Composing column: " << column << " " << *column << std::endl;
    column->SetPosition(Point(x, y));
    column->SetWidth(width);
    column->SetHeight(height);

    // after setting column borders cut excess rows from it
    GlyphContainer::GlyphList cutRows = CutExcessRows(column);

    GlyphContainer::GlyphList cutCharacters;

    Glyph::GlyphPtr row = column->GetFirstGlyph();
    int currentY = topIndent;
    while (row != nullptr) {
        for (auto& character : cutCharacters) {
            row->InsertFront(character);
        }
        cutCharacters.clear();
        cutCharacters = ComposeRow(row, x, currentY, width);
        currentY += row->GetHeight() + lineSpacing;
        row = column->GetNextGlyph(row);
    }

    if (!cutCharacters.empty()) {
        Glyph::GlyphPtr newRow = std::make_shared<Row>(
            Row(column->GetPosition().x, column->GetPosition().x, width,
                charHeight));
        for (auto& character : cutCharacters) {
            newRow->InsertFront(character);  // what if not all cut characters
                                             // can be replaced in new row???
        }
        column->Add(newRow);
    }

    return cutRows;
}

GlyphContainer::GlyphList SimpleCompositor::ComposeRow(Glyph::GlyphPtr& row,
                                                       int x, int y,
                                                       int width) {
    std::cout << "Composing row: " << row << " " << *row << std::endl;
    row->SetPosition(Point(x, y));
    row->SetWidth(width);

    // after setting row borders cut excess characters from it
    GlyphContainer::GlyphList cutCharacters = CutExcessCharacters(row);

    Glyph::GlyphPtr character = row->GetFirstGlyph();
    int currentX;
    switch (alignment) {
        case LEFT: {
            currentX = x;
            break;
        }
        case CENTER: {
            currentX = floor((pageWidth - leftIndent - rightIndent -
                              GetNestedGlyphsWidth(row)) /
                             2);
            break;
        }
        case RIGHT: {
            currentX = (pageWidth - leftIndent - rightIndent -
                        GetNestedGlyphsWidth(row));
            break;
        }
        case JUSTIFIED: {
            currentX = x;
            break;
        }
    }
    std::cout << "currentX " << currentX << " " << GetNestedGlyphsWidth(row)
              << std::endl;

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

    std::cout << "characterSpacing " << characterSpacing << std::endl;

    while (character != nullptr) {
        ComposeCharacter(character, currentX, y);
        currentX += character->GetWidth() + characterSpacing;
        character = row->GetNextGlyph(character);
    }

    return cutCharacters;
}

void SimpleCompositor::ComposeCharacter(Glyph::GlyphPtr& character, int x,
                                        int y) {
    std::cout << "Composing character: " << character << " " << *character
              << std::endl;
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

GlyphContainer::GlyphList SimpleCompositor::CutExcessCharacters(
    Glyph::GlyphPtr& row) {
    GlyphContainer::GlyphList cutCharacters;

    if (row->GetWidth() >= GetNestedGlyphsWidth(row)) {
        return cutCharacters;
    }

    // skip serial characters that can be placed in row
    Glyph::GlyphPtr character = row->GetFirstGlyph();
    int accumulatedWidth = 0;
    while (character != nullptr) {
        if (accumulatedWidth + character->GetWidth() > row->GetWidth()) {
            break;
        }
        accumulatedWidth += character->GetWidth();
        character = row->GetNextGlyph(row);
    }

    // cut excess characters from row and paste into the list
    while (character != nullptr) {
        cutCharacters.push_back(character);
        Glyph::GlyphPtr nextCharacter = row->GetNextGlyph(character);
        row->Remove(character);
        character = nextCharacter;
    }

    return cutCharacters;
}

GlyphContainer::GlyphList SimpleCompositor::CutExcessRows(
    Glyph::GlyphPtr& column) {
    GlyphContainer::GlyphList cutRows;

    if (column->GetHeight() >= GetNestedGlyphsHeight(column)) {
        return cutRows;
    }

    // skip serial rows that can be placed in column
    Glyph::GlyphPtr row = column->GetFirstGlyph();
    int accumulatedHeight = 0;
    while (row != nullptr) {
        if (accumulatedHeight + row->GetHeight() > column->GetHeight()) {
            break;
        }
        accumulatedHeight += row->GetHeight();
        row = column->GetNextGlyph(row);
    }

    // cut excess row from column and paste into the list
    while (row != nullptr) {
        cutRows.push_back(row);
        Glyph::GlyphPtr nextRow = column->GetNextGlyph(row);
        column->Remove(row);
        row = nextRow;
    }

    return cutRows;
}