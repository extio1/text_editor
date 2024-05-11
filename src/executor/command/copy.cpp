#include "executor/command/copy.h"

Copy::Copy(Document& doc, Point& from, Point& to)
    : doc(doc), glyphs(std::list<Glyph::GlyphPtr>()) {}

void Copy::Execute() { doc->SelectGlyphs(); }

~Copy() override;