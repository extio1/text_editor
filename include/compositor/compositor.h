#ifndef TEXT_EDITOR_COMPOSITOR_H_
#define TEXT_EDITOR_COMPOSITOR_H_

#include <iostream>

#include "document/document.h"

class Compositor {
   public:
    enum Alignment { LEFT, CENTER, RIGHT, JUSTIFIED };

    Compositor(int topIndent = 5, int bottomIndent = 10, int leftIndent = 3,
               int rightIndent = 6, Alignment alignment = LEFT,
               int lineSpacing = 5) {
        this->topIndent = topIndent;
        this->bottomIndent = bottomIndent;
        this->leftIndent = leftIndent;
        this->rightIndent = rightIndent;
        this->alignment = alignment;
        this->lineSpacing = lineSpacing;
    }

    virtual ~Compositor() = default;

    void SetDocument(Document* document);

    virtual void Compose() = 0;

    void SetTopIndent(int value);
    void SetBottomIndent(int value);
    void SetLeftIndent(int value);
    void SetRightIndent(int value);
    void SetAlignment(Alignment value);
    void SetLineSpacing(int value);

   protected:
    Document* document;

    int topIndent;
    int bottomIndent;
    int leftIndent;
    int rightIndent;
    Alignment alignment;
    int lineSpacing;
};

#endif  // TEXT_EDITOR_COMPOSITOR_H_