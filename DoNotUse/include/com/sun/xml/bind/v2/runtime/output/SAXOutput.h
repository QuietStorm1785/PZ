#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/util/AttributesImpl.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/output/NamespaceContextImpl/Element.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/ContentHandler.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/helpers/LocatorImpl.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class SAXOutput : public XmlOutputAbstractImpl {
public:
    const ContentHandler out;
    std::string elementNsUri;
    std::string elementLocalName;
    std::string elementQName;
   private char[] buf = new char[256];
    const AttributesImpl atts = std::make_shared<AttributesImpl>();

    public SAXOutput(ContentHandler out) {
      this.out = out;
      out.setDocumentLocator(std::make_unique<LocatorImpl>());
   }

    void startDocument(XMLSerializer serializer, bool fragment, int[] nsUriIndex2prefixIndex, NamespaceContextImpl nsContext) {
      super.startDocument(serializer, fragment, nsUriIndex2prefixIndex, nsContext);
      if (!fragment) {
         this.out.startDocument();
      }
   }

    void endDocument(bool fragment) {
      if (!fragment) {
         this.out.endDocument();
      }

      super.endDocument(fragment);
   }

    void beginStartTag(int prefix, const std::string& localName) {
      this.elementNsUri = this.nsContext.getNamespaceURI(prefix);
      this.elementLocalName = localName;
      this.elementQName = this.getQName(prefix, localName);
      this.atts.clear();
   }

    void attribute(int prefix, const std::string& localName, const std::string& value) {
    std::string qname;
    std::string nsUri;
      if (prefix == -1) {
         nsUri = "";
         qname = localName;
      } else {
         nsUri = this.nsContext.getNamespaceURI(prefix);
    std::string p = this.nsContext.getPrefix(prefix);
         if (p.length() == 0) {
            qname = localName;
         } else {
            qname = p + ':' + localName;
         }
      }

      this.atts.addAttribute(nsUri, localName, qname, "CDATA", value);
   }

    void endStartTag() {
    Element ns = this.nsContext.getCurrent();
      if (ns != nullptr) {
    int sz = ns.count();

         for (int i = 0; i < sz; i++) {
    std::string p = ns.getPrefix(i);
    std::string uri = ns.getNsUri(i);
            if (uri.length() != 0 || ns.getBase() != 1) {
               this.out.startPrefixMapping(p, uri);
            }
         }
      }

      this.out.startElement(this.elementNsUri, this.elementLocalName, this.elementQName, this.atts);
   }

    void endTag(int prefix, const std::string& localName) {
      this.out.endElement(this.nsContext.getNamespaceURI(prefix), localName, this.getQName(prefix, localName));
    Element ns = this.nsContext.getCurrent();
      if (ns != nullptr) {
    int sz = ns.count();

         for (int i = sz - 1; i >= 0; i--) {
    std::string p = ns.getPrefix(i);
    std::string uri = ns.getNsUri(i);
            if (uri.length() != 0 || ns.getBase() != 1) {
               this.out.endPrefixMapping(p);
            }
         }
      }
   }

    std::string getQName(int prefix, const std::string& localName) {
    std::string p = this.nsContext.getPrefix(prefix);
    std::string qname;
      if (p.length() == 0) {
         qname = localName;
      } else {
         qname = p + ':' + localName;
      }

    return qname;
   }

    void text(const std::string& value, bool needsSP) {
    int vlen = value.length();
      if (this.buf.length <= vlen) {
         this.buf = new char[Math.max(this.buf.length * 2, vlen + 1)];
      }

      if (needsSP) {
         value.getChars(0, vlen, this.buf, 1);
         this.buf[0] = ' ';
      } else {
         value.getChars(0, vlen, this.buf, 0);
      }

      this.out.characters(this.buf, 0, vlen + (needsSP ? 1 : 0));
   }

    void text(Pcdata value, bool needsSP) {
    int vlen = value.length();
      if (this.buf.length <= vlen) {
         this.buf = new char[Math.max(this.buf.length * 2, vlen + 1)];
      }

      if (needsSP) {
         value.writeTo(this.buf, 1);
         this.buf[0] = ' ';
      } else {
         value.writeTo(this.buf, 0);
      }

      this.out.characters(this.buf, 0, vlen + (needsSP ? 1 : 0));
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
