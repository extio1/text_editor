#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "compositor/compositor.h"
BOOST_CLASS_EXPORT_IMPLEMENT(Compositor)

#include <iostream>

void Compositor::SetDocument(Document* document) {
    // std::cout << "Compositor::SetDocument()" << std::endl;
    this->document = document;
}

void Compositor::SetTopIndent(int value) { this->topIndent = value; }

void Compositor::SetBottomIndent(int value) { this->bottomIndent = value; }

void Compositor::SetLeftIndent(int value) { this->leftIndent = value; }

void Compositor::SetRightIndent(int value) { this->rightIndent = value; }

void Compositor::SetAlignment(Alignment value) { this->alignment = value; }

void Compositor::SetLineSpacing(int value) { this->lineSpacing = value; }