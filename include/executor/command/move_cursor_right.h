#ifndef TEXT_EDITOR_PROJECT_MOVE_CURSOR_RIGHT_H
#define TEXT_EDITOR_PROJECT_MOVE_CURSOR_RIGHT_H

#include <memory>

#include "document/document.h"
#include "executor/command.h"

class MoveCursorRight : public Command {
public:
    explicit MoveCursorRight(std::shared_ptr<IDocument> doc);

    MoveCursorRight(MoveCursorRight&&) = default;
    MoveCursorRight& operator=(MoveCursorRight&&) = default;
    MoveCursorRight(const MoveCursorRight&) = delete;
    MoveCursorRight& operator=(const MoveCursorRight&) = delete;

    void Execute() override;

    ~MoveCursorRight() override;

private:
    std::shared_ptr<IDocument> doc;
};

#endif //TEXT_EDITOR_PROJECT_MOVE_CURSOR_RIGHT_H
