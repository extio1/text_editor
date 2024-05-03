#include "executor/executor.h"

#include <iostream>

Executor::Executor(const std::size_t command_queue_length):
    command_history(std::vector<Command>(command_queue_length)),
    new_command_indx(0)
    {}

void Executor::Do(Command&& command)
{
    command_history[new_command_indx++] = std::move(command);

    for (auto&& c: command_history){
        printf("%p\n", &c);
    }
}