#ifndef TEXT_EDITOR_DOCUMENT_H_
#define TEXT_EDITOR_DOCUMENT_H_

#include <functional>
#include <boost/serialization/export.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include "glyphs/glyph.h"
#include "glyphs/page.h"

const int pageWidth = 500;
const int pageHeight = 1000;

/**
 * Interface for google mock.
 * Executor's commands depend on this interface
 */
class IDocument {
   public:
    virtual void Insert(Glyph::GlyphPtr& glyph) = 0;
    virtual void Remove(Glyph::GlyphPtr& glyph) = 0;
    virtual void SelectGlyphs(GlyphContainer::GlyphList& glyphs) = 0;
    virtual void PasteGlyphs(int x, int y) = 0;
    virtual void CutGlyphs(GlyphContainer::GlyphList& glyphs) = 0;
    virtual ~IDocument() = default;
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version){ std::cout << "IDocument\n";}
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(IDocument)

class Compositor;

class Document : public IDocument {
   public:
    using PageList = std::list<Page::PagePtr>;

    explicit Document(std::shared_ptr<Compositor> compositor);

    void SetCompositor(std::shared_ptr<Compositor> compositor);
    std::shared_ptr<Compositor> GetCompositor();

    /**
     * @brief           Inserts glyph into the document due to its position.
     * @param glyph     Pointer to the glyph.
     */
    void Insert(Glyph::GlyphPtr& glyph);

    /**
     * @brief           Remove glyph from the document by pointer.
     * @param glyph     Pointer to the glyph.
     */
    void Remove(Glyph::GlyphPtr& glyph);

    /**
     * @brief           Inserts glyphs from the buffer of selected glyphs into
     * the document by the position.
     * @param start     The starting point of the selected area in document.
     * @param end       The end point of the selected area in document.
     */
    void SelectGlyphs(const Point& start, const Point& end);

    /**
     * @brief              Inserts glyphs from the buffer of selected glyphs
     * into the document by the position.
     * @param to_point     The point where the glyphs will be inserted.
     * @return             List of created and inserted in document glyphs.
     */
    Glyph::GlyphList PasteGlyphs(const Point& to_point);

    /**
     * @brief           Removes selected glyphs from the document and leaves
     * them saved in the buffer.
     * @param start     The starting point of the selected area in document.
     * @param end       The end point of the selected area in document.
     */
    void CutGlyphs(const Point& start, const Point& end);

    void SetCurrentPage(Page::PagePtr page);
    Page::PagePtr GetCurrentPage();

    size_t GetPagesCount() const;
    size_t GetPageWidth() const;
    size_t GetPageHeight() const;

    void AddPage(const Page::PagePtr& page);

    Page::PagePtr GetFirstPage();
    Page::PagePtr GetNextPage(const Page::PagePtr& pagePtr);

   private:
    std::shared_ptr<Compositor> compositor;
    Page::PagePtr currentPage;
    PageList pages;

    GlyphContainer::GlyphList selectedGlyphs;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        std::cout << "0 Document\n";
        ar & boost::serialization::base_object<IDocument>(*this);
        ar & pages;
        std::cout << "1 Document\n";
    }
};
BOOST_CLASS_EXPORT_KEY(Document)


#endif  // TEXT_EDITOR_DOCUMENT_H_