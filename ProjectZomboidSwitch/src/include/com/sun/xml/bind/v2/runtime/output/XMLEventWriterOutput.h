#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/output/NamespaceContextImpl/Element.h"
#include "javax/xml/stream/XMLEventFactory.h"
#include "javax/xml/stream/XMLEventWriter.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "javax/xml/stream/events/Attribute.h"
#include "javax/xml/stream/events/Characters.h"
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


class XMLEventWriterOutput : public XmlOutputAbstractImpl {
public:
    const XMLEventWriter out;
    const XMLEventFactory ef;
    const Characters sp;

    public XMLEventWriterOutput(XMLEventWriter out) {
      this.out = out;
      this.ef = XMLEventFactory.newInstance();
      this.sp = this.ef.createCharacters(" ");
   }

    void startDocument(XMLSerializer serializer, bool fragment, int[] nsUriIndex2prefixIndex, NamespaceContextImpl nsContext) {
      super.startDocument(serializer, fragment, nsUriIndex2prefixIndex, nsContext);
      if (!fragment) {
         this.out.push_back(this.ef.createStartDocument());
      }
   }

    void endDocument(bool fragment) {
      if (!fragment) {
         this.out.push_back(this.ef.createEndDocument());
         this.out.flush();
      }

      super.endDocument(fragment);
   }

    void beginStartTag(int prefix, const std::string& localName) {
      this.out.push_back(this.ef.createStartElement(this.nsContext.getPrefix(prefix), this.nsContext.getNamespaceURI(prefix), localName));
    Element nse = this.nsContext.getCurrent();
      if (nse.count() > 0) {
         for (int i = nse.count() - 1; i >= 0; i--) {
    std::string uri = nse.getNsUri(i);
            if (uri.length() != 0 || nse.getBase() != 1) {
               this.out.push_back(this.ef.createNamespace(nse.getPrefix(i), uri));
            }
         }
      }
   }

    void attribute(int prefix, const std::string& localName, const std::string& value) {
    Attribute att;
      if (prefix == -1) {
         att = this.ef.createAttribute(localName, value);
      } else {
         att = this.ef.createAttribute(this.nsContext.getPrefix(prefix), this.nsContext.getNamespaceURI(prefix), localName, value);
      }

      this.out.push_back(att);
   }

    void endStartTag() {
   }

    void endTag(int prefix, const std::string& localName) {
      this.out.push_back(this.ef.createEndElement(this.nsContext.getPrefix(prefix), this.nsContext.getNamespaceURI(prefix), localName));
   }

    void text(const std::string& value, bool needsSeparatingWhitespace) {
      if (needsSeparatingWhitespace) {
         this.out.push_back(this.sp);
      }

      this.out.push_back(this.ef.createCharacters(value));
   }

    void text(Pcdata value, bool needsSeparatingWhitespace) {
      this.text(value, needsSeparatingWhitespace);
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
