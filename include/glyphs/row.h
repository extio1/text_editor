#ifndef TEXT_EDITOR_ROW
#define TEXT_EDITOR_ROW

#include <memory>
#include <list>
#include "composition.h"

/**
 * A class representing a row that consists characters, images and figures.
 */
class Row: public Composition {
public:
    explicit Row(const int x, const int y, const int width, const int height);
    Row(const int x, const int y, const int width, const int height, GlyphList&& list);

    void Remove(const GlyphPtr& ptr);
    void Remove(GlyphList::iterator& it);

    void Insert(std::shared_ptr<Row>& row);
    void InsertBack(std::list<GlyphPtr>&& glyphs);
    void Insert(size_t insertPosition, std::list<GlyphPtr>&& itemsToInsert);
    void Add(GlyphPtr glyph);

    bool IsEmpty() const;
    bool IsFull() const;
    int GetFreeSpace() const;
    int GetUsedSpace() const;
    GlyphPtr GetFirstGlyph() const;
    GlyphPtr GetLastGlyph() const;

private:
    int usedWidth = 0;

    void UpdateRestElements(GlyphList::iterator& it, const int updateValue);
};

#endif  // TEXT_EDITOR_ROW