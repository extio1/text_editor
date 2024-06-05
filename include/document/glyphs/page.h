#ifndef TEXT_EDITOR_PAGE_H_
#define TEXT_EDITOR_PAGE_H_

<<<<<<< HEAD
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
=======
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
>>>>>>> origin/up-30

#include "glyph_container.h"

class Page : public GlyphContainer {
   public:
    using PagePtr = std::shared_ptr<Page>;

    // x and y can be used for saving position in document or can be ignored
    explicit Page(const int x, const int y, const int width, const int height);

    Glyph::GlyphList Select(const Glyph::GlyphPtr& area) override;

    void Insert(GlyphPtr& glyph) override;
    void Remove(const GlyphPtr& glyph) override;

    std::shared_ptr<Glyph> Clone() const override;

    size_t GetColumnsCount();

<<<<<<< HEAD
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        std::cout << "0 Page\n";
        ar & boost::serialization::base_object<GlyphContainer>(*this);
=======
   private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        std::cout << "0 Page\n";
        ar& boost::serialization::base_object<GlyphContainer>(*this);
>>>>>>> origin/up-30
        std::cout << "1 Page\n";
    }
    explicit Page() {}
};
BOOST_CLASS_EXPORT_KEY(Page)

#endif  // TEXT_EDITOR_PAGE_H_