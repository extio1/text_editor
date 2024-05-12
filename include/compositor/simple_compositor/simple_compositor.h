#ifndef TEXT_EDITOR_SIMPLECOMPOSITOR_H_
#define TEXT_EDITOR_SIMPLECOMPOSITOR_H_

#include <iostream>

#include "compositor/compositor.h"
#include "document/document.h"

class SimpleCompositor : public Compositor {
   public:
    explicit SimpleCompositor() {}
    ~SimpleCompositor() override = default;

    // void Compose() override;
    void Compose() override {
        std::cout << "SimpleCompositor::Compose()" << std::endl;
    }
};

#endif  // TEXT_EDITOR_SIMPLECOMPOSITOR_H_