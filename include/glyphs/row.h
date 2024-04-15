#ifndef TEXT_EDITOR_ROW
#define TEXT_EDITOR_ROW

#include <optional>
#include <memory>
#include <list>
#include "utils/glyph_params.h"
#include "window.h"
#include "composition.h"

class Row: public Composition {
public:
    explicit Row(const GlyphParams& params);
    Row(const GlyphParams& params, GlyphList&& list);

    void Draw(Window* window) override;
    void ReDraw(Window* window) override;

    void Remove(Window* window, const GlyphPtr& ptr);

    void Insert(std::shared_ptr<Row>& row);
    void Insert(std::shared_ptr<Row>&& row);
    void InsertBack(std::list<GlyphPtr>&& glyphs);
    void Insert(int insertPosition, std::list<GlyphPtr>&& glyphs);

    bool IsEmpty() const { return components.empty(); }
    bool IsFull() const;
    int GetFreeSpace() const { return params.width - usedWidth; }
    int GetUsedSpace() const { return usedWidth; }
    GlyphPtr GetFirstGlyph() const;
    GlyphPtr GetLastGlyph() const;

private:
    int usedWidth = 0;
};

#endif  // TEXT_EDITOR_ROW