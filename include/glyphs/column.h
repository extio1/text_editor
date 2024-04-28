#ifndef TEXT_EDITOR_COLUMN
#define TEXT_EDITOR_COLUMN

#include <optional>
#include <memory>
#include <list>
#include "composition.h"

/**
 * A class representing a column of rows.
 */
class Column: public Composition {
public:
    explicit Column(const int x, const int y, const int width, const int height);
    Column(const int x, const int y, const int width, const int height, GlyphList&& list);

    void Remove(const GlyphPtr& ptr);
    void Remove(GlyphList::iterator& it);

    void Insert(std::shared_ptr<Column>& column);
    void InsertBack(std::list<GlyphPtr>&& glyphs);
    void Insert(size_t insertPosition, std::list<GlyphPtr>&& itemsToInsert);

    bool IsEmpty() const;
    bool IsFull() const;
    int GetFreeSpace() const;
    int GetUsedSpace() const;
    GlyphPtr GetFirstGlyph() const;
    GlyphPtr GetLastGlyph() const;

    void MoveUpRows(int height);

private:
    int usedHeight = 0;

    void UpdateRestElements(GlyphList::iterator& it, const int updateValue);
};

#endif  // TEXT_EDITOR_COLUMN