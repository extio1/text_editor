#include "../../include/glyphs/page.h"

void Page::SetCurrentRow(std::shared_ptr<Row> row) {
    currentRow = std::move(row);
}

bool Page::IsEmpty() const { 
    return components.empty();
}
