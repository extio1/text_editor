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