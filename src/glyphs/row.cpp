#include "../../include/glyphs/row.h"

Row::Row(const int x, const int y, const int width, const int height): 
    Composition(x, y, width, height) {}

bool Row::IsEmpty() const { 
    return components.empty(); 
}
bool Row::IsFull() const {
    // TO DO
}
int Row::GetFreeSpace() const { 
    return width - usedWidth; 
}
int Row::GetUsedSpace() const { 
    return usedWidth; 
}
