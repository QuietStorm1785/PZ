#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/PropertyException.h"
#include "javax/xml/bind/UnmarshalException.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "javax/xml/bind/Unmarshaller/Listener.h"
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"
#include "javax/xml/bind/attachment/AttachmentUnmarshaller.h"
#include "javax/xml/parsers/ParserConfigurationException.h"
#include "javax/xml/parsers/SAXParserFactory.h"
#include "javax/xml/stream/XMLEventReader.h"
#include "javax/xml/stream/XMLStreamReader.h"
#include "javax/xml/transform/Source.h"
#include "javax/xml/transform/dom/DOMSource.h"
#include "javax/xml/transform/sax/SAXSource.h"
#include "javax/xml/transform/stream/StreamSource.h"
#include "javax/xml/validation/Schema.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/InputSource.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/XMLReader.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace xml {
namespace bind {
namespace helpers {


class AbstractUnmarshallerImpl {
public:
    ValidationEventHandler eventHandler = std::make_shared<DefaultValidationEventHandler>();
    bool validating = false;
    XMLReader reader = nullptr;

    XMLReader getXMLReader() {
      if (this.reader == nullptr) {
         try {
    SAXParserFactory parserFactory = SAXParserFactory.newInstance();
            parserFactory.setNamespaceAware(true);
            parserFactory.setValidating(false);
            this.reader = parserFactory.newSAXParser().getXMLReader();
         } catch (ParserConfigurationException var2) {
            throw JAXBException(var2);
         } catch (SAXException var3) {
            throw JAXBException(var3);
         }
      }

      return this.reader;
   }

    void* unmarshal(Source source) {
      if (source == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "source"));
      } else if (dynamic_cast<SAXSource*>(source) != nullptr) {
         return this.unmarshal((SAXSource)source);
      } else if (dynamic_cast<StreamSource*>(source) != nullptr) {
         return this.unmarshal(streamSourceToInputSource((StreamSource)source));
      } else if (dynamic_cast<DOMSource*>(source) != nullptr) {
         return this.unmarshal(((DOMSource)source).getNode());
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    void* unmarshal(SAXSource source) {
    XMLReader r = source.getXMLReader();
      if (r == nullptr) {
         r = this.getXMLReader();
      }

      return this.unmarshal(r, source.getInputSource());
   }

   protected abstract Object unmarshal(XMLReader var1, InputSource var2) throws JAXBException;

    void* unmarshal(InputSource source) {
      if (source == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "source"));
      } else {
         return this.unmarshal(this.getXMLReader(), source);
      }
   }

    void* unmarshal(const std::string& url) {
      return this.unmarshal(std::make_shared<InputSource>(url));
   }

    void* unmarshal(URL url) {
      if (url == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "url"));
      } else {
         return this.unmarshal(url.toExternalForm());
      }
   }

    void* unmarshal(File f) {
      if (f == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "file"));
      } else {
         try {
            return this.unmarshal(std::make_shared<BufferedInputStream>(std::make_shared<FileInputStream>(f)));
         } catch (FileNotFoundException var3) {
            throw IllegalArgumentException(var3.getMessage());
         }
      }
   }

    void* unmarshal(InputStream is) {
      if (is == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "is"));
      } else {
    InputSource isrc = std::make_shared<InputSource>(is);
         return this.unmarshal(isrc);
      }
   }

    void* unmarshal(Reader reader) {
      if (reader == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "reader"));
      } else {
    InputSource isrc = std::make_shared<InputSource>(reader);
         return this.unmarshal(isrc);
      }
   }

    static InputSource streamSourceToInputSource(StreamSource ss) {
    InputSource is = std::make_shared<InputSource>();
      is.setSystemId(ss.getSystemId());
      is.setByteStream(ss.getInputStream());
      is.setCharacterStream(ss.getReader());
    return is;
   }

    bool isValidating() {
      return this.validating;
   }

    void setEventHandler(ValidationEventHandler handler) {
      if (handler == nullptr) {
         this.eventHandler = std::make_unique<DefaultValidationEventHandler>();
      } else {
         this.eventHandler = handler;
      }
   }

    void setValidating(bool validating) {
      this.validating = validating;
   }

    ValidationEventHandler getEventHandler() {
      return this.eventHandler;
   }

    UnmarshalException createUnmarshalException(SAXException e) {
    std::exception nested = e.getException();
      if (dynamic_cast<UnmarshalException*>(nested) != nullptr) {
         return (UnmarshalException)nested;
      } else if (dynamic_cast<RuntimeException*>(nested) != nullptr) {
         throw (RuntimeException)nested;
      } else {
         return nested != nullptr ? std::make_shared<UnmarshalException>(nested) : std::make_shared<UnmarshalException>(e);
      }
   }

    void setProperty(const std::string& name, void* value) {
      if (name == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "name"));
      } else {
         throw PropertyException(name, value);
      }
   }

    void* getProperty(const std::string& name) {
      if (name == nullptr) {
         throw IllegalArgumentException(Messages.format("Shared.MustNotBeNull", "name"));
      } else {
         throw PropertyException(name);
      }
   }

    void* unmarshal(XMLEventReader reader) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void* unmarshal(XMLStreamReader reader) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public <T> JAXBElement<T> unmarshal(Node node, Class<T> expectedType) throws JAXBException {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public <T> JAXBElement<T> unmarshal(Source source, Class<T> expectedType) throws JAXBException {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public <T> JAXBElement<T> unmarshal(XMLStreamReader reader, Class<T> expectedType) throws JAXBException {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public <T> JAXBElement<T> unmarshal(XMLEventReader reader, Class<T> expectedType) throws JAXBException {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setSchema(Schema schema) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    Schema getSchema() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setAdapter(XmlAdapter adapter) {
      if (adapter == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         this.setAdapter(adapter.getClass(), adapter);
      }
   }

   public <A : public XmlAdapter> void setAdapter(Class<A> type, A adapter) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public <A : public XmlAdapter> A getAdapter(Class<A> type) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setAttachmentUnmarshaller(AttachmentUnmarshaller au) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    AttachmentUnmarshaller getAttachmentUnmarshaller() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setListener(Listener listener) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    Listener getListener() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace helpers
} // namespace bind
} // namespace xml
} // namespace javax
