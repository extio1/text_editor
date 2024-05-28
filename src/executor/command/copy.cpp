#include "executor/command/copy.h"

Copy::Copy(std::shared_ptr<IDocument> doc, const Point& from, const Point& to):
 doc(doc),from(from), to(to)
{}

void Copy::Execute(){
    doc->SelectGlyphs(from, to);
}

Copy::~Copy() {}