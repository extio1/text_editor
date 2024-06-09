#ifndef TEXT_EDITOR_COMPOSITOR_H_
#define TEXT_EDITOR_COMPOSITOR_H_

#include <iostream>
#include <boost/serialization/export.hpp>
#include <boost/serialization/access.hpp>

#include "document/document.h"

class Compositor {
   public:
    enum Alignment { LEFT, CENTER, RIGHT, JUSTIFIED };

    Compositor() {
        document = nullptr;
        this->topIndent = 5;
        this->bottomIndent = 10;
        this->leftIndent = 3;
        this->rightIndent = 6;
        this->alignment = LEFT;
        this->lineSpacing = 3;
    }

    Compositor(int topIndent, int bottomIndent, int leftIndent,
               int rightIndent, Alignment alignment,
               int lineSpacing) {
        document = nullptr;
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

   private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        std::cout << "0 Compositor\n";
        ar & document;
        ar & topIndent & bottomIndent & leftIndent;
        ar & rightIndent & alignment & lineSpacing;
        std::cout << "1 Compositor\n";
    }

};
BOOST_CLASS_EXPORT_KEY(Compositor)

#endif  // TEXT_EDITOR_COMPOSITOR_H_