#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class ForkXmlOutput : public XmlOutputAbstractImpl {
public:
    const XmlOutput lhs;
    const XmlOutput rhs;

    public ForkXmlOutput(XmlOutput lhs, XmlOutput rhs) {
      this.lhs = lhs;
      this.rhs = rhs;
   }

    void startDocument(XMLSerializer serializer, bool fragment, int[] nsUriIndex2prefixIndex, NamespaceContextImpl nsContext) {
      this.lhs.startDocument(serializer, fragment, nsUriIndex2prefixIndex, nsContext);
      this.rhs.startDocument(serializer, fragment, nsUriIndex2prefixIndex, nsContext);
   }

    void endDocument(bool fragment) {
      this.lhs.endDocument(fragment);
      this.rhs.endDocument(fragment);
   }

    void beginStartTag(Name name) {
      this.lhs.beginStartTag(name);
      this.rhs.beginStartTag(name);
   }

    void attribute(Name name, const std::string& value) {
      this.lhs.attribute(name, value);
      this.rhs.attribute(name, value);
   }

    void endTag(Name name) {
      this.lhs.endTag(name);
      this.rhs.endTag(name);
   }

    void beginStartTag(int prefix, const std::string& localName) {
      this.lhs.beginStartTag(prefix, localName);
      this.rhs.beginStartTag(prefix, localName);
   }

    void attribute(int prefix, const std::string& localName, const std::string& value) {
      this.lhs.attribute(prefix, localName, value);
      this.rhs.attribute(prefix, localName, value);
   }

    void endStartTag() {
      this.lhs.endStartTag();
      this.rhs.endStartTag();
   }

    void endTag(int prefix, const std::string& localName) {
      this.lhs.endTag(prefix, localName);
      this.rhs.endTag(prefix, localName);
   }

    void text(const std::string& value, bool needsSeparatingWhitespace) {
      this.lhs.text(value, needsSeparatingWhitespace);
      this.rhs.text(value, needsSeparatingWhitespace);
   }

    void text(Pcdata value, bool needsSeparatingWhitespace) {
      this.lhs.text(value, needsSeparatingWhitespace);
      this.rhs.text(value, needsSeparatingWhitespace);
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
