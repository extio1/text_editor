#ifndef TEXT_EDITOR_COLUMN_H_
#define TEXT_EDITOR_COLUMN_H_

#include <list>
#include <memory>
#include <optional>

#include "glyph_container.h"

/**
 * A class representing a column of rows.
 */
class Column : public GlyphContainer {
   public:
    using ColumnPtr = std::shared_ptr<Column>;

    /**
     * @brief           Creates a column with the specified parameters.
     * @param x         Horizontal coordinate.
     * @param x         Vertical coordinate.
     * @param width     Column width.
     * @param height    Column height.
     */
    explicit Column(const int x, const int y, const int width,
                    const int height);

    void Remove(const GlyphPtr& ptr) override;

    void Insert(ColumnPtr& column);
    void InsertBack(std::list<GlyphPtr>&& glyphs);
    void Insert(int insertPosition, std::list<GlyphPtr>&& itemsToInsert);

    bool IsEmpty() const;
    bool IsFull() const;

    /**
     * @brief           Calculates and returns the amount of free space by
     * height.
     * @return          The total height of the free space.
     */
    int GetFreeSpace() const;

    /**
     * @brief           Calculates and returns the amount of used space by
     * height.
     * @return          The total height of the used space.
     */
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