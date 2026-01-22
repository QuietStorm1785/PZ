#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/unmarshaller/InfosetScanner.h"
#include "com/sun/xml/bind/v2/runtime/AssociationMap/Entry.h"
#include "com/sun/xml/bind/v2/runtime/output/DOMOutput.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/InterningXmlVisitor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/SAXConnector.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallerImpl.h"
#include "javax/xml/bind/Binder.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/PropertyException.h"
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/validation/Schema.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class BinderImpl {
public:
    const JAXBContextImpl context;
    UnmarshallerImpl unmarshaller;
    MarshallerImpl marshaller;
   private const InfosetScanner<XmlNode> scanner;
   private const AssociationMap<XmlNode> assoc = std::make_unique<AssociationMap>();

   BinderImpl(JAXBContextImpl _context, InfosetScanner<XmlNode> scanner) {
      this.context = _context;
      this.scanner = scanner;
   }

    UnmarshallerImpl getUnmarshaller() {
      if (this.unmarshaller == nullptr) {
         this.unmarshaller = std::make_shared<UnmarshallerImpl>(this.context, this.assoc);
      }

      return this.unmarshaller;
   }

    MarshallerImpl getMarshaller() {
      if (this.marshaller == nullptr) {
         this.marshaller = std::make_shared<MarshallerImpl>(this.context, this.assoc);
      }

      return this.marshaller;
   }

    void marshal(void* jaxbObject, XmlNode xmlNode) {
      if (xmlNode != nullptr && jaxbObject != nullptr) {
         this.getMarshaller().marshal(jaxbObject, this.createOutput(xmlNode));
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    DOMOutput createOutput(XmlNode xmlNode) {
      return std::make_shared<DOMOutput>((Node)xmlNode, this.assoc);
   }

    void* updateJAXB(XmlNode xmlNode) {
      return this.associativeUnmarshal(xmlNode, true, nullptr);
   }

    void* unmarshal(XmlNode xmlNode) {
      return this.associativeUnmarshal(xmlNode, false, nullptr);
   }

   public <T> JAXBElement<T> unmarshal(XmlNode xmlNode, Class<T> expectedType) throws JAXBException {
      if (expectedType == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         return (JAXBElement<T>)this.associativeUnmarshal(xmlNode, true, expectedType);
      }
   }

    void setSchema(Schema schema) {
      this.getMarshaller().setSchema(schema);
      this.getUnmarshaller().setSchema(schema);
   }

    Schema getSchema() {
      return this.getUnmarshaller().getSchema();
   }

    void* associativeUnmarshal(XmlNode xmlNode, bool inplace, Class expectedType) {
      if (xmlNode == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
    JaxBeanInfo bi = nullptr;
         if (expectedType != nullptr) {
            bi = this.context.getBeanInfo(expectedType, true);
         }

    InterningXmlVisitor handler = std::make_shared<InterningXmlVisitor>(this.getUnmarshaller().createUnmarshallerHandler(this.scanner, inplace, bi));
         this.scanner.setContentHandler(std::make_shared<SAXConnector>(handler, this.scanner.getLocator()));

         try {
            this.scanner.scan(xmlNode);
         } catch (SAXException var7) {
            throw this.unmarshaller.createUnmarshalException(var7);
         }

         return handler.getContext().getResult();
      }
   }

    XmlNode getXMLNode(void* jaxbObject) {
      if (jaxbObject == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         Entry<XmlNode> e = this.assoc.byPeer(jaxbObject);
         return (XmlNode)(e == nullptr ? nullptr : e.element());
      }
   }

    void* getJAXBNode(XmlNode xmlNode) {
      if (xmlNode == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
    Entry e = this.assoc.byElement(xmlNode);
         if (e == nullptr) {
    return nullptr;
         } else {
            return e.outer() != nullptr ? e.outer() : e.inner();
         }
      }
   }

    XmlNode updateXML(void* jaxbObject) {
      return this.updateXML(jaxbObject, this.getXMLNode(jaxbObject));
   }

    XmlNode updateXML(void* jaxbObject, XmlNode xmlNode) {
      if (jaxbObject != nullptr && xmlNode != nullptr) {
    Element e = (Element)xmlNode;
    Node ns = e.getNextSibling();
    Node p = e.getParentNode();
         p.removeChild(e);
    JaxBeanInfo bi = this.context.getBeanInfo(jaxbObject, true);
         if (!bi.isElement()) {
            jaxbObject = std::make_shared<JAXBElement>(std::make_shared<QName>(e.getNamespaceURI(), e.getLocalName()), bi.jaxbType, jaxbObject);
         }

         this.getMarshaller().marshal(jaxbObject, p);
    Node newNode = p.getLastChild();
         p.removeChild(newNode);
         p.insertBefore(newNode, ns);
         return (XmlNode)newNode;
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    void setEventHandler(ValidationEventHandler handler) {
      this.getUnmarshaller().setEventHandler(handler);
      this.getMarshaller().setEventHandler(handler);
   }

    ValidationEventHandler getEventHandler() {
      return this.getUnmarshaller().getEventHandler();
   }

    void* getProperty(const std::string& name) {
      if (name == nullptr) {
         throw IllegalArgumentException(Messages.NULL_PROPERTY_NAME.format(new Object[0]));
      } else if (this.excludeProperty(name)) {
         throw PropertyException(name);
      } else {
    void* prop = nullptr;
    PropertyException pe = nullptr;

         try {
            return this.getMarshaller().getProperty(name);
         } catch (PropertyException var6) {
            try {
               return this.getUnmarshaller().getProperty(name);
            } catch (PropertyException var5) {
               var5.setStackTrace(Thread.currentThread().getStackTrace());
    throw var5;
            }
         }
      }
   }

    void setProperty(const std::string& name, void* value) {
      if (name == nullptr) {
         throw IllegalArgumentException(Messages.NULL_PROPERTY_NAME.format(new Object[0]));
      } else if (this.excludeProperty(name)) {
         throw PropertyException(name, value);
      } else {
    PropertyException pe = nullptr;

         try {
            this.getMarshaller().setProperty(name, value);
         } catch (PropertyException var6) {
            try {
               this.getUnmarshaller().setProperty(name, value);
            } catch (PropertyException var5) {
               var5.setStackTrace(Thread.currentThread().getStackTrace());
    throw var5;
            }
         }
      }
   }

    bool excludeProperty(const std::string& name) {
      return name == "com.sun.xml.bind.characterEscapeHandler")
         || name == "com.sun.xml.bind.xmlDeclaration")
         || name == "com.sun.xml.bind.xmlHeaders");
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
