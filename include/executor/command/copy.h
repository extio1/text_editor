#ifndef TEXT_EDITOR_PROJECT_COPY_H
#define TEXT_EDITOR_PROJECT_COPY_H

#include "document/document.h"
#include "document/glyphs/glyph.h"
#include "executor/command.h"
#include "utils/point.h"

class Copy : public Command {
public:
    explicit Copy(std::shared_ptr<IDocument> doc, Point& from, Point& to);

    Copy(Copy&&) = default;
    Copy& operator=(Copy&&) = default;
    Copy(const Copy&) = delete;
    Copy& operator=(const Copy&) = delete;

    void Execute() override;

    ~Copy() override;

private:
    std::shared_ptr<IDocument> doc;
};


#endif //TEXT_EDITOR_PROJECT_COPY_H
