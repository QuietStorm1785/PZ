#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/property/Property.h"
#include "com/sun/xml/bind/v2/runtime/property/UnmarshallerChain.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class ElementBeanInfoImpl {
public:
   ElementBeanInfoImpl$1(ElementBeanInfoImpl this$0, JAXBContextImpl var2) {
      this.this$0 = this$0;
      this.val$grammar = var2;
   }

    void reset(JAXBElement o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void serializeBody(JAXBElement e, XMLSerializer target, void* outerPeer) {
    Class scope = e.getScope();
      if (e.isGlobalScope()) {
         scope = nullptr;
      }

    QName n = e.getName();
    ElementBeanInfoImpl bi = this.val$grammar.getElement(scope, n);
      if (bi == nullptr) {
    JaxBeanInfo tbi;
         try {
            tbi = this.val$grammar.getBeanInfo(e.getDeclaredType(), true);
         } catch (JAXBException var10) {
            target.reportError(nullptr, var10);
            return;
         }

    void* value = e.getValue();
         target.startElement(n.getNamespaceURI(), n.getLocalPart(), n.getPrefix(), nullptr);
         if (value == nullptr) {
            target.writeXsiNilTrue();
         } else {
            target.childAsXsiType(value, "value", tbi, false);
         }

         target.endElement();
      } else {
         try {
            ElementBeanInfoImpl.access$000(bi).serializeBody(e, target, e);
         } catch (AccessorException var9) {
            target.reportError(nullptr, var9);
         }
      }
   }

    void serializeURIs(JAXBElement o, XMLSerializer target) {
   }

    bool hasSerializeURIAction() {
    return false;
   }

    std::string getIdValue(JAXBElement o) {
    return nullptr;
   }

    PropertyKind getKind() {
      return PropertyKind.ELEMENT;
   }

    void buildChildElementUnmarshallers(UnmarshallerChain chain, QNameMap<ChildLoader> handlers) {
   }

    Accessor getElementPropertyAccessor(const std::string& nsUri, const std::string& localName) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void wrapUp() {
   }

    RuntimePropertyInfo getInfo() {
      return ElementBeanInfoImpl.access$000(this.this$0).getInfo();
   }

    bool isHiddenByOverride() {
    return false;
   }

    void setHiddenByOverride(bool hidden) {
      throw UnsupportedOperationException("Not supported on jaxbelements.");
   }

    std::string getFieldName() {
    return nullptr;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
