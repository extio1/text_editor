#ifndef TEXT_EDITOR_COLUMN
#define TEXT_EDITOR_COLUMN

#include <optional>
#include <memory>
#include <list>
#include "utils/glyph_params.h"
#include "window.h"
#include "composition.h"
#include "row.h"

class Column: public Composition {
public:
    explicit Column(const GlyphParams& params);
    Column(const GlyphParams& params, GlyphList&& list);

    void Draw(Window* window) override;
    void ReDraw(Window* window) override;

    void Remove(Window* window, const GlyphPtr& ptr);

    void Insert(std::shared_ptr<Row>& row);
    void Insert(std::shared_ptr<Row>&& row);
    void InsertBack(std::list<GlyphPtr>&& list);
    void Insert(int insertPosition, std::list<GlyphPtr>&& glyphs);

    bool IsEmpty() const { return components.empty(); }
    bool IsFull() const;
    int GetFreeSpace() const { return params.height - usedHeight; }
    int GetUsedSpace() const { return usedHeight; }
    GlyphPtr GetFirstGlyph() const;
    GlyphPtr GetLastGlyph() const;

private:
    int usedHeight = 0;
};

#endif  // TEXT_EDITOR_COLUMN