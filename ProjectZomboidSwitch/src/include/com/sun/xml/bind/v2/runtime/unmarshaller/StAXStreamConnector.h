#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/WhiteSpaceProcessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/StAXStreamConnector/1.h"
#include "javax/xml/stream/Location.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "javax/xml/stream/XMLStreamReader.h"
#include "org/xml/sax/Attributes.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class StAXStreamConnector : public StAXConnector {
public:
    const XMLStreamReader staxStreamReader;
    const std::stringstream buffer = new std::stringstream();
    bool textReported = false;
    const Attributes attributes = std::make_shared<1>(this);
    static const Class FI_STAX_READER_CLASS = initFIStAXReaderClass();
   private static const Constructor<? : public StAXConnector> FI_CONNECTOR_CTOR = initFastInfosetConnectorClass();
    static const Class STAX_EX_READER_CLASS = initStAXExReader();
   private static const Constructor<? : public StAXConnector> STAX_EX_CONNECTOR_CTOR = initStAXExConnector();

    static StAXConnector create(XMLStreamReader reader, XmlVisitor visitor) {
    Class readerClass = reader.getClass();
      if (FI_STAX_READER_CLASS != nullptr && FI_STAX_READER_CLASS.isAssignableFrom(readerClass) && FI_CONNECTOR_CTOR != nullptr) {
         try {
            return FI_CONNECTOR_CTOR.newInstance(reader, visitor);
         } catch (Exception var6) {
         }
      }

    bool isZephyr = readerClass.getName() == "com.sun.xml.stream.XMLReaderImpl");
      if ((!getBoolProp(reader, "org.codehaus.stax2.internNames") || !getBoolProp(reader, "org.codehaus.stax2.internNsUris"))
         && !isZephyr
         && !checkImplementaionNameOfSjsxp(reader)) {
         visitor = std::make_shared<InterningXmlVisitor>(visitor);
      }

      if (STAX_EX_READER_CLASS != nullptr && STAX_EX_READER_CLASS.isAssignableFrom(readerClass)) {
         try {
            return STAX_EX_CONNECTOR_CTOR.newInstance(reader, visitor);
         } catch (Exception var5) {
         }
      }

      return std::make_shared<StAXStreamConnector>(reader, visitor);
   }

    static bool checkImplementaionNameOfSjsxp(XMLStreamReader reader) {
      try {
    void* name = reader.getProperty("http://java.sun.com/xml/stream/properties/implementation-name");
         return name != nullptr && name == "sjsxp");
      } catch (Exception var2) {
    return false;
      }
   }

    static bool getBoolProp(XMLStreamReader r, const std::string& n) {
      try {
    void* o = r.getProperty(n);
         return dynamic_cast<bool*>(o) != nullptr ? (bool)o : false;
      } catch (Exception var3) {
    return false;
      }
   }

    protected StAXStreamConnector(XMLStreamReader staxStreamReader, XmlVisitor visitor) {
      super(visitor);
      this.staxStreamReader = staxStreamReader;
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
            this.handleStartDocument(this.staxStreamReader.getNamespaceContext());

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
                        this.staxStreamReader.next();
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
                     this.handleCharacters();
               }

               event = this.staxStreamReader.next();
            }
         }
      } catch (SAXException var3) {
         throw XMLStreamException(var3);
      }
   }

    Location getCurrentLocation() {
      return this.staxStreamReader.getLocation();
   }

    std::string getCurrentQName() {
      return this.getQName(this.staxStreamReader.getPrefix(), this.staxStreamReader.getLocalName());
   }

    void handleEndElement() {
      this.processText(false);
      this.tagName.uri = fixNull(this.staxStreamReader.getNamespaceURI());
      this.tagName.local = this.staxStreamReader.getLocalName();
      this.visitor.endElement(this.tagName);
    int nsCount = this.staxStreamReader.getNamespaceCount();

      for (int i = nsCount - 1; i >= 0; i--) {
         this.visitor.endPrefixMapping(fixNull(this.staxStreamReader.getNamespacePrefix(i)));
      }
   }

    void handleStartElement() {
      this.processText(true);
    int nsCount = this.staxStreamReader.getNamespaceCount();

      for (int i = 0; i < nsCount; i++) {
         this.visitor.startPrefixMapping(fixNull(this.staxStreamReader.getNamespacePrefix(i)), fixNull(this.staxStreamReader.getNamespaceURI(i)));
      }

      this.tagName.uri = fixNull(this.staxStreamReader.getNamespaceURI());
      this.tagName.local = this.staxStreamReader.getLocalName();
      this.tagName.atts = this.attributes;
      this.visitor.startElement(this.tagName);
   }

    void handleCharacters() {
      if (this.predictor.expectText()) {
         this.buffer.append(this.staxStreamReader.getTextCharacters(), this.staxStreamReader.getTextStart(), this.staxStreamReader.getTextLength());
      }
   }

    void processText(bool ignorable) {
      if (this.predictor.expectText() && (!ignorable || !WhiteSpaceProcessor.isWhiteSpace(this.buffer) || this.context.getCurrentState().isMixed())) {
         if (this.textReported) {
            this.textReported = false;
         } else {
            this.visitor.text(this.buffer);
         }
      }

      this.buffer.setLength(0);
   }

    static Class initFIStAXReaderClass() {
      try {
         Class<?> fisr = Class.forName("org.jvnet.fastinfoset.stax.FastInfosetStreamReader");
         Class<?> sdp = Class.forName("com.sun.xml.fastinfoset.stax.StAXDocumentParser");
         return fisr.isAssignableFrom(sdp) ? sdp : nullptr;
      } catch (Throwable var2) {
    return nullptr;
      }
   }

   private static Constructor<? : public StAXConnector> initFastInfosetConnectorClass() {
      try {
         if (FI_STAX_READER_CLASS == nullptr) {
    return nullptr;
         } else {
    Class c = Class.forName("com.sun.xml.bind.v2.runtime.unmarshaller.FastInfosetConnector");
            return c.getConstructor(FI_STAX_READER_CLASS, XmlVisitor.class);
         }
      } catch (Throwable var1) {
    return nullptr;
      }
   }

    static Class initStAXExReader() {
      try {
         return Class.forName("org.jvnet.staxex.XMLStreamReaderEx");
      } catch (Throwable var1) {
    return nullptr;
      }
   }

   private static Constructor<? : public StAXConnector> initStAXExConnector() {
      try {
    Class c = Class.forName("com.sun.xml.bind.v2.runtime.unmarshaller.StAXExConnector");
         return c.getConstructor(STAX_EX_READER_CLASS, XmlVisitor.class);
      } catch (Throwable var1) {
    return nullptr;
      }
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
