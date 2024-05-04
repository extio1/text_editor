#ifndef TEXTEDITOR_INCLUDEEXECUTOR_EXECUTOR_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_EXECUTOR_H_

#include "command.h"
#include "utils/circular_buffer.hpp"

#include <cstdint>
#include <vector>
#include <memory>


/*
 * Encapsulates circular buffer of commands.        
 * Have functions to Do, Undo (CTRL+Z) and Redo (CTRL+Y) 
 * commands from the circular buffer.
 */
class Executor
{
public:

    explicit Executor(const std::size_t command_queue_length);

    void Do(std::shared_ptr<Command>&&);
    void Undo();
    void Redo();

private:

    CircularBuffer<std::shared_ptr<Command>> command_history;
    std::size_t n_executed;
    std::size_t n_unexecuted;
};

#endif // TEXTEDITOR_INCLUDEEXECUTOR_EXECUTOR_H_