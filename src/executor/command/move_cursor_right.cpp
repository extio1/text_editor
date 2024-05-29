#include "executor/command/move_cursor_right.h"

MoveCursorRight::MoveCursorRight(std::shared_ptr<IDocument> doc): doc(doc){}

void MoveCursorRight::Execute() {
    doc->MoveCursorRight();
}

MoveCursorRight::~MoveCursorRight() = default;
