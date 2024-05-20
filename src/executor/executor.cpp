#include "executor/executor.h"

Executor::Executor(const std::size_t command_queue_length)
    : command_history(
          CircularBuffer<std::shared_ptr<Command>>(command_queue_length)),
      n_executed(0),
      n_unexecuted(0) {}

void Executor::Do(std::shared_ptr<Command>&& command) {
    command->Execute();
    command_history.push(std::move(command));

    ++n_executed;
    n_unexecuted = 0;
}

void Executor::Redo() {
    if (n_unexecuted > 0) {
        auto c = command_history.get_next();
        c->Execute();

        ++n_executed;
        --n_unexecuted;
    }
}

void Executor::Undo() {
    if (n_executed > 0) {
        auto c = command_history.pop();
        auto rc = std::dynamic_pointer_cast<ReversibleCommand>(c);
        if (rc) {
            rc->Unexecute();
        }

        --n_executed;
        ++n_unexecuted;
    }
}