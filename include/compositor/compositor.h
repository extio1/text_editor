#ifndef TEXT_EDITOR_COMPOSITOR_H_
#define TEXT_EDITOR_COMPOSITOR_H_

#include <iostream>

#include "document/document.h"

// class Document;

// class Compositor {
//    public:
//     explicit Compositor() {}
//     virtual ~Compositor() = default;

//     // void SetDocument(Document* document);
//     void SetDocument(Document* document) {
//         std::cout << "Compositor::SetDocument()" << std::endl;
//         this->document = document;
//     }
//     virtual void Compose() = 0;
//
//    protected:
//     Document* document;
// };

class Compositor {
   public:
    Compositor() {}
    virtual ~Compositor() = default;

    void SetDocument(Document* document);
    // void SetDocument(Document* document) {
    //     std::cout << "Compositor::SetDocument()" << std::endl;
    //     this->document = document;
    // }

    virtual void Compose() = 0;

   protected:
    Document* document;
};

#endif  // TEXT_EDITOR_COMPOSITOR_H_