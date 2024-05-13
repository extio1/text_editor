#include "compositor/simple_compositor/simple_compositor.h"

#include <cmath>

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

    // columns on page have the same width
    int columnWidth =
        floor((page->GetWidth() - leftIndent - rightIndent) / columnsCount);
    std::cout << columnsCount << " columns " << columnWidth << " width"
              << std::endl;
    Glyph::GlyphPtr column = page->GetFirstGlyph();
    int currentX = leftIndent;
    while (column != nullptr) {
        ComposeColumn(column, currentX, topIndent, columnWidth,
                      page->GetHeight() - topIndent - bottomIndent);
        currentX += columnWidth;
        column = page->GetNextGlyph(column);
    }
}

void SimpleCompositor::ComposeColumn(Glyph::GlyphPtr& column, int x, int y,
                                     int width, int height) {
    std::cout << "Composing column: " << column << " " << *column << std::endl;
    column->SetPosition(Point(x, y));
    column->SetWidth(width);
    column->SetHeight(height);

    Glyph::GlyphPtr row = column->GetFirstGlyph();
    int currentY = topIndent;
    while (row != nullptr) {
        ComposeRow(row, x, currentY, width);
        currentY += row->GetHeight() + lineSpacing;
        row = column->GetNextGlyph(row);
    }
}

void SimpleCompositor::ComposeRow(Glyph::GlyphPtr& row, int x, int y,
                                  int width) {
    std::cout << "Composing row: " << row << " " << *row << std::endl;
    row->SetPosition(Point(x, y));
    row->SetWidth(width);

    Glyph::GlyphPtr character = row->GetFirstGlyph();
    int currentX = x;
    while (character != nullptr) {
        ComposeCharacter(character, x, y);
        character = row->GetNextGlyph(character);
    }
}

void SimpleCompositor::ComposeCharacter(Glyph::GlyphPtr& character, int x,
                                        int y) {
    std::cout << "Composing character: " << character << " " << *character
              << std::endl;
    character->SetPosition(Point(x, y));
}