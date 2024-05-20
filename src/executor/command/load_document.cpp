#include "executor/command/load_document.h"

#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <utility>

//LoadDocument::LoadDocument(Document& doc, std::string path)
//    : doc(doc), path(std::move(path)) {}
//
//void LoadDocument::Execute() {
//    //    std::ifstream ifs(path);
//    //    boost::archive::text_iarchive ia(ifs);
//    //    ia >> doc;
//}
//
//LoadDocument::~LoadDocument() {}