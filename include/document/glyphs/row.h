#ifndef TEXT_EDITOR_ROW_H_
#define TEXT_EDITOR_ROW_H_

#include <list>
#include <memory>

#include "glyph_container.h"

/**
 * A class representing a row that consists characters, images and figures.
 */
class Row : public GlyphContainer {
   public:
    using RowPtr = std::shared_ptr<Row>;

    /**
     * @brief           Creates a row with the specified parameters.
     * @param x         Horizontal coordinate.
     * @param x         Vertical coordinate.
     * @param width     Row width.
     * @param height    Row height.
     */
    explicit Row(const int x, const int y, const int width, const int height);

    /**
     * @brief           Inserts a glyph into the string at the position closest
     * to the specified one.
     * @param glyph     Pointer to the glyph.
     */
    void Insert(GlyphPtr& glyph);

    void Remove(const GlyphPtr& glyph) override;

    bool IsEmpty() const;
    bool IsFull() const;

    /**
     * @brief           Calculates and returns the amount of free space by
     * width.
     * @return          The total width of the free space.
     */
    int GetFreeSpace() const;

    /**
     * @brief           Calculates and returns the amount of used space by
     * width.
     * @return          The total width of the used space.
     */
    int GetUsedSpace() const;

   private:
    int usedWidth = 0;
};

#endif  // TEXT_EDITOR_ROW_H_