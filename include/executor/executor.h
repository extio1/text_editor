#ifndef TEXTEDITOR_INCLUDEEXECUTOR_EXECUTOR_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_EXECUTOR_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "command.h"
#include "utils/circular_buffer.hpp"

/*
 * Encapsulates circular buffer of commands.
 * Have functions to Do, Undo (CTRL+Z) and Redo (CTRL+Y)
 * commands from the circular buffer.
 */
class Executor {
   public:
    explicit Executor(const std::size_t command_queue_length);

    void Do(std::shared_ptr<Command>&&);
    void Undo();
    void Redo();

   private:
    CircularBuffer<Command> command_history;
    /*
     * this flag is set true after Do and set false after Undo
     * because after Do "future" - commands that have been unexecuted(), are not
     * valid
     */
    bool future_impossible;
};

#endif  // TEXTEDITOR_INCLUDEEXECUTOR_EXECUTOR_H_