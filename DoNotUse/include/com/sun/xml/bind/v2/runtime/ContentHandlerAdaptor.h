#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/FinalArrayList.h"
#include "com/sun/istack/SAXException2.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/Attributes.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/helpers/DefaultHandler.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class ContentHandlerAdaptor : public DefaultHandler {
public:
   private const FinalArrayList<std::string> prefixMap = std::make_unique<FinalArrayList>();
    const XMLSerializer serializer;
    const std::stringstream text = new std::stringstream();

   ContentHandlerAdaptor(XMLSerializer _serializer) {
      this.serializer = _serializer;
   }

    void startDocument() {
      this.prefixMap.clear();
   }

    void startPrefixMapping(const std::string& prefix, const std::string& uri) {
      this.prefixMap.push_back(prefix);
      this.prefixMap.push_back(uri);
   }

    bool containsPrefixMapping(const std::string& prefix, const std::string& uri) {
      for (int i = 0; i < this.prefixMap.size(); i += 2) {
         if (((std::string)this.prefixMap.get(i)) == prefix) && ((std::string)this.prefixMap.get(i + 1)) == uri)) {
    return true;
         }
      }

    return false;
   }

    void startElement(const std::string& namespaceURI, const std::string& localName, const std::string& qName, Attributes atts) {
      try {
         this.flushText();
    int len = atts.getLength();
    std::string p = this.getPrefix(qName);
         if (this.containsPrefixMapping(p, namespaceURI)) {
            this.serializer.startElementForce(namespaceURI, localName, p, nullptr);
         } else {
            this.serializer.startElement(namespaceURI, localName, p, nullptr);
         }

         for (int i = 0; i < this.prefixMap.size(); i += 2) {
            this.serializer.getNamespaceContext().force((std::string)this.prefixMap.get(i + 1), (std::string)this.prefixMap.get(i));
         }

         for (int i = 0; i < len; i++) {
    std::string qname = atts.getQName(i);
            if (!qname.startsWith("xmlns") && atts.getURI(i).length() != 0) {
    std::string prefix = this.getPrefix(qname);
               this.serializer.getNamespaceContext().declareNamespace(atts.getURI(i), prefix, true);
            }
         }

         this.serializer.endNamespaceDecls(nullptr);

         for (int ix = 0; ix < len; ix++) {
            if (!atts.getQName(ix).startsWith("xmlns")) {
               this.serializer.attribute(atts.getURI(ix), atts.getLocalName(ix), atts.getValue(ix));
            }
         }

         this.prefixMap.clear();
         this.serializer.endAttributes();
      } catch (IOException var10) {
         throw SAXException2(var10);
      } catch (XMLStreamException var11) {
         throw SAXException2(var11);
      }
   }

    std::string getPrefix(const std::string& qname) {
    int idx = qname.indexOf(58);
    return idx = = -1 ? "" : qname.substr(0, idx);
   }

    void endElement(const std::string& namespaceURI, const std::string& localName, const std::string& qName) {
      try {
         this.flushText();
         this.serializer.endElement();
      } catch (IOException var5) {
         throw SAXException2(var5);
      } catch (XMLStreamException var6) {
         throw SAXException2(var6);
      }
   }

    void flushText() {
      if (this.text.length() != 0) {
         this.serializer.text(this.text, nullptr);
         this.text.setLength(0);
      }
   }

    void characters(char[] ch, int start, int length) {
      this.text.append(ch, start, length);
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
