#ifndef TEXT_EDITOR_COLUMN_H_
#define TEXT_EDITOR_COLUMN_H_

#include <boost/serialization/list.hpp>
#include <boost/serialization/shared_ptr.hpp>
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

    Glyph::GlyphList Select(const Glyph::GlyphPtr& area) override;

    void Insert(GlyphPtr& glyph) override;
    void Remove(const GlyphPtr& glyph) override;

    std::shared_ptr<Glyph> Clone() const override;

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

   private:
    int usedHeight = 0;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        std::cout << "0 Column\n";
        ar & boost::serialization::base_object<GlyphContainer>(*this);
        ar & usedHeight;
        std::cout << "1 Column\n";
    }
    explicit Column() {}
};
BOOST_CLASS_EXPORT_KEY(Column)

#endif  // TEXT_EDITOR_COLUMN_H_