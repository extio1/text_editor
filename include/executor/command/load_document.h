#ifndef TEXT_EDITOR_PROJECT_LOAD_DOCUMENT_H
#define TEXT_EDITOR_PROJECT_LOAD_DOCUMENT_H

#include <memory>

#include "document/document.h"
#include "executor/command.h"

class LoadDocument : public Command {
public:
    explicit LoadDocument(std::shared_ptr<IDocument>& doc, std::string path);

    LoadDocument(LoadDocument&&) = default;
    LoadDocument& operator=(LoadDocument&&) = default;
    LoadDocument(const LoadDocument&) = delete;
    LoadDocument& operator=(const LoadDocument&) = delete;

    void Execute() override;

    ~LoadDocument() override;

private:
    std::shared_ptr<IDocument> doc;
    std::string path;
};

#endif  // TEXT_EDITOR_PROJECT_LOAD_DOCUMENT_H
