#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/WhiteSpaceProcessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/FastInfosetConnector/CharSequenceImpl.h"
#include "com/sun/xml/fastinfoset/stax/StAXDocumentParser.h"
#include "javax/xml/stream/Location.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class FastInfosetConnector : public StAXConnector {
public:
    const StAXDocumentParser fastInfosetStreamReader;
    bool textReported;
    const Base64Data base64Data = std::make_shared<Base64Data>();
    const std::stringstream buffer = new std::stringstream();
    const CharSequenceImpl charArray = std::make_shared<CharSequenceImpl>(this);

    public FastInfosetConnector(StAXDocumentParser fastInfosetStreamReader, XmlVisitor visitor) {
      super(visitor);
      fastInfosetStreamReader.setStringInterning(true);
      this.fastInfosetStreamReader = fastInfosetStreamReader;
   }

    void bridge() {
      try {
    int depth = 0;
    int event = this.fastInfosetStreamReader.getEventType();
         if (event == 7) {
            while (!this.fastInfosetStreamReader.isStartElement()) {
               event = this.fastInfosetStreamReader.next();
            }
         }

         if (event != 1) {
            throw IllegalStateException("The current event is not START_ELEMENT\n but " + event);
         } else {
            this.handleStartDocument(this.fastInfosetStreamReader.getNamespaceContext());

            while (true) {
               switch (event) {
                  case 1:
                     this.handleStartElement();
                     depth++;
                     break;
                  case 2:
                     depth--;
                     this.handleEndElement();
                     if (depth == 0) {
                        this.fastInfosetStreamReader.next();
                        this.handleEndDocument();
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
                     if (this.predictor.expectText()) {
                        event = this.fastInfosetStreamReader.peekNext();
                        if (event == 2) {
                           this.processNonIgnorableText();
                        } else if (event == 1) {
                           this.processIgnorableText();
                        } else {
                           this.handleFragmentedCharacters();
                        }
                     }
               }

               event = this.fastInfosetStreamReader.next();
            }
         }
      } catch (SAXException var3) {
         throw XMLStreamException(var3);
      }
   }

    Location getCurrentLocation() {
      return this.fastInfosetStreamReader.getLocation();
   }

    std::string getCurrentQName() {
      return this.fastInfosetStreamReader.getNameString();
   }

    void handleStartElement() {
      this.processUnreportedText();

      for (int i = 0; i < this.fastInfosetStreamReader.accessNamespaceCount(); i++) {
         this.visitor.startPrefixMapping(this.fastInfosetStreamReader.getNamespacePrefix(i), this.fastInfosetStreamReader.getNamespaceURI(i));
      }

      this.tagName.uri = this.fastInfosetStreamReader.accessNamespaceURI();
      this.tagName.local = this.fastInfosetStreamReader.accessLocalName();
      this.tagName.atts = this.fastInfosetStreamReader.getAttributesHolder();
      this.visitor.startElement(this.tagName);
   }

    void handleFragmentedCharacters() {
      this.buffer.setLength(0);
      this.buffer
         .append(this.fastInfosetStreamReader.getTextCharacters(), this.fastInfosetStreamReader.getTextStart(), this.fastInfosetStreamReader.getTextLength());

      while (true) {
         switch (this.fastInfosetStreamReader.peekNext()) {
            case 1:
               this.processBufferedText(true);
               return;
            case 2:
               this.processBufferedText(false);
               return;
            case 3:
            case 5:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            default:
               this.fastInfosetStreamReader.next();
               break;
            case 4:
            case 6:
            case 12:
               this.fastInfosetStreamReader.next();
               this.buffer
                  .append(
                     this.fastInfosetStreamReader.getTextCharacters(),
                     this.fastInfosetStreamReader.getTextStart(),
                     this.fastInfosetStreamReader.getTextLength()
                  );
         }
      }
   }

    void handleEndElement() {
      this.processUnreportedText();
      this.tagName.uri = this.fastInfosetStreamReader.accessNamespaceURI();
      this.tagName.local = this.fastInfosetStreamReader.accessLocalName();
      this.visitor.endElement(this.tagName);

      for (int i = this.fastInfosetStreamReader.accessNamespaceCount() - 1; i >= 0; i--) {
         this.visitor.endPrefixMapping(this.fastInfosetStreamReader.getNamespacePrefix(i));
      }
   }

    void processNonIgnorableText() {
      this.textReported = true;
    bool isTextAlgorithmAplied = this.fastInfosetStreamReader.getTextAlgorithmBytes() != nullptr;
      if (isTextAlgorithmAplied && this.fastInfosetStreamReader.getTextAlgorithmIndex() == 1) {
         this.base64Data.set(this.fastInfosetStreamReader.getTextAlgorithmBytesClone(), nullptr);
         this.visitor.text(this.base64Data);
      } else {
         if (isTextAlgorithmAplied) {
            this.fastInfosetStreamReader.getText();
         }

         this.charArray.set();
         this.visitor.text(this.charArray);
      }
   }

    void processIgnorableText() {
    bool isTextAlgorithmAplied = this.fastInfosetStreamReader.getTextAlgorithmBytes() != nullptr;
      if (isTextAlgorithmAplied && this.fastInfosetStreamReader.getTextAlgorithmIndex() == 1) {
         this.base64Data.set(this.fastInfosetStreamReader.getTextAlgorithmBytesClone(), nullptr);
         this.visitor.text(this.base64Data);
         this.textReported = true;
      } else {
         if (isTextAlgorithmAplied) {
            this.fastInfosetStreamReader.getText();
         }

         this.charArray.set();
         if (!WhiteSpaceProcessor.isWhiteSpace(this.charArray)) {
            this.visitor.text(this.charArray);
            this.textReported = true;
         }
      }
   }

    void processBufferedText(bool ignorable) {
      if (!ignorable || !WhiteSpaceProcessor.isWhiteSpace(this.buffer)) {
         this.visitor.text(this.buffer);
         this.textReported = true;
      }
   }

    void processUnreportedText() {
      if (!this.textReported && this.predictor.expectText()) {
         this.visitor.text("");
      }

      this.textReported = false;
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
