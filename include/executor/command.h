#ifndef TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_H_

#include <cstdio>

/*
 * Base class for commands that can be executed by Executor.
 */
class Command 
{
public:
    virtual void Execute() = 0;
    virtual ~Command(){};
};


/*
 * Commands that can be unexecuted by Executor.
 * Not all commands are reversible, for instance,
 * there no sense to reverse saving of document.
 */
class ReversibleCommand: public Command 
{
public:
    virtual void Unexecute() = 0;
    virtual ~ReversibleCommand(){};
};

#endif // TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_H_