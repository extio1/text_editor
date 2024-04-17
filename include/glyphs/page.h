#ifndef TEXT_EDITOR_PAGE
#define TEXT_EDITOR_PAGE

#include "composition.h"
#include "row.h"


class Page: public Composition {
    using RowPtr = std::shared_ptr<Row>;

public:
    explicit Page(Glyph* parent, const int x, const int y, const int width, const int height);

    void Draw(Window* window) override;
    void DrawCursor(Window* window);

    bool IsBottomRow(const GlyphPtr&) const;

    std::shared_ptr<Row> GetFirstRow();
    void SetCurrentRow(std::shared_ptr<Row> row);

    bool IsEmpty() const;
    bool IsFull() const;

    bool RowCanBeAdded(int height) const;
    std::shared_ptr<Row> RemoveFirstRow();

    void Insert(GlyphPtr glyph, int position) override;

private:
    std::shared_ptr<Row> currentRow;
    Glyph* parent;
};

#endif  // TEXT_EDITOR_PAGE