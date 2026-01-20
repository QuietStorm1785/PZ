#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/InterningXmlVisitor/AttributesImpl.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XmlVisitor/TextPredictor.h"
#include "javax/xml/namespace/NamespaceContext.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class InterningXmlVisitor {
public:
    const XmlVisitor next;
    const AttributesImpl attributes = std::make_shared<AttributesImpl>(nullptr);

    public InterningXmlVisitor(XmlVisitor next) {
      this.next = next;
   }

    void startDocument(LocatorEx locator, NamespaceContext nsContext) {
      this.next.startDocument(locator, nsContext);
   }

    void endDocument() {
      this.next.endDocument();
   }

    void startElement(TagName tagName) {
      this.attributes.setAttributes(tagName.atts);
      tagName.atts = this.attributes;
      tagName.uri = intern(tagName.uri);
      tagName.local = intern(tagName.local);
      this.next.startElement(tagName);
   }

    void endElement(TagName tagName) {
      tagName.uri = intern(tagName.uri);
      tagName.local = intern(tagName.local);
      this.next.endElement(tagName);
   }

    void startPrefixMapping(const std::string& prefix, const std::string& nsUri) {
      this.next.startPrefixMapping(intern(prefix), intern(nsUri));
   }

    void endPrefixMapping(const std::string& prefix) {
      this.next.endPrefixMapping(intern(prefix));
   }

    void text(CharSequence pcdata) {
      this.next.text(pcdata);
   }

    UnmarshallingContext getContext() {
      return this.next.getContext();
   }

    TextPredictor getPredictor() {
      return this.next.getPredictor();
   }

    static std::string intern(const std::string& s) {
    return s = = nullptr ? nullptr : s.intern();
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
