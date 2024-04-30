#ifndef TEXT_EDITOR_COLUMN_H_
#define TEXT_EDITOR_COLUMN_H_

#include <optional>
#include <memory>
#include <list>
#include "composition.h"

/**
 * A class representing a column of rows.
 */
class Column: public Composition {
public:
    using ColumnPtr = std::shared_ptr<Column>;
    
    explicit Column(const int x, const int y, const int width, const int height);
    Column(const int x, const int y, const int width, const int height, GlyphList&& list);

    void Remove(const GlyphPtr& ptr) override;

    void Insert(ColumnPtr& column);
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

    void Remove(GlyphList::iterator& it);
    void UpdateRestElements(GlyphList::iterator& it, const int updateValue);
};

#endif  // TEXT_EDITOR_COLUMN_H_