#ifndef TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_REMOVECHARACTER_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_REMOVECHARACTER_H_

#include "document/document.h"
#include "document/glyphs/glyph.h"
#include "executor/command.h"

class RemoveCharacter : public ReversibleCommand {
   public:
    explicit RemoveCharacter(IDocument& doc, int x, int y);

    RemoveCharacter(RemoveCharacter&&) = default;
    RemoveCharacter& operator=(RemoveCharacter&&) = default;
    RemoveCharacter(const RemoveCharacter&) = delete;
    RemoveCharacter& operator=(const RemoveCharacter&) = delete;

    void Execute() override;
    void Unexecute() override;

    ~RemoveCharacter() override;

   private:
    IDocument& doc;
    Glyph::GlyphPtr character;
};

#endif  // TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_REMOVECHARACTER_H_