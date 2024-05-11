#ifndef TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_CUT_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_CUT_H_

#include "executor/command.h"

class Cut : public ReversibleCommand {
   public:
    Cut(Cut&&) = default;
    Cut& operator=(Cut&&) = default;
    Cut(const Cut&) = delete;
    Cut& operator=(const Cut&) = delete;

    void Execute() override;
    void Unexecute() override;

    ~Cut() override;
};

#endif  // TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_CUT_H_