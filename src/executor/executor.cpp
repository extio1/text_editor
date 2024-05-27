#include "executor/executor.h"

Executor::Executor(const std::size_t command_queue_length)
    : command_history(
          CircularBuffer<Command>(command_queue_length))
          {}

void Executor::Do(std::shared_ptr<Command>&& command) {
    command->Execute();
    command_history.push(std::move(command));
}

void Executor::Redo() {
    auto c = command_history.get_next();

    if(c)
        c->Execute();
}

void Executor::Undo() {
    auto c = command_history.pop();

    if(c) {
        auto rc = std::dynamic_pointer_cast<ReversibleCommand>(c);
        if (rc) {
            rc->Unexecute();
        }
    }
}