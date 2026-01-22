#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XmlVisitor/TextPredictor.h"
#include "javax/activation/DataHandler.h"
#include "javax/xml/bind/attachment/AttachmentUnmarshaller.h"
#include "javax/xml/namespace/NamespaceContext.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class MTOMDecorator {
public:
    const XmlVisitor next;
    const AttachmentUnmarshaller au;
    UnmarshallerImpl parent;
    const Base64Data base64data = std::make_shared<Base64Data>();
    bool inXopInclude;
    bool followXop;

    public MTOMDecorator(UnmarshallerImpl parent, XmlVisitor next, AttachmentUnmarshaller au) {
      this.parent = parent;
      this.next = next;
      this.au = au;
   }

    void startDocument(LocatorEx loc, NamespaceContext nsContext) {
      this.next.startDocument(loc, nsContext);
   }

    void endDocument() {
      this.next.endDocument();
   }

    void startElement(TagName tagName) {
      if (tagName.local == "Include") && tagName.uri == "http://www.w3.org/2004/08/xop/include")) {
    std::string href = tagName.atts.getValue("href");
    DataHandler attachment = this.au.getAttachmentAsDataHandler(href);
         if (attachment == nullptr) {
            this.parent.getEventHandler().handleEvent(nullptr);
         }

         this.base64data.set(attachment);
         this.next.text(this.base64data);
         this.inXopInclude = true;
         this.followXop = true;
      } else {
         this.next.startElement(tagName);
      }
   }

    void endElement(TagName tagName) {
      if (this.inXopInclude) {
         this.inXopInclude = false;
         this.followXop = true;
      } else {
         this.next.endElement(tagName);
      }
   }

    void startPrefixMapping(const std::string& prefix, const std::string& nsUri) {
      this.next.startPrefixMapping(prefix, nsUri);
   }

    void endPrefixMapping(const std::string& prefix) {
      this.next.endPrefixMapping(prefix);
   }

    void text(CharSequence pcdata) {
      if (!this.followXop) {
         this.next.text(pcdata);
      } else {
         this.followXop = false;
      }
   }

    UnmarshallingContext getContext() {
      return this.next.getContext();
   }

    TextPredictor getPredictor() {
      return this.next.getPredictor();
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
