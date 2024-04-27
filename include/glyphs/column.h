// #ifndef TEXT_EDITOR_COLUMN
// #define TEXT_EDITOR_COLUMN

// #include <optional>
// #include <memory>
// #include <list>
// #include "composition.h"
// #include "row.h"

// /**
//  * A class representing a column of rows.
//  */
// class Column: public Composition {
// public:
//     explicit Column(const int x, const int y, const int width, const int height);
//     Column(const int x, const int y, const int width, const int height, GlyphList&& list);

//     void Draw() override;
//     void ReDraw() override;

//     void Remove(Window* window, const GlyphPtr& ptr);

//     void Insert(std::shared_ptr<Row>& row);
//     void Insert(std::shared_ptr<Row>&& row);
//     void InsertBack(std::list<GlyphPtr>&& list);
//     void Insert(int insertPosition, std::list<GlyphPtr>&& glyphs);

//     bool IsEmpty() const { return components.empty(); }
//     bool IsFull() const;
//     int GetFreeSpace() const { return height - usedHeight; }
//     int GetUsedSpace() const { return usedHeight; }
//     GlyphPtr GetFirstGlyph() const;
//     GlyphPtr GetLastGlyph() const;

// private:
//     int usedHeight = 0;
// };

// #endif  // TEXT_EDITOR_COLUMN