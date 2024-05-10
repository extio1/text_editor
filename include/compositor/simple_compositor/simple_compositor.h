#ifndef TEXT_EDITOR_SIMPLECOMPOSITOR_H_
#define TEXT_EDITOR_SIMPLECOMPOSITOR_H_

#include "document/document.h"

class SimpleCompositor : public Compositor {
   public:
    explicit SimpleCompositor() {}
    ~SimpleCompositor() override = default;

    // void SetComposition(Document* document);
    void Compose() override;
};

#endif  // TEXT_EDITOR_SIMPLECOMPOSITOR_H_