#ifndef TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_LOADDOCUMENT_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_LOADDOCUMENT_H_

#include "executor/command.h"

class LoadDocument : public Command {
   public:
    LoadDocument(LoadDocument&&) = default;
    LoadDocument& operator=(LoadDocument&&) = default;
    LoadDocument(const LoadDocument&) = delete;
    LoadDocument& operator=(const LoadDocument&) = delete;

    void Execute() override;

    ~LoadDocument() override;
};

#endif  // TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_LOADDOCUMENT_H_