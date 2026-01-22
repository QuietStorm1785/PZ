#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/XMLStreamReaderToContentHandler/1.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "javax/xml/stream/XMLStreamReader.h"
#include "org/xml/sax/Attributes.h"
#include "org/xml/sax/ContentHandler.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/helpers/AttributesImpl.h"

namespace com {
namespace sun {
namespace istack {


class XMLStreamReaderToContentHandler {
public:
    const XMLStreamReader staxStreamReader;
    const ContentHandler saxHandler;
    const bool eagerQuit;
    const bool fragment;
   private const std::string[] inscopeNamespaces;

    public XMLStreamReaderToContentHandler(XMLStreamReader staxCore, ContentHandler saxCore, bool eagerQuit, bool fragment) {
      this(staxCore, saxCore, eagerQuit, fragment, new std::string[0]);
   }

    public XMLStreamReaderToContentHandler(XMLStreamReader staxCore, ContentHandler saxCore, bool eagerQuit, bool fragment, std::string[] inscopeNamespaces) {
      this.staxStreamReader = staxCore;
      this.saxHandler = saxCore;
      this.eagerQuit = eagerQuit;
      this.fragment = fragment;
      this.inscopeNamespaces = (std::string[])inscopeNamespaces.clone();

      assert inscopeNamespaces.length % 2 == 0;
   }

    void bridge() {
      try {
    int depth = 0;
    int event = this.staxStreamReader.getEventType();
         if (event == 7) {
            while (!this.staxStreamReader.isStartElement()) {
               event = this.staxStreamReader.next();
            }
         }

         if (event != 1) {
            throw IllegalStateException("The current event is not START_ELEMENT\n but " + event);
         } else {
            this.handleStartDocument();

            for (int i = 0; i < this.inscopeNamespaces.length; i += 2) {
               this.saxHandler.startPrefixMapping(this.inscopeNamespaces[i], this.inscopeNamespaces[i + 1]);
            }

            label56:
            do {
               switch (event) {
                  case 1:
                     depth++;
                     this.handleStartElement();
                     break;
                  case 2:
                     this.handleEndElement();
                     if (--depth == 0 && this.eagerQuit) {
    break label56;
                     }
                     break;
                  case 3:
                     this.handlePI();
                     break;
                  case 4:
                     this.handleCharacters();
                     break;
                  case 5:
                     this.handleComment();
                     break;
                  case 6:
                     this.handleSpace();
                     break;
                  case 7:
                  case 8:
                  default:
                     throw InternalError("processing event: " + event);
                  case 9:
                     this.handleEntityReference();
                     break;
                  case 10:
                     this.handleAttribute();
                     break;
                  case 11:
                     this.handleDTD();
                     break;
                  case 12:
                     this.handleCDATA();
                     break;
                  case 13:
                     this.handleNamespace();
                     break;
                  case 14:
                     this.handleNotationDecl();
                     break;
                  case 15:
                     this.handleEntityDecl();
               }

               event = this.staxStreamReader.next();
            } while (depth != 0);

            for (int i = 0; i < this.inscopeNamespaces.length; i += 2) {
               this.saxHandler.endPrefixMapping(this.inscopeNamespaces[i]);
            }

            this.handleEndDocument();
         }
      } catch (SAXException var4) {
         throw XMLStreamException2(var4);
      }
   }

    void handleEndDocument() {
      if (!this.fragment) {
         this.saxHandler.endDocument();
      }
   }

    void handleStartDocument() {
      if (!this.fragment) {
         this.saxHandler.setDocumentLocator(std::make_shared<1>(this));
         this.saxHandler.startDocument();
      }
   }

    void handlePI() {
      try {
         this.saxHandler.processingInstruction(this.staxStreamReader.getPITarget(), this.staxStreamReader.getPIData());
      } catch (SAXException var2) {
         throw XMLStreamException2(var2);
      }
   }

    void handleCharacters() {
      try {
         this.saxHandler.characters(this.staxStreamReader.getTextCharacters(), this.staxStreamReader.getTextStart(), this.staxStreamReader.getTextLength());
      } catch (SAXException var2) {
         throw XMLStreamException2(var2);
      }
   }

    void handleEndElement() {
    QName qName = this.staxStreamReader.getName();

      try {
    std::string pfix = qName.getPrefix();
    std::string rawname = pfix != nullptr && pfix.length() != 0 ? pfix + ':' + qName.getLocalPart() : qName.getLocalPart();
         this.saxHandler.endElement(qName.getNamespaceURI(), qName.getLocalPart(), rawname);
    int nsCount = this.staxStreamReader.getNamespaceCount();

         for (int i = nsCount - 1; i >= 0; i--) {
    std::string prefix = this.staxStreamReader.getNamespacePrefix(i);
            if (prefix == nullptr) {
               prefix = "";
            }

            this.saxHandler.endPrefixMapping(prefix);
         }
      } catch (SAXException var7) {
         throw XMLStreamException2(var7);
      }
   }

    void handleStartElement() {
      try {
    int nsCount = this.staxStreamReader.getNamespaceCount();

         for (int i = 0; i < nsCount; i++) {
            this.saxHandler.startPrefixMapping(fixNull(this.staxStreamReader.getNamespacePrefix(i)), fixNull(this.staxStreamReader.getNamespaceURI(i)));
         }

    QName qName = this.staxStreamReader.getName();
    std::string prefix = qName.getPrefix();
    std::string rawname;
         if (prefix != nullptr && prefix.length() != 0) {
            rawname = prefix + ':' + qName.getLocalPart();
         } else {
            rawname = qName.getLocalPart();
         }

    Attributes attrs = this.getAttributes();
         this.saxHandler.startElement(qName.getNamespaceURI(), qName.getLocalPart(), rawname, attrs);
      } catch (SAXException var6) {
         throw XMLStreamException2(var6);
      }
   }

    static std::string fixNull(const std::string& s) {
    return s = = nullptr ? "" : s;
   }

    Attributes getAttributes() {
    AttributesImpl attrs = std::make_shared<AttributesImpl>();
    int eventType = this.staxStreamReader.getEventType();
      if (eventType != 10 && eventType != 1) {
         throw InternalError("getAttributes() attempting to process: " + eventType);
      } else {
         for (int i = 0; i < this.staxStreamReader.getAttributeCount(); i++) {
    std::string uri = this.staxStreamReader.getAttributeNamespace(i);
            if (uri == nullptr) {
               uri = "";
            }

    std::string localName = this.staxStreamReader.getAttributeLocalName(i);
    std::string prefix = this.staxStreamReader.getAttributePrefix(i);
    std::string qName;
            if (prefix != nullptr && prefix.length() != 0) {
               qName = prefix + ':' + localName;
            } else {
               qName = localName;
            }

    std::string type = this.staxStreamReader.getAttributeType(i);
    std::string value = this.staxStreamReader.getAttributeValue(i);
            attrs.addAttribute(uri, localName, qName, type, value);
         }

    return attrs;
      }
   }

    void handleNamespace() {
   }

    void handleAttribute() {
   }

    void handleDTD() {
   }

    void handleComment() {
   }

    void handleEntityReference() {
   }

    void handleSpace() {
   }

    void handleNotationDecl() {
   }

    void handleEntityDecl() {
   }

    void handleCDATA() {
   }
}
} // namespace istack
} // namespace sun
} // namespace com
