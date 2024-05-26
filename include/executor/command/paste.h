#ifndef TEXT_EDITOR_PROJECT_PASTE_H
#define TEXT_EDITOR_PROJECT_PASTE_H

#include "document/document.h"
#include "document/glyphs/glyph.h"
#include "executor/command.h"
#include "utils/point.h"

class Paste : public ReversibleCommand {
public:
    explicit Paste(std::shared_ptr<IDocument> doc, Point& begin_with);

    Paste(Paste&&) = default;
    Paste& operator=(Paste&&) = default;
    Paste(const Paste&) = delete;
    Paste& operator=(const Paste&) = delete;

    void Execute() override;
    void Unexecute() override;

    ~Paste() override;

private:
    std::shared_ptr<IDocument> doc;
    GlyphContainer::GlyphList pasted_glyphs;
};


#endif //TEXT_EDITOR_PROJECT_PASTE_H
