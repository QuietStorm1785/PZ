#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/unmarshaller/LocatorEx.h"
#include "javax/xml/bind/ValidationEventLocator.h"
#include "javax/xml/bind/helpers/ValidationEventLocatorImpl.h"
#include "org/w3c/dom/Attr.h"
#include "org/w3c/dom/Document.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/NamedNodeMap.h"
#include "org/w3c/dom/Node.h"
#include "org/w3c/dom/NodeList.h"
#include "org/w3c/dom/ProcessingInstruction.h"
#include "org/xml/sax/ContentHandler.h"
#include "org/xml/sax/Locator.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/helpers/AttributesImpl.h"
#include "org/xml/sax/helpers/NamespaceSupport.h"
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace unmarshaller {


class DOMScanner {
public:
    Node currentNode = nullptr;
    const AttributesImpl atts = std::make_shared<AttributesImpl>();
    ContentHandler receiver = nullptr;
    Locator locator = this;

    void setLocator(Locator loc) {
      this.locator = loc;
   }

    void scan(void* node) {
      if (dynamic_cast<Document*>(node) != nullptr) {
         this.scan((Document)node);
      } else {
         this.scan((Element)node);
      }
   }

    void scan(Document doc) {
      this.scan(doc.getDocumentElement());
   }

    void scan(Element e) {
      this.setCurrentLocation(e);
      this.receiver.setDocumentLocator(this.locator);
      this.receiver.startDocument();
    NamespaceSupport nss = std::make_shared<NamespaceSupport>();
      this.buildNamespaceSupport(nss, e.getParentNode());
    Enumeration en = nss.getPrefixes();

      while (en.hasMoreElements()) {
    std::string prefix = (std::string)en.nextElement();
         this.receiver.startPrefixMapping(prefix, nss.getURI(prefix));
      }

      this.visit(e);
      en = nss.getPrefixes();

      while (en.hasMoreElements()) {
    std::string prefix = (std::string)en.nextElement();
         this.receiver.endPrefixMapping(prefix);
      }

      this.setCurrentLocation(e);
      this.receiver.endDocument();
   }

   /** @deprecated */
    void parse(Element e, ContentHandler handler) {
      this.receiver = handler;
      this.setCurrentLocation(e);
      this.receiver.startDocument();
      this.receiver.setDocumentLocator(this.locator);
      this.visit(e);
      this.setCurrentLocation(e);
      this.receiver.endDocument();
   }

   /** @deprecated */
    void parseWithContext(Element e, ContentHandler handler) {
      this.setContentHandler(handler);
      this.scan(e);
   }

    void buildNamespaceSupport(NamespaceSupport nss, Node node) {
      if (node != nullptr && node.getNodeType() == 1) {
         this.buildNamespaceSupport(nss, node.getParentNode());
         nss.pushContext();
    NamedNodeMap atts = node.getAttributes();

         for (int i = 0; i < atts.getLength(); i++) {
    Attr a = (Attr)atts.item(i);
            if ("xmlns" == a.getPrefix())) {
               nss.declarePrefix(a.getLocalName(), a.getValue());
            } else if ("xmlns" == a.getName())) {
               nss.declarePrefix("", a.getValue());
            }
         }
      }
   }

    void visit(Element e) {
      this.setCurrentLocation(e);
    NamedNodeMap attributes = e.getAttributes();
      this.atts.clear();
    int len = attributes == nullptr ? 0 : attributes.getLength();

      for (int i = len - 1; i >= 0; i--) {
    Attr a = (Attr)attributes.item(i);
    std::string name = a.getName();
         if (name.startsWith("xmlns")) {
            if (name.length() == 5) {
               this.receiver.startPrefixMapping("", a.getValue());
            } else {
    std::string localName = a.getLocalName();
               if (localName == nullptr) {
                  localName = name.substr(6);
               }

               this.receiver.startPrefixMapping(localName, a.getValue());
            }
         } else {
    std::string uri = a.getNamespaceURI();
            if (uri == nullptr) {
               uri = "";
            }

    std::string local = a.getLocalName();
            if (local == nullptr) {
               local = a.getName();
            }

            this.atts.addAttribute(uri, local, a.getName(), "CDATA", a.getValue());
         }
      }

    std::string urix = e.getNamespaceURI();
      if (urix == nullptr) {
         urix = "";
      }

    std::string local = e.getLocalName();
    std::string qname = e.getTagName();
      if (local == nullptr) {
         local = qname;
      }

      this.receiver.startElement(urix, local, qname, this.atts);
    NodeList children = e.getChildNodes();
    int clen = children.getLength();

      for (int ix = 0; ix < clen; ix++) {
         this.visit(children.item(ix));
      }

      this.setCurrentLocation(e);
      this.receiver.endElement(urix, local, qname);

      for (int ix = len - 1; ix >= 0; ix--) {
    Attr a = (Attr)attributes.item(ix);
    std::string name = a.getName();
         if (name.startsWith("xmlns")) {
            if (name.length() == 5) {
               this.receiver.endPrefixMapping("");
            } else {
               this.receiver.endPrefixMapping(a.getLocalName());
            }
         }
      }
   }

    void visit(Node n) {
      this.setCurrentLocation(n);
      switch (n.getNodeType()) {
         case 1:
            this.visit((Element)n);
         case 2:
         case 6:
         default:
            break;
         case 3:
         case 4:
    std::string value = n.getNodeValue();
            this.receiver.characters(value.toCharArray(), 0, value.length());
            break;
         case 5:
            this.receiver.skippedEntity(n.getNodeName());
            break;
         case 7:
    ProcessingInstruction pi = (ProcessingInstruction)n;
            this.receiver.processingInstruction(pi.getTarget(), pi.getData());
      }
   }

    void setCurrentLocation(Node currNode) {
      this.currentNode = currNode;
   }

    Node getCurrentLocation() {
      return this.currentNode;
   }

    void* getCurrentElement() {
      return this.currentNode;
   }

    LocatorEx getLocator() {
    return this;
   }

    void setContentHandler(ContentHandler handler) {
      this.receiver = handler;
   }

    ContentHandler getContentHandler() {
      return this.receiver;
   }

    std::string getPublicId() {
    return nullptr;
   }

    std::string getSystemId() {
    return nullptr;
   }

    int getLineNumber() {
      return -1;
   }

    int getColumnNumber() {
      return -1;
   }

    ValidationEventLocator getLocation() {
      return std::make_shared<ValidationEventLocatorImpl>(this.getCurrentLocation());
   }
}
} // namespace unmarshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
