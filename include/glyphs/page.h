#ifndef TEXT_EDITOR_PAGE
#define TEXT_EDITOR_PAGE

#include "composition.h"
#include "row.h"
#include "column.h"
#include "glyph.h"
#include "../document.h"

class Document;

class Page: public Composition {
    using RowPtr = std::shared_ptr<Row>;
    using ColumnPtr = std::shared_ptr<Column>;

public:
    explicit Page(Document* parent, const int x, const int y, const int width, const int height);

    void Draw() override;

    bool IsBottomRow(const GlyphPtr&) const;
    bool IsRightColumn(const GlyphPtr&) const;

    std::shared_ptr<Row> GetFirstRow();
    std::shared_ptr<Column> GetFirstColumn();
    void SetCurrentRow(std::shared_ptr<Row> row);
    void SetCurrentColumn(std::shared_ptr<Column> column);

    bool IsEmpty() const;
    bool IsFull() const;

    bool RowCanBeAdded(int height) const;
    bool ColumnCanBeAdded(int width) const;
    std::shared_ptr<Row> RemoveFirstRow();
    std::shared_ptr<Column> RemoveFirstColumn();

    void Insert(GlyphPtr glyph, int position) override;

private:
    static int topIndent;
    static int botIndent;
    static int leftIndent;
    static int rightIndent;
    static const int charHeight; //replace
    static const int charWidth; //replace
    std::shared_ptr<Column> currentColumn;
    std::shared_ptr<Row> currentRow;
    Document* parent;

    void MoveLeftColumns(std::list<Glyph::GlyphPtr>::iterator colIt);
    std::shared_ptr<Column> GetPreviousColumn();
    std::shared_ptr<Column> GetPreviousColumn(Glyph::GlyphPtr &column);
    std::shared_ptr<Column> GetNextColumn();
    std::shared_ptr<Column> GetNextColumn(Glyph::GlyphPtr &column);
    ColumnPtr GetLastColumn();
};

#endif  // TEXT_EDITOR_PAGE