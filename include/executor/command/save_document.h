#ifndef TEXT_EDITOR_PROJECT_SAVE_DOCUMENT_H
#define TEXT_EDITOR_PROJECT_SAVE_DOCUMENT_H

#include <memory>

#include "document/document.h"
#include "executor/command.h"

class SaveDocument : public Command {
   public:
    explicit SaveDocument(const std::shared_ptr<IDocument> doc, std::string path);

    SaveDocument(SaveDocument&&) = default;
    SaveDocument& operator=(SaveDocument&&) = default;
    SaveDocument(const SaveDocument&) = delete;
    SaveDocument& operator=(const SaveDocument&) = delete;

    void Execute() override;

    ~SaveDocument() override;

   private:
    std::shared_ptr<IDocument> doc;
    std::string path;
};

#endif  // TEXT_EDITOR_PROJECT_SAVE_DOCUMENT_H
