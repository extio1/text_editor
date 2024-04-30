#ifndef TEXT_EDITOR_PAGE_H_
#define TEXT_EDITOR_PAGE_H_

#include "glyph_container.h"
#include "row.h"
#include "column.h"
#include "glyph.h"


class Page: public GlyphContainer {
public:    
    using PagePtr = std::shared_ptr<Page>;

    explicit Page(const int x, const int y, const int width, const int height);

    void Draw() override;

    bool IsBottomRow(const GlyphPtr&) const;
    bool IsRightColumn(const GlyphPtr&) const;

    Row::RowPtr GetFirstRow();
    Column::ColumnPtr GetFirstColumn();
    void SetCurrentRow(Row::RowPtr row);
    void SetCurrentColumn(Column::ColumnPtr column);

    bool IsEmpty() const;
    bool IsFull() const;

    bool RowCanBeAdded(int height) const;
    bool ColumnCanBeAdded(int width) const;
    Row::RowPtr RemoveFirstRow();
    Column::ColumnPtr RemoveFirstColumn();

    void Insert(GlyphPtr glyph, int position) override;
    void Remove(const GlyphPtr& ptr) override;

private:
    static int topIndent;
    static int botIndent;
    static int leftIndent;
    static int rightIndent;
    static const int charHeight; //replace
    static const int charWidth; //replace
    Column::ColumnPtr currentColumn;
    Row::RowPtr currentRow;

    void Remove(GlyphList::iterator& it);
    void MoveLeftColumns(GlyphList::iterator colIt);
    Column::ColumnPtr GetPreviousColumn();
    Column::ColumnPtr GetPreviousColumn(Glyph::GlyphPtr &column);
    Column::ColumnPtr GetNextColumn();
    Column::ColumnPtr GetNextColumn(Glyph::GlyphPtr &column);
    Column::ColumnPtr GetLastColumn();
};

#endif  // TEXT_EDITOR_PAGE_H_