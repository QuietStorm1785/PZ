#include <string>
#include "com\sun\xml\bind\v2\runtime\output/ForkXmlOutput.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {

public ForkXmlOutput::ForkXmlOutput(XmlOutput lhs, XmlOutput rhs) {
    // TODO: Implement ForkXmlOutput
    return nullptr;
}

void ForkXmlOutput::startDocument(XMLSerializer serializer, bool fragment, int[] nsUriIndex2prefixIndex, NamespaceContextImpl nsContext) {
    // TODO: Implement startDocument
}

void ForkXmlOutput::endDocument(bool fragment) {
    // TODO: Implement endDocument
}

void ForkXmlOutput::beginStartTag(Name name) {
    // TODO: Implement beginStartTag
}

void ForkXmlOutput::attribute(Name name, const std::string& value) {
    // TODO: Implement attribute
}

void ForkXmlOutput::endTag(Name name) {
    // TODO: Implement endTag
}

void ForkXmlOutput::beginStartTag(int prefix, const std::string& localName) {
    // TODO: Implement beginStartTag
}

void ForkXmlOutput::attribute(int prefix, const std::string& localName, const std::string& value) {
    // TODO: Implement attribute
}

void ForkXmlOutput::endStartTag() {
    // TODO: Implement endStartTag
}

void ForkXmlOutput::endTag(int prefix, const std::string& localName) {
    // TODO: Implement endTag
}

void ForkXmlOutput::text(const std::string& value, bool needsSeparatingWhitespace) {
    // TODO: Implement text
}

void ForkXmlOutput::text(Pcdata value, bool needsSeparatingWhitespace) {
    // TODO: Implement text
}

} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
