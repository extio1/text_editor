#ifndef TEXTEDITOR_INCLUDEEXECUTOR_EXECUTOR_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_EXECUTOR_H_

#include "command.h"

#include <cstdint>
#include <vector>

class Executor
{
public:

    explicit Executor(const std::size_t command_queue_length);

    void Do(Command&&);
    
    void Undo();
    void Redo();

private:
    std::vector<Command> command_history;
    std::size_t new_command_indx;
};

#endif // TEXTEDITOR_INCLUDEEXECUTOR_EXECUTOR_H_