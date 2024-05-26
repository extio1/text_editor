#ifndef TEXT_EDITOR_ROW_H_
#define TEXT_EDITOR_ROW_H_

#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/shared_ptr.hpp>

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

    Glyph::GlyphList Select(const Glyph::GlyphPtr& area) override;

    /**
     * @brief           Inserts a glyph into the string at the position closest
     * to the specified one.
     * @param glyph     Pointer to the glyph.
     */
    void Insert(GlyphPtr& glyph);
    void Remove(const GlyphPtr& glyph) override;

    std::shared_ptr<Glyph> Clone() const override;

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

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        std::cout << "0 Row\n";
        ar & boost::serialization::base_object<GlyphContainer>(*this);
        ar & usedWidth;
        std::cout << "1 Row\n";
    }
    explicit Row(){}
};
BOOST_CLASS_EXPORT_KEY(Row)

#endif  // TEXT_EDITOR_ROW_H_