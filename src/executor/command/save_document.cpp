#include "executor/command/save_document.h"

#include <boost/archive/text_oarchive.hpp>
#include <fstream>
#include <utility>

//SaveDocument::SaveDocument(Document& doc, std::string path)
//    : doc(doc), path(std::move(path)) {}
//
//void SaveDocument::Execute() {
//    std::ofstream ofs(path);
//    boost::archive::text_oarchive oa(ofs);
//    oa << doc;
//}
//
//SaveDocument::~SaveDocument() {}
