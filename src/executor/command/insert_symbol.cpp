#include "executor/command/insert_symbol.h"

#include <iostream>

InsertSymbol::InsertSymbol(int x, int y, int wight, int lenght, char symbol) : 
    c(symbol)
{
    std::cout << "InsertSymbol command creation\n";
}

void InsertSymbol::Execute()
{
    std::cout << c << " execution of InsertSymbol\n";
}

void InsertSymbol::Unexecute()
{
    std::cout << c << " unexecution of InsertSymbol\n";
}

InsertSymbol::~InsertSymbol()
{
    std::cout << "InsertSymbol command destruction " << c << "\n";
}