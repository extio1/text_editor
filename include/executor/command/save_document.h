#ifndef TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_SAVEDOCUMENT_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_SAVEDOCUMENT_H_

#include "executor/command.h"

class SaveDocument : public Command {
   public:
    SaveDocument(SaveDocument&&) = default;
    SaveDocument& operator=(SaveDocument&&) = default;
    SaveDocument(const SaveDocument&) = delete;
    SaveDocument& operator=(const SaveDocument&) = delete;

    void Execute() override;

    ~SaveDocument() override;
};

#endif  // TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_SAVEDOCUMENT_H_