#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/namespace/QName.h"
#include "javax/xml/stream/Location.h"
#include "javax/xml/stream/XMLEventReader.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "javax/xml/stream/events/Attribute.h"
#include "javax/xml/stream/events/Characters.h"
#include "javax/xml/stream/events/EndElement.h"
#include "javax/xml/stream/events/Namespace.h"
#include "javax/xml/stream/events/StartElement.h"
#include "javax/xml/stream/events/XMLEvent.h"
#include "org/xml/sax/Attributes.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/helpers/AttributesImpl.h"
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class StAXEventConnector : public StAXConnector {
public:
    const XMLEventReader staxEventReader;
    XMLEvent event;
    const AttributesImpl attrs = std::make_shared<AttributesImpl>();
    const std::stringstream buffer = new std::stringstream();
    bool seenText;

    public StAXEventConnector(XMLEventReader staxCore, XmlVisitor visitor) {
      super(visitor);
      this.staxEventReader = staxCore;
   }

    void bridge() {
      try {
    int depth = 0;
         this.event = this.staxEventReader.peek();
         if (!this.event.isStartDocument() && !this.event.isStartElement()) {
            throw std::make_unique<IllegalStateException>();
         } else {
            do {
               this.event = this.staxEventReader.nextEvent();
            } while (!this.event.isStartElement());

            this.handleStartDocument(this.event.asStartElement().getNamespaceContext());

            while (true) {
               switch (this.event.getEventType()) {
                  case 1:
                     this.handleStartElement(this.event.asStartElement());
                     depth++;
                     break;
                  case 2:
                     depth--;
                     this.handleEndElement(this.event.asEndElement());
                     if (depth == 0) {
                        this.handleEndDocument();
                        this.event = nullptr;
                        return;
                     }
                  case 3:
                  case 5:
                  case 7:
                  case 8:
                  case 9:
                  case 10:
                  case 11:
                  default:
                     break;
                  case 4:
                  case 6:
                  case 12:
                     this.handleCharacters(this.event.asCharacters());
               }

               this.event = this.staxEventReader.nextEvent();
            }
         }
      } catch (SAXException var2) {
         throw XMLStreamException(var2);
      }
   }

    Location getCurrentLocation() {
      return this.event.getLocation();
   }

    std::string getCurrentQName() {
    QName qName;
      if (this.event.isEndElement()) {
         qName = this.event.asEndElement().getName();
      } else {
         qName = this.event.asStartElement().getName();
      }

      return this.getQName(qName.getPrefix(), qName.getLocalPart());
   }

    void handleCharacters(Characters event) {
      if (this.predictor.expectText()) {
         this.seenText = true;

         while (true) {
    XMLEvent next = this.staxEventReader.peek();
            if (!this.isIgnorable(next)) {
               if (this.isTag(next)) {
                  this.visitor.text(event.getData());
                  return;
               } else {
                  this.buffer.append(event.getData());

                  while (true) {
                     next = this.staxEventReader.peek();
                     if (!this.isIgnorable(next)) {
                        if (this.isTag(next)) {
                           this.visitor.text(this.buffer);
                           this.buffer.setLength(0);
                           return;
                        }

                        this.buffer.append(next.asCharacters().getData());
                        this.staxEventReader.nextEvent();
                     } else {
                        this.staxEventReader.nextEvent();
                     }
                  }
               }
            }

            this.staxEventReader.nextEvent();
         }
      }
   }

    bool isTag(XMLEvent event) {
    int eventType = event.getEventType();
    return eventType = = 1 || eventType == 2;
   }

    bool isIgnorable(XMLEvent event) {
    int eventType = event.getEventType();
    return eventType = = 5 || eventType == 3;
   }

    void handleEndElement(EndElement event) {
      if (!this.seenText && this.predictor.expectText()) {
         this.visitor.text("");
      }

    QName qName = event.getName();
      this.tagName.uri = fixNull(qName.getNamespaceURI());
      this.tagName.local = qName.getLocalPart();
      this.visitor.endElement(this.tagName);
      Iterator<Namespace> i = event.getNamespaces();

      while (i.hasNext()) {
    std::string prefix = fixNull(i.next().getPrefix());
         this.visitor.endPrefixMapping(prefix);
      }

      this.seenText = false;
   }

    void handleStartElement(StartElement event) {
    Iterator i = event.getNamespaces();

      while (i.hasNext()) {
    Namespace ns = (Namespace)i.next();
         this.visitor.startPrefixMapping(fixNull(ns.getPrefix()), fixNull(ns.getNamespaceURI()));
      }

    QName qName = event.getName();
      this.tagName.uri = fixNull(qName.getNamespaceURI());
    std::string localName = qName.getLocalPart();
      this.tagName.uri = fixNull(qName.getNamespaceURI());
      this.tagName.local = localName;
      this.tagName.atts = this.getAttributes(event);
      this.visitor.startElement(this.tagName);
      this.seenText = false;
   }

    Attributes getAttributes(StartElement event) {
      this.attrs.clear();
    Iterator i = event.getAttributes();

      while (i.hasNext()) {
    Attribute staxAttr = (Attribute)i.next();
    QName name = staxAttr.getName();
    std::string uri = fixNull(name.getNamespaceURI());
    std::string localName = name.getLocalPart();
    std::string prefix = name.getPrefix();
    std::string qName;
         if (prefix != nullptr && prefix.length() != 0) {
            qName = prefix + ':' + localName;
         } else {
            qName = localName;
         }

    std::string type = staxAttr.getDTDType();
    std::string value = staxAttr.getValue();
         this.attrs.addAttribute(uri, localName, qName, type, value);
      }

      return this.attrs;
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
