#ifndef TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_COPY_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_COPY_H_

#include <vector>

#include "document/document.h"
#include "document/glyphs/glyph_container.h"
#include "executor/command.h"
#include "utils/point.h"

class Copy : public Command {
   public:
    Copy(Document& doc, Point& from, Point& to);

    Copy(Copy&&) = default;
    Copy& operator=(Copy&&) = default;
    Copy(const Copy&) = delete;
    Copy& operator=(const Copy&) = delete;

    void Execute() override;

    ~Copy() override;

   private:
    Document& doc;
    Point& from;
    Point& to;
    GlyphContainer::GlyphList glyphs;
};

#endif  // TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_COPY_H_