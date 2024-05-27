#include "executor/command/paste.h"

Paste::Paste(std::shared_ptr<IDocument> doc, const Point& begin_with):
    doc(doc), begin_with(begin_with){}

void Paste::Execute(){
    pasted_glyphs = doc->PasteGlyphs(begin_with);
}

void Paste::Unexecute(){
    for(auto gl : pasted_glyphs){
        doc->Remove(gl);
    }
}

Paste::~Paste(){}
