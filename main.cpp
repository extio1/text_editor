#include "include/vector.h"
#include <vector>
#include <iostream>

int main()
{
    auto v1 = Vector{1, 2, 3};
    auto v2 = Vector{0, 0, 0};

    std::cout << v1 / v2 << "\n";
}