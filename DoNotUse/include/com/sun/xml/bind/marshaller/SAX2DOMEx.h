#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/FinalArrayList.h"
#include "com/sun/xml/bind/util/Which.h"
#include "com/sun/xml/bind/v2/util/XmlFactory.h"
#include "javax/xml/parsers/DocumentBuilderFactory.h"
#include "javax/xml/parsers/ParserConfigurationException.h"
#include "org/w3c/dom/Document.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/Node.h"
#include "org/w3c/dom/Text.h"
#include "org/xml/sax/Attributes.h"
#include "org/xml/sax/ContentHandler.h"
#include "org/xml/sax/Locator.h"
#include "org/xml/sax/SAXException.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace marshaller {


class SAX2DOMEx {
public:
    Node node = nullptr;
    bool isConsolidate;
   protected const std::stack<Node> nodeStack = std::make_unique<std::stack<>>();
   private const FinalArrayList<std::string> unprocessedNamespaces = std::make_unique<FinalArrayList>();
    const Document document;

    public SAX2DOMEx(Node node) {
      this(node, false);
   }

    public SAX2DOMEx(Node node, bool isConsolidate) {
      this.node = node;
      this.isConsolidate = isConsolidate;
      this.nodeStack.push(this.node);
      if (dynamic_cast<Document*>(node) != nullptr) {
         this.document = (Document)node;
      } else {
         this.document = node.getOwnerDocument();
      }
   }

    public SAX2DOMEx(DocumentBuilderFactory f) {
      f.setValidating(false);
      this.document = f.newDocumentBuilder().newDocument();
      this.node = this.document;
      this.nodeStack.push(this.document);
   }

   /** @deprecated */
    public SAX2DOMEx() {
    DocumentBuilderFactory factory = XmlFactory.createDocumentBuilderFactory(false);
      factory.setValidating(false);
      this.document = factory.newDocumentBuilder().newDocument();
      this.node = this.document;
      this.nodeStack.push(this.document);
   }

    Element getCurrentElement() {
      return (Element)this.nodeStack.peek();
   }

    Node getDOM() {
      return this.node;
   }

    void startDocument() {
   }

    void endDocument() {
   }

    void namespace(Element element, const std::string& prefix, const std::string& uri) {
    std::string qname;
      if (!"" == prefix) && prefix != nullptr) {
         qname = "xmlns:" + prefix;
      } else {
         qname = "xmlns";
      }

      if (element.hasAttributeNS("http://www.w3.org/2000/xmlns/", qname)) {
         element.removeAttributeNS("http://www.w3.org/2000/xmlns/", qname);
      }

      element.setAttributeNS("http://www.w3.org/2000/xmlns/", qname, uri);
   }

    void startElement(const std::string& namespace, const std::string& localName, const std::string& qName, Attributes attrs) {
    Node parent = this.nodeStack.peek();
    Element element = this.document.createElementNS(namespace, qName);
      if (element == nullptr) {
         throw AssertionError(
            Messages.format("SAX2DOMEx.DomImplDoesntSupportCreateElementNs", this.document.getClass().getName(), Which.which(this.document.getClass()))
         );
      } else {
         for (int i = 0; i < this.unprocessedNamespaces.size(); i += 2) {
    std::string prefix = (std::string)this.unprocessedNamespaces.get(i);
    std::string uri = (std::string)this.unprocessedNamespaces.get(i + 1);
            this.namespace(element, prefix, uri);
         }

         this.unprocessedNamespaces.clear();
         if (attrs != nullptr) {
    int length = attrs.getLength();

            for (int i = 0; i < length; i++) {
    std::string namespaceuri = attrs.getURI(i);
    std::string value = attrs.getValue(i);
    std::string qname = attrs.getQName(i);
               element.setAttributeNS(namespaceuri, qname, value);
            }
         }

         parent.appendChild(element);
         this.nodeStack.push(element);
      }
   }

    void endElement(const std::string& namespace, const std::string& localName, const std::string& qName) {
      this.nodeStack.pop();
   }

    void characters(char[] ch, int start, int length) {
      this.characters(new std::string(ch, start, length));
   }

    Text characters(const std::string& s) {
    Node parent = this.nodeStack.peek();
    Node lastChild = parent.getLastChild();
    Text text;
      if (this.isConsolidate && lastChild != nullptr && lastChild.getNodeType() == 3) {
         text = (Text)lastChild;
         text.appendData(s);
      } else {
         text = this.document.createTextNode(s);
         parent.appendChild(text);
      }

    return text;
   }

    void ignorableWhitespace(char[] ch, int start, int length) {
   }

    void processingInstruction(const std::string& target, const std::string& data) {
    Node parent = this.nodeStack.peek();
    Node n = this.document.createProcessingInstruction(target, data);
      parent.appendChild(n);
   }

    void setDocumentLocator(Locator locator) {
   }

    void skippedEntity(const std::string& name) {
   }

    void startPrefixMapping(const std::string& prefix, const std::string& uri) {
      this.unprocessedNamespaces.push_back(prefix);
      this.unprocessedNamespaces.push_back(uri);
   }

    void endPrefixMapping(const std::string& prefix) {
   }
}
} // namespace marshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
