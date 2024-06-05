#ifndef TEXT_EDITOR_PROJECT_MOVE_CURSOR_LEFT_H
#define TEXT_EDITOR_PROJECT_MOVE_CURSOR_LEFT_H

#include <memory>

#include "document/document.h"
#include "executor/command.h"

class MoveCursorLeft : public Command {
public:
    explicit MoveCursorLeft(std::shared_ptr<IDocument> doc);

    MoveCursorLeft(MoveCursorLeft&&) = default;
    MoveCursorLeft& operator=(MoveCursorLeft&&) = default;
    MoveCursorLeft(const MoveCursorLeft&) = delete;
    MoveCursorLeft& operator=(const MoveCursorLeft&) = delete;

    void Execute() override;

    ~MoveCursorLeft() override;

private:
    std::shared_ptr<IDocument> doc;
};

#endif //TEXT_EDITOR_PROJECT_MOVE_CURSOR_LEFT_H
