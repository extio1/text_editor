#ifndef TEXT_EDITOR_DOCUMENT_H_
#define TEXT_EDITOR_DOCUMENT_H_

#include <functional>

#include "glyphs/glyph.h"
#include "glyphs/page.h"


const int pageWidth = 500;
const int pageHeight = 1000;

class Document {
public:
    explicit Document();

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
     * @brief           Saves selected glyphs from the document to the buffer of selected glyphs. 
     * @param glyphs    Pointer to the list of glyphs.
     */
    void SelectGlyphs(GlyphContainer::GlyphList& glyphs);

    /**
     * @brief           Inserts glyphs from the buffer of selected glyphs into the document by the position. 
     * @param x         Horizontal coordinate.
     * @param y         Vertical coordinate.
     */
    void PasteGlyphs(int x, int y);

    /**
     * @brief           Removes selected glyphs from the document and saves them to the selected buffer. 
     * @param glyphs    Pointer to the list of glyphs.
     */
    void CutGlyphs(GlyphContainer::GlyphList& glyphs);

    void SetCurrentPage(Page::PagePtr page);
    Page::PagePtr GetCurrentPage();

    size_t GetPageCount() const;
    size_t GetPageWidth() const;
    size_t GetPageHeight() const;

    void AddPage(const Glyph::GlyphPtr& page);
    Page::PagePtr GetNextPage(const Page* page);

private:
    Page::PagePtr currentPage;
    GlyphContainer::GlyphList pages;

    GlyphContainer::GlyphList selectedGlyphs;
};

#endif  // TEXT_EDITOR_DOCUMENT_H_