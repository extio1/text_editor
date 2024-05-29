#include "executor/command/move_cursor_left.h"

MoveCursorLeft::MoveCursorLeft(std::shared_ptr<IDocument> doc): doc(doc){}

void MoveCursorLeft::Execute() {
    doc->MoveCursorLeft();
}

MoveCursorLeft::~MoveCursorLeft() = default;
