#include <string>
#include "com\sun\xml\bind\v2\runtime\output/MTOMXmlOutput.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {

public MTOMXmlOutput::MTOMXmlOutput(XmlOutput next) {
    // TODO: Implement MTOMXmlOutput
    return nullptr;
}

void MTOMXmlOutput::startDocument(XMLSerializer serializer, bool fragment, int[] nsUriIndex2prefixIndex, NamespaceContextImpl nsContext) {
    // TODO: Implement startDocument
}

void MTOMXmlOutput::endDocument(bool fragment) {
    // TODO: Implement endDocument
}

void MTOMXmlOutput::beginStartTag(Name name) {
    // TODO: Implement beginStartTag
}

void MTOMXmlOutput::beginStartTag(int prefix, const std::string& localName) {
    // TODO: Implement beginStartTag
}

void MTOMXmlOutput::attribute(Name name, const std::string& value) {
    // TODO: Implement attribute
}

void MTOMXmlOutput::attribute(int prefix, const std::string& localName, const std::string& value) {
    // TODO: Implement attribute
}

void MTOMXmlOutput::endStartTag() {
    // TODO: Implement endStartTag
}

void MTOMXmlOutput::endTag(Name name) {
    // TODO: Implement endTag
}

void MTOMXmlOutput::endTag(int prefix, const std::string& localName) {
    // TODO: Implement endTag
}

void MTOMXmlOutput::text(const std::string& value, bool needsSeparatingWhitespace) {
    // TODO: Implement text
}

void MTOMXmlOutput::text(Pcdata value, bool needsSeparatingWhitespace) {
    // TODO: Implement text
}

} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
