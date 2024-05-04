#include "glyphs/page.h"

#include <cassert>
#include <algorithm>

#include "document.h"


int Page::topIndent = 0;
int Page::botIndent = 0;
int Page::leftIndent = 0;
int Page::rightIndent = 0;
const int Page::charHeight = 1; //temporary
const int Page::charWidth = 1; //temporary

Page::Page(const int x, const int y, const int width, const int height): 
GlyphContainer(x, y, width, height) {
    currentColumn = std::make_shared<Column>(
        x + leftIndent, y + topIndent,
            width - leftIndent - rightIndent, height - topIndent - botIndent);
    GlyphContainer::Add(currentColumn);
    currentRow = std::make_shared<Row>(
        x + leftIndent + charWidth, y + topIndent + charHeight,
            width - leftIndent - rightIndent, charHeight);
    GlyphList list;
    list.push_back(currentRow);
    currentColumn->InsertBack(std::move(list));
}

void Page::Draw() {
    std::cout << "Page::Draw()" << std::endl;
    GlyphContainer::Draw();
}

bool Page::IsBottomRow(const GlyphPtr& row) const {
    return row->GetBottomBorder() + charHeight >
        y + height - botIndent;
}

bool Page::IsRightColumn(const GlyphPtr& column) const {
    return column->GetRightBorder() + charWidth >
        x + width - rightIndent;
}

Row::RowPtr Page::GetFirstRow() {
    return std::static_pointer_cast<Row>(currentColumn->GetFirstGlyph());
}

Column::ColumnPtr Page::GetFirstColumn() {
    return std::static_pointer_cast<Column>(components.front());
}

void Page::SetCurrentRow(Row::RowPtr row) {
    currentRow = std::move(row);
}

void Page::SetCurrentColumn(Column::ColumnPtr column) {
    currentColumn = std::move(column);
}

bool Page::IsEmpty() const { 
    return components.empty();
}

bool Page::IsFull() const {
    return components.back()->GetPosition().x + charWidth >= GetRightBorder() - rightIndent;
}

bool Page::RowCanBeAdded(int height) const {
    return currentColumn->GetLastGlyph()->GetBottomBorder() + height < GetBottomBorder() - botIndent;
}

bool Page::ColumnCanBeAdded(int width) const {
    return components.back()->GetRightBorder() + width < GetRightBorder() - rightIndent;
}

Row::RowPtr Page::RemoveFirstRow() {
    auto result = std::static_pointer_cast<Row>(currentColumn->GetFirstGlyph());
    currentRow = result;

    currentRow->ClearGlyph();
    // auto isFull = IsFull();
    currentColumn->Remove(currentColumn->GetFirstGlyph());

    currentColumn->MoveUpRows(currentRow->GetHeight());

    // it can be useless(?)
    // if (isFull) {
    //     auto nextPage = parent->GetNextPage(this);
    //     auto newLastRow = nextPage->RemoveFirstRow(); //should take the same column, not current on that page - to fix
    //     newLastRow->SetPosition(newLastRow->GetPosition().x, currentColumn->GetLastGlyph()->GetBottomBorder());
    //     currentColumn->Add(newLastRow);
    // }

    return std::static_pointer_cast<Row>(result);
}

Column::ColumnPtr Page::RemoveFirstColumn() {
    auto result = std::static_pointer_cast<Column>(components.front());
    currentColumn = result;

    currentColumn->ClearGlyph();;
    // auto isFull = IsFull();
    components.pop_front();

    MoveLeftColumns(components.begin());

    return std::static_pointer_cast<Column>(result);
}

void Page::Insert(GlyphPtr glyph, int position) {
    GlyphContainer::Insert(glyph, position);

    auto it = std::find(components.begin(), components.end(), glyph);
    assert((it != components.end()) && "Glyph wasn't inserted");

    for (it = std::next(it); it != components.end(); ++it) {
        auto& row = *it;
        row->MoveGlyph(0, glyph->GetHeight());
    }
}

void Page::Remove(const GlyphPtr& ptr) {
    auto it = std::find(components.begin(), components.end(), ptr);
    if (it != components.end()) {
        Remove(it);
    }
}

void Page::Remove(GlyphContainer::GlyphList::iterator& it) {
    auto columnWidth = (*it)->GetWidth();
    it = components.erase(it);
    for(; it != components.end(); ++it) {
        auto& nextColumn = (*it);
        nextColumn->SetPosition({nextColumn->GetPosition().x - columnWidth, y});
    }
    ReDraw();
}

void Page::MoveLeftColumns(GlyphList::iterator colIt) {
    for(; colIt != components.end(); ++colIt) {
        auto& column = *colIt;
        column->ClearGlyph();
        column->MoveGlyph(0, -currentColumn->GetWidth());
        column->Draw();
    }
}

Column::ColumnPtr Page::GetPreviousColumn() {
    auto columnIt = std::find(components.begin(), components.end(), currentColumn);
    return std::static_pointer_cast<Column>(*(std::prev(columnIt)));
}

Column::ColumnPtr Page::GetPreviousColumn(Glyph::GlyphPtr& column) {
    auto columnIt = std::find(components.begin(), components.end(), column);
    return std::static_pointer_cast<Column>(*(std::prev(columnIt)));
}

Column::ColumnPtr Page::GetNextColumn() {
    auto columnIt = std::find(components.begin(), components.end(), currentColumn);
    return std::static_pointer_cast<Column>(*std::next(columnIt));
}

Column::ColumnPtr Page::GetNextColumn(Glyph::GlyphPtr& column) {
    auto columnIt = std::find(components.begin(), components.end(), column);
    return std::static_pointer_cast<Column>(*std::next(columnIt));
}

Column::ColumnPtr Page::GetLastColumn() {
    if (components.empty()) return nullptr;
    return std::dynamic_pointer_cast<Column>(components.back());
}