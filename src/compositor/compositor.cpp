#include "compositor/compositor.h"

#include <iostream>

void Compositor::SetDocument(Document* document) {
    std::cout << "Compositor::SetDocument()" << std::endl;
    this->document = document;
}

void Compositor::SetTopIndent(int value) { this->topIndent = value; }

void Compositor::SetBottomIndent(int value) { this->bottomIndent = value; }

void Compositor::SetLeftIndent(int value) { this->leftIndent = value; }

void Compositor::SetRightIndent(int value) { this->rightIndent = value; }

void Compositor::SetAlignment(Alignment value) { this->alignment = value; }

void Compositor::SetLineSpacing(int value) { this->lineSpacing = value; }