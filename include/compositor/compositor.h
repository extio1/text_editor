#ifndef TEXT_EDITOR_COMPOSITOR_H_
#define TEXT_EDITOR_COMPOSITOR_H_

// #include "document/document.h"

class Document;

class Compositor {
   public:
    explicit Compositor() {}
    virtual ~Compositor() = default;

    void SetDocument(Document* document);
    virtual void Compose() = 0;
};

#endif  // TEXT_EDITOR_COMPOSITOR_H_