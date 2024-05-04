#ifndef TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_INSERTSYMBOL_H_
#define TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_INSERTSYMBOL_H_

#include "executor/command.h"

class InsertSymbol: public ReversibleCommand
{
public:
    InsertSymbol(int x, int y, int wight, int lenght, char symbol);

    InsertSymbol(InsertSymbol&&) = default;
    InsertSymbol& operator=(InsertSymbol&&) = default;
    InsertSymbol(const InsertSymbol&) = delete;
    InsertSymbol& operator=(const InsertSymbol&) = delete;

    void Execute() override;
    void Unexecute() override;

    ~InsertSymbol() override;
private:
    char c;
};

#endif // TEXTEDITOR_INCLUDEEXECUTOR_COMMAND_INSERTSYMBOL_H_