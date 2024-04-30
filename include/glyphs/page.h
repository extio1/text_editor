#ifndef TEXT_EDITOR_PAGE_H_
#define TEXT_EDITOR_PAGE_H_

#include "composition.h"
#include "row.h"
#include "column.h"
#include "glyph.h"
#include "../document.h"

class Document;

class Page: public Composition {
public:    
    explicit Page(Document* parent, const int x, const int y, const int width, const int height);

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

private:
    static int topIndent;
    static int botIndent;
    static int leftIndent;
    static int rightIndent;
    static const int charHeight; //replace
    static const int charWidth; //replace
    Column::ColumnPtr currentColumn;
    Row::RowPtr currentRow;
    Document* parent;

    void MoveLeftColumns(std::list<Glyph::GlyphPtr>::iterator colIt);
    Column::ColumnPtr GetPreviousColumn();
    Column::ColumnPtr GetPreviousColumn(Glyph::GlyphPtr &column);
    Column::ColumnPtr GetNextColumn();
    Column::ColumnPtr GetNextColumn(Glyph::GlyphPtr &column);
    Column::ColumnPtr GetLastColumn();
};

#endif  // TEXT_EDITOR_PAGE_H_