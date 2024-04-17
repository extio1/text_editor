#include "../../include/glyphs/row.h"

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
