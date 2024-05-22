#ifndef TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_INSERTCHARACTER_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_INSERTCHARACTER_H_

#include "document/document.h"
#include "document/glyphs/glyph.h"
#include "executor/command.h"

class InsertCharacter : public ReversibleCommand {
   public:
    explicit InsertCharacter(IDocument& doc, int x, int y, int wight, int height,
                    char symbol);

    InsertCharacter(InsertCharacter&&) = default;
    InsertCharacter& operator=(InsertCharacter&&) = default;
    InsertCharacter(const InsertCharacter&) = delete;
    InsertCharacter& operator=(const InsertCharacter&) = delete;

    void Execute() override;
    void Unexecute() override;

    ~InsertCharacter() override;

   private:
    IDocument& doc;
    Glyph::GlyphPtr character;
};

#endif  // TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_INSERTCHARACTER_H_