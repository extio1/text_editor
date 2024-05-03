#ifndef TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_H_

class Command 
{
public:
    Command() = default;
    Command(Command&&) = default;
    Command& operator=(Command&&) = default;

    Command(const Command&) = delete;
    Command& operator=(const Command&) = delete;

    virtual void Execute(){};

    virtual ~Command(){};
};

#endif // TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_H_