#ifndef JAVAX_XML_PARSERS_DOCUMENTBUILDERFACTORY_H
#define JAVAX_XML_PARSERS_DOCUMENTBUILDERFACTORY_H

#include "javax/xml/parsers/DocumentBuilder.h"

namespace javax { namespace xml { namespace parsers {

class DocumentBuilderFactory {
public:
 static DocumentBuilderFactory* newInstance() { static DocumentBuilderFactory f; return &f; }
 DocumentBuilder* newDocumentBuilder() { static DocumentBuilder b; return &b; }
};

}}} // namespace javax::xml::parsers

#endif // JAVAX_XML_PARSERS_DOCUMENTBUILDERFACTORY_H
