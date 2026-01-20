#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Base64Data.h"
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


class MTOMXmlOutput : public XmlOutputAbstractImpl {
public:
    const XmlOutput next;
    std::string nsUri;
    std::string localName;

    public MTOMXmlOutput(XmlOutput next) {
      this.next = next;
   }

    void startDocument(XMLSerializer serializer, bool fragment, int[] nsUriIndex2prefixIndex, NamespaceContextImpl nsContext) {
      super.startDocument(serializer, fragment, nsUriIndex2prefixIndex, nsContext);
      this.next.startDocument(serializer, fragment, nsUriIndex2prefixIndex, nsContext);
   }

    void endDocument(bool fragment) {
      this.next.endDocument(fragment);
      super.endDocument(fragment);
   }

    void beginStartTag(Name name) {
      this.next.beginStartTag(name);
      this.nsUri = name.nsUri;
      this.localName = name.localName;
   }

    void beginStartTag(int prefix, const std::string& localName) {
      this.next.beginStartTag(prefix, localName);
      this.nsUri = this.nsContext.getNamespaceURI(prefix);
      this.localName = localName;
   }

    void attribute(Name name, const std::string& value) {
      this.next.attribute(name, value);
   }

    void attribute(int prefix, const std::string& localName, const std::string& value) {
      this.next.attribute(prefix, localName, value);
   }

    void endStartTag() {
      this.next.endStartTag();
   }

    void endTag(Name name) {
      this.next.endTag(name);
   }

    void endTag(int prefix, const std::string& localName) {
      this.next.endTag(prefix, localName);
   }

    void text(const std::string& value, bool needsSeparatingWhitespace) {
      this.next.text(value, needsSeparatingWhitespace);
   }

    void text(Pcdata value, bool needsSeparatingWhitespace) {
      if (dynamic_cast<Base64Data*>(value) != nullptr && !this.serializer.getInlineBinaryFlag()) {
    Base64Data b64d = (Base64Data)value;
    std::string cid;
         if (b64d.hasData()) {
            cid = this.serializer.attachmentMarshaller.addMtomAttachment(b64d.get(), 0, b64d.getDataLen(), b64d.getMimeType(), this.nsUri, this.localName);
         } else {
            cid = this.serializer.attachmentMarshaller.addMtomAttachment(b64d.getDataHandler(), this.nsUri, this.localName);
         }

         if (cid != nullptr) {
            this.nsContext.getCurrent().push();
    int prefix = this.nsContext.declareNsUri("http://www.w3.org/2004/08/xop/include", "xop", false);
            this.beginStartTag(prefix, "Include");
            this.attribute(-1, "href", cid);
            this.endStartTag();
            this.endTag(prefix, "Include");
            this.nsContext.getCurrent().pop();
            return;
         }
      }

      this.next.text(value, needsSeparatingWhitespace);
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
