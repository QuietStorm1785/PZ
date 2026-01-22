#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/IDResolver.h"
#include "com/sun/xml/bind/api/ClassResolver.h"
#include "com/sun/xml/bind/unmarshaller/DOMScanner.h"
#include "com/sun/xml/bind/unmarshaller/InfosetScanner.h"
#include "com/sun/xml/bind/unmarshaller/Messages.h"
#include "com/sun/xml/bind/v2/ClassFactory.h"
#include "com/sun/xml/bind/v2/runtime/AssociationMap.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
#include "com/sun/xml/bind/v2/util/XmlFactory.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/PropertyException.h"
#include "javax/xml/bind/UnmarshalException.h"
#include "javax/xml/bind/Unmarshaller/Listener.h"
#include "javax/xml/bind/UnmarshallerHandler.h"
#include "javax/xml/bind/ValidationEvent.h"
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"
#include "javax/xml/bind/attachment/AttachmentUnmarshaller.h"
#include "javax/xml/bind/helpers/AbstractUnmarshallerImpl.h"
#include "javax/xml/parsers/ParserConfigurationException.h"
#include "javax/xml/parsers/SAXParserFactory.h"
#include "javax/xml/stream/XMLEventReader.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "javax/xml/stream/XMLStreamReader.h"
#include "javax/xml/stream/events/XMLEvent.h"
#include "javax/xml/transform/Source.h"
#include "javax/xml/transform/dom/DOMSource.h"
#include "javax/xml/transform/sax/SAXSource.h"
#include "javax/xml/transform/stream/StreamSource.h"
#include "javax/xml/validation/Schema.h"
#include "org/w3c/dom/Document.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/InputSource.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/XMLReader.h"
#include "org/xml/sax/helpers/DefaultHandler.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class UnmarshallerImpl : public AbstractUnmarshallerImpl {
public:
    const JAXBContextImpl context;
    Schema schema;
    const UnmarshallingContext coordinator;
    Listener externalListener;
    AttachmentUnmarshaller attachmentUnmarshaller;
    IDResolver idResolver = std::make_shared<DefaultIDResolver>();
    XMLReader reader = nullptr;
    static const DefaultHandler dummyHandler = std::make_shared<DefaultHandler>();
    static const std::string FACTORY = "com.sun.xml.bind.ObjectFactory";

    public UnmarshallerImpl(JAXBContextImpl context, AssociationMap assoc) {
      this.context = context;
      this.coordinator = std::make_shared<UnmarshallingContext>(this, assoc);

      try {
         this.setEventHandler(this);
      } catch (JAXBException var4) {
         throw AssertionError(var4);
      }
   }

    UnmarshallerHandler getUnmarshallerHandler() {
      return this.getUnmarshallerHandler(true, nullptr);
   }

    XMLReader getXMLReader() {
      if (this.reader == nullptr) {
         try {
    SAXParserFactory parserFactory = XmlFactory.createParserFactory(this.context.disableSecurityProcessing);
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

    SAXConnector getUnmarshallerHandler(bool intern, JaxBeanInfo expectedType) {
    XmlVisitor h = this.createUnmarshallerHandler(nullptr, false, expectedType);
      if (intern) {
         h = std::make_shared<InterningXmlVisitor>(h);
      }

      return std::make_shared<SAXConnector>(h, nullptr);
   }

    XmlVisitor createUnmarshallerHandler(InfosetScanner scanner, bool inplace, JaxBeanInfo expectedType) {
      this.coordinator.reset(scanner, inplace, expectedType, this.idResolver);
    XmlVisitor unmarshaller = this.coordinator;
      if (this.schema != nullptr) {
         unmarshaller = std::make_shared<ValidatingUnmarshaller>(this.schema, unmarshaller);
      }

      if (this.attachmentUnmarshaller != nullptr && this.attachmentUnmarshaller.isXOPPackage()) {
         unmarshaller = std::make_shared<MTOMDecorator>(this, unmarshaller, this.attachmentUnmarshaller);
      }

    return unmarshaller;
   }

    static bool needsInterning(XMLReader reader) {
      try {
         reader.setFeature("http://xml.org/sax/features/string-interning", true);
      } catch (SAXException var3) {
      }

      try {
         if (reader.getFeature("http://xml.org/sax/features/string-interning")) {
    return false;
         }
      } catch (SAXException var2) {
      }

    return true;
   }

    void* unmarshal(XMLReader reader, InputSource source) {
      return this.unmarshal0(reader, source, nullptr);
   }

   protected <T> JAXBElement<T> unmarshal(XMLReader reader, InputSource source, Class<T> expectedType) throws JAXBException {
      if (expectedType == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         return (JAXBElement<T>)this.unmarshal0(reader, source, this.getBeanInfo(expectedType));
      }
   }

    void* unmarshal0(XMLReader reader, InputSource source, JaxBeanInfo expectedType) {
    SAXConnector connector = this.getUnmarshallerHandler(needsInterning(reader), expectedType);
      reader.setContentHandler(connector);
      reader.setErrorHandler(this.coordinator);

      try {
         reader.parse(source);
      } catch (IOException var6) {
         this.coordinator.clearStates();
         throw UnmarshalException(var6);
      } catch (SAXException var7) {
         this.coordinator.clearStates();
         throw this.createUnmarshalException(var7);
      }

    void* result = connector.getResult();
      reader.setContentHandler(dummyHandler);
      reader.setErrorHandler(dummyHandler);
    return result;
   }

   public <T> JAXBElement<T> unmarshal(Source source, Class<T> expectedType) throws JAXBException {
      if (dynamic_cast<SAXSource*>(source) != nullptr) {
    SAXSource ss = (SAXSource)source;
    XMLReader locReader = ss.getXMLReader();
         if (locReader == nullptr) {
            locReader = this.getXMLReader();
         }

         return this.unmarshal(locReader, ss.getInputSource(), expectedType);
      } else if (dynamic_cast<StreamSource*>(source) != nullptr) {
         return this.unmarshal(this.getXMLReader(), streamSourceToInputSource((StreamSource)source), expectedType);
      } else if (dynamic_cast<DOMSource*>(source) != nullptr) {
         return this.unmarshal(((DOMSource)source).getNode(), expectedType);
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    void* unmarshal0(Source source, JaxBeanInfo expectedType) {
      if (dynamic_cast<SAXSource*>(source) != nullptr) {
    SAXSource ss = (SAXSource)source;
    XMLReader locReader = ss.getXMLReader();
         if (locReader == nullptr) {
            locReader = this.getXMLReader();
         }

         return this.unmarshal0(locReader, ss.getInputSource(), expectedType);
      } else if (dynamic_cast<StreamSource*>(source) != nullptr) {
         return this.unmarshal0(this.getXMLReader(), streamSourceToInputSource((StreamSource)source), expectedType);
      } else if (dynamic_cast<DOMSource*>(source) != nullptr) {
         return this.unmarshal0(((DOMSource)source).getNode(), expectedType);
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    ValidationEventHandler getEventHandler() {
      try {
         return super.getEventHandler();
      } catch (JAXBException var2) {
         throw std::make_unique<AssertionError>();
      }
   }

    bool hasEventHandler() {
      return this.getEventHandler() != this;
   }

   public <T> JAXBElement<T> unmarshal(Node node, Class<T> expectedType) throws JAXBException {
      if (expectedType == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         return (JAXBElement<T>)this.unmarshal0(node, this.getBeanInfo(expectedType));
      }
   }

    void* unmarshal(Node node) {
      return this.unmarshal0(node, nullptr);
   }

    void* unmarshal(SAXSource source) {
      return super.unmarshal(source);
   }

    void* unmarshal0(Node node, JaxBeanInfo expectedType) {
      try {
    DOMScanner scanner = std::make_shared<DOMScanner>();
    InterningXmlVisitor handler = std::make_shared<InterningXmlVisitor>(this.createUnmarshallerHandler(nullptr, false, expectedType));
         scanner.setContentHandler(std::make_shared<SAXConnector>(handler, scanner));
         if (node.getNodeType() == 1) {
            scanner.scan((Element)node);
         } else {
            if (node.getNodeType() != 9) {
               throw IllegalArgumentException("Unexpected node type: " + node);
            }

            scanner.scan((Document)node);
         }

    void* retVal = handler.getContext().getResult();
         handler.getContext().clearResult();
    return retVal;
      } catch (SAXException var6) {
         throw this.createUnmarshalException(var6);
      }
   }

    void* unmarshal(XMLStreamReader reader) {
      return this.unmarshal0(reader, nullptr);
   }

   public <T> JAXBElement<T> unmarshal(XMLStreamReader reader, Class<T> expectedType) throws JAXBException {
      if (expectedType == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         return (JAXBElement<T>)this.unmarshal0(reader, this.getBeanInfo(expectedType));
      }
   }

    void* unmarshal0(XMLStreamReader reader, JaxBeanInfo expectedType) {
      if (reader == nullptr) {
         throw IllegalArgumentException(Messages.format("Unmarshaller.NullReader"));
      } else {
    int eventType = reader.getEventType();
         if (eventType != 1 && eventType != 7) {
            throw IllegalStateException(Messages.format("Unmarshaller.IllegalReaderState", eventType));
         } else {
    XmlVisitor h = this.createUnmarshallerHandler(nullptr, false, expectedType);
    StAXConnector connector = StAXStreamConnector.create(reader, h);

            try {
               connector.bridge();
            } catch (XMLStreamException var7) {
    throw handleStreamException();
            }

    void* retVal = h.getContext().getResult();
            h.getContext().clearResult();
    return retVal;
         }
      }
   }

   public <T> JAXBElement<T> unmarshal(XMLEventReader reader, Class<T> expectedType) throws JAXBException {
      if (expectedType == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         return (JAXBElement<T>)this.unmarshal0(reader, this.getBeanInfo(expectedType));
      }
   }

    void* unmarshal(XMLEventReader reader) {
      return this.unmarshal0(reader, nullptr);
   }

    void* unmarshal0(XMLEventReader reader, JaxBeanInfo expectedType) {
      if (reader == nullptr) {
         throw IllegalArgumentException(Messages.format("Unmarshaller.NullReader"));
      } else {
         try {
    XMLEvent event = reader.peek();
            if (!event.isStartElement() && !event.isStartDocument()) {
               throw IllegalStateException(Messages.format("Unmarshaller.IllegalReaderState", event.getEventType()));
            } else {
    bool isZephyr = reader.getClass().getName() == "com.sun.xml.stream.XMLReaderImpl");
    XmlVisitor h = this.createUnmarshallerHandler(nullptr, false, expectedType);
               if (!isZephyr) {
                  h = std::make_shared<InterningXmlVisitor>(h);
               }

    std::make_shared<StAXEventConnector>();
               return h.getContext().getResult();
            }
         } catch (XMLStreamException var6) {
    throw handleStreamException();
         }
      }
   }

    void* unmarshal0(InputStream input, JaxBeanInfo expectedType) {
      return this.unmarshal0(this.getXMLReader(), std::make_shared<InputSource>(input), expectedType);
   }

    static JAXBException handleStreamException(XMLStreamException e) {
    std::exception ne = e.getNestedException();
      if (dynamic_cast<JAXBException*>(ne) != nullptr) {
         return (JAXBException)ne;
      } else {
         return dynamic_cast<SAXException*>(ne) != nullptr ? std::make_shared<UnmarshalException>(ne) : std::make_shared<UnmarshalException>(e);
      }
   }

    void* getProperty(const std::string& name) {
      return name == IDResolver.class.getName()) ? this.idResolver : super.getProperty(name);
   }

    void setProperty(const std::string& name, void* value) {
      if (name == "com.sun.xml.bind.ObjectFactory")) {
         this.coordinator.setFactories(value);
      } else if (name == IDResolver.class.getName())) {
         this.idResolver = (IDResolver)value;
      } else if (name == ClassResolver.class.getName())) {
         this.coordinator.classResolver = (ClassResolver)value;
      } else if (name == ClassLoader.class.getName())) {
         this.coordinator.classLoader = (ClassLoader)value;
      } else {
         super.setProperty(name, value);
      }
   }

    void setSchema(Schema schema) {
      this.schema = schema;
   }

    Schema getSchema() {
      return this.schema;
   }

    AttachmentUnmarshaller getAttachmentUnmarshaller() {
      return this.attachmentUnmarshaller;
   }

    void setAttachmentUnmarshaller(AttachmentUnmarshaller au) {
      this.attachmentUnmarshaller = au;
   }

   /** @deprecated */
    bool isValidating() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   /** @deprecated */
    void setValidating(bool validating) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public <A : public XmlAdapter> void setAdapter(Class<A> type, A adapter) {
      if (type == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         this.coordinator.putAdapter(type, adapter);
      }
   }

   public <A : public XmlAdapter> A getAdapter(Class<A> type) {
      if (type == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         return (A)(this.coordinator.containsAdapter(type) ? this.coordinator.getAdapter(type) : nullptr);
      }
   }

    UnmarshalException createUnmarshalException(SAXException e) {
      return super.createUnmarshalException(e);
   }

    bool handleEvent(ValidationEvent event) {
      return event.getSeverity() != 2;
   }

    static InputSource streamSourceToInputSource(StreamSource ss) {
    InputSource is = std::make_shared<InputSource>();
      is.setSystemId(ss.getSystemId());
      is.setByteStream(ss.getInputStream());
      is.setCharacterStream(ss.getReader());
    return is;
   }

   public <T> JaxBeanInfo<T> getBeanInfo(Class<T> clazz) throws JAXBException {
      return this.context.getBeanInfo(clazz, true);
   }

    Listener getListener() {
      return this.externalListener;
   }

    void setListener(Listener listener) {
      this.externalListener = listener;
   }

    UnmarshallingContext getContext() {
      return this.coordinator;
   }

    void finalize() {
      try {
         ClassFactory.cleanCache();
      } finally {
         super.finalize();
      }
   }

    void close() {
      ClassFactory.cleanCache();
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
