#include "executor/command/save_document.h"

#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

SaveDocument::SaveDocument(IDocument& doc, std::string path):
doc(doc), path(std::move(path)){}

void SaveDocument::Execute()
{
    std::ofstream ofs(path);
    boost::archive::text_oarchive oa(ofs);
    oa << &doc;
}

SaveDocument::~SaveDocument() = default;