#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XmlVisitor/TextPredictor.h"
#include "com/sun/xml/bind/v2/util/FatalAdapter.h"
#include "javax/xml/namespace/NamespaceContext.h"
#include "javax/xml/validation/Schema.h"
#include "javax/xml/validation/ValidatorHandler.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class ValidatingUnmarshaller {
public:
    const XmlVisitor next;
    const ValidatorHandler validator;
    NamespaceContext nsContext = nullptr;
    const TextPredictor predictor;
   private char[] buf = new char[256];

    public ValidatingUnmarshaller(Schema schema, XmlVisitor next) {
      this.validator = schema.newValidatorHandler();
      this.next = next;
      this.predictor = next.getPredictor();
      this.validator.setErrorHandler(std::make_shared<FatalAdapter>(this.getContext()));
   }

    void startDocument(LocatorEx locator, NamespaceContext nsContext) {
      this.nsContext = nsContext;
      this.validator.setDocumentLocator(locator);
      this.validator.startDocument();
      this.next.startDocument(locator, nsContext);
   }

    void endDocument() {
      this.nsContext = nullptr;
      this.validator.endDocument();
      this.next.endDocument();
   }

    void startElement(TagName tagName) {
      if (this.nsContext != nullptr) {
    std::string tagNamePrefix = tagName.getPrefix().intern();
         if (tagNamePrefix != "") {
            this.validator.startPrefixMapping(tagNamePrefix, this.nsContext.getNamespaceURI(tagNamePrefix));
         }
      }

      this.validator.startElement(tagName.uri, tagName.local, tagName.getQname(), tagName.atts);
      this.next.startElement(tagName);
   }

    void endElement(TagName tagName) {
      this.validator.endElement(tagName.uri, tagName.local, tagName.getQname());
      this.next.endElement(tagName);
   }

    void startPrefixMapping(const std::string& prefix, const std::string& nsUri) {
      this.validator.startPrefixMapping(prefix, nsUri);
      this.next.startPrefixMapping(prefix, nsUri);
   }

    void endPrefixMapping(const std::string& prefix) {
      this.validator.endPrefixMapping(prefix);
      this.next.endPrefixMapping(prefix);
   }

    void text(CharSequence pcdata) {
    int len = pcdata.length();
      if (this.buf.length < len) {
         this.buf = new char[len];
      }

      for (int i = 0; i < len; i++) {
         this.buf[i] = pcdata.charAt(i);
      }

      this.validator.characters(this.buf, 0, len);
      if (this.predictor.expectText()) {
         this.next.text(pcdata);
      }
   }

    UnmarshallingContext getContext() {
      return this.next.getContext();
   }

    TextPredictor getPredictor() {
    return this;
   }

    bool expectText() {
    return true;
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
