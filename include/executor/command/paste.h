#ifndef TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_PASTE_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_PASTE_H_

#include "executor/command.h"

class Paste : public ReversibleCommand {
   public:
    Paste(Paste&&) = default;
    Paste& operator=(Paste&&) = default;
    Paste(const Paste&) = delete;
    Paste& operator=(const Paste&) = delete;

    void Execute() override;
    void Unexecute() override;

    ~Paste() override;
};

#endif  // TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_PASTE_H_