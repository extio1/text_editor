#ifndef TEXT_EDITOR_ROW_H_
#define TEXT_EDITOR_ROW_H_

#include <memory>
#include <list>

#include "glyph_container.h"


/**
 * A class representing a row that consists characters, images and figures.
 */
class Row: public GlyphContainer {
public:
    using RowPtr = std::shared_ptr<Row>;

    explicit Row(const int x, const int y, const int width, const int height);
    Row(const int x, const int y, const int width, const int height, GlyphList&& list);

    void Remove(const GlyphPtr& ptr) override;

    void Insert(RowPtr& row);
    void InsertBack(std::list<GlyphPtr>&& glyphs);
    void Insert(int insertPosition, std::list<GlyphPtr>&& itemsToInsert);

    bool IsEmpty() const;
    bool IsFull() const;
    int GetFreeSpace() const;
    int GetUsedSpace() const;
    GlyphPtr GetFirstGlyph() const;
    GlyphPtr GetLastGlyph() const;

private:
    int usedWidth = 0;

    void Remove(GlyphList::iterator& it);
    void UpdateRestElements(GlyphList::iterator& it, const int updateValue);
};

#endif  // TEXT_EDITOR_ROW_H_