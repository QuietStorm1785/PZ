#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeInfo.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/DomLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XsiTypeLoader.h"
#include "javax/xml/bind/annotation/W3CDomHandler.h"
#include "javax/xml/bind/helpers/ValidationEventImpl.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/w3c/dom/Attr.h"
#include "org/w3c/dom/Element.h"
#include "org/w3c/dom/NamedNodeMap.h"
#include "org/w3c/dom/Node.h"
#include "org/w3c/dom/NodeList.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class AnyTypeBeanInfo : public JaxBeanInfo {
public:
    bool nilIncluded = false;
    static const W3CDomHandler domHandler = std::make_shared<W3CDomHandler>();
    static const DomLoader domLoader = std::make_shared<DomLoader>(domHandler);
    const XsiTypeLoader substLoader = std::make_shared<XsiTypeLoader>(this);

    public AnyTypeBeanInfo(JAXBContextImpl grammar, RuntimeTypeInfo anyTypeInfo) {
      super(grammar, anyTypeInfo, Object.class, std::make_shared<QName>("http://www.w3.org/2001/XMLSchema", "anyType"), false, true, false);
   }

    std::string getElementNamespaceURI(void* element) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    std::string getElementLocalName(void* element) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void* createInstance(UnmarshallingContext context) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool reset(void* element, UnmarshallingContext context) {
    return false;
   }

    std::string getId(void* element, XMLSerializer target) {
    return nullptr;
   }

    void serializeBody(void* element, XMLSerializer target) {
    NodeList childNodes = ((Element)element).getChildNodes();
    int len = childNodes.getLength();

      for (int i = 0; i < len; i++) {
    Node child = childNodes.item(i);
         switch (child.getNodeType()) {
            case 1:
               target.writeDom((Element)child, domHandler, nullptr, nullptr);
            case 2:
            default:
               break;
            case 3:
            case 4:
               target.text(child.getNodeValue(), nullptr);
         }
      }
   }

    void serializeAttributes(void* element, XMLSerializer target) {
    NamedNodeMap al = ((Element)element).getAttributes();
    int len = al.getLength();

      for (int i = 0; i < len; i++) {
    Attr a = (Attr)al.item(i);
    std::string uri = a.getNamespaceURI();
         if (uri == nullptr) {
            uri = "";
         }

    std::string local = a.getLocalName();
    std::string name = a.getName();
         if (local == nullptr) {
            local = name;
         }

         if (uri == "http://www.w3.org/2001/XMLSchema-instance") && "nil" == local)) {
            this.isNilIncluded = true;
         }

         if (!name.startsWith("xmlns")) {
            target.attribute(uri, local, a.getValue());
         }
      }
   }

    void serializeRoot(void* element, XMLSerializer target) {
      target.reportError(std::make_shared<ValidationEventImpl>(1, Messages.UNABLE_TO_MARSHAL_NON_ELEMENT.format(new Object[]{element.getClass().getName()}), nullptr, nullptr));
   }

    void serializeURIs(void* element, XMLSerializer target) {
    NamedNodeMap al = ((Element)element).getAttributes();
    int len = al.getLength();
    NamespaceContext2 context = target.getNamespaceContext();

      for (int i = 0; i < len; i++) {
    Attr a = (Attr)al.item(i);
         if ("xmlns" == a.getPrefix())) {
            context.force(a.getValue(), a.getLocalName());
         } else if ("xmlns" == a.getName())) {
            if (dynamic_cast<Element*>(element) != nullptr) {
               context.declareNamespace(a.getValue(), nullptr, false);
            } else {
               context.force(a.getValue(), "");
            }
         } else {
    std::string nsUri = a.getNamespaceURI();
            if (nsUri != nullptr && nsUri.length() > 0) {
               context.declareNamespace(nsUri, a.getPrefix(), true);
            }
         }
      }
   }

   public Transducer<Object> getTransducer() {
    return nullptr;
   }

    Loader getLoader(JAXBContextImpl context, bool typeSubstitutionCapable) {
      return (Loader)(typeSubstitutionCapable ? this.substLoader : domLoader);
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
