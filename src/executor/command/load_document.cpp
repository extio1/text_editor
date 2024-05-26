#include "executor/command/load_document.h"

#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

LoadDocument::LoadDocument(std::shared_ptr<IDocument>* doc, std::string path):
        doc(doc), path(std::move(path)) {}

void LoadDocument::Execute()
{
    IDocument* document;

    std::ifstream ofs(path);
    boost::archive::text_iarchive ia(ofs);
    ia >> document;

    doc->reset(document);
}

LoadDocument::~LoadDocument() = default;