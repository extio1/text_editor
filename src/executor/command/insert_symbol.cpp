#include "executor/command/insert_symbol.h"

#include <iostream>

InsertSymbol::InsertSymbol(int x, int y, int wight, int lenght, char symbol):
    c(symbol)
{
    std::cout << "InsertSymbol command creation\n";
}

void InsertSymbol::Execute()
{
    std::cout << "InsertSymbol command execution\n";
}

InsertSymbol::~InsertSymbol()
{
    std::cout << c << " InsertSymbol command destruction\n";   
}