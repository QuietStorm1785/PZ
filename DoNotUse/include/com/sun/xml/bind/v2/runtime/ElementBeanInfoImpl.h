#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElementInfo.h"
#include "com/sun/xml/bind/v2/runtime/ElementBeanInfoImpl/1.h"
#include "com/sun/xml/bind/v2/runtime/ElementBeanInfoImpl/IntercepterLoader.h"
#include "com/sun/xml/bind/v2/runtime/property/Property.h"
#include "com/sun/xml/bind/v2/runtime/property/PropertyFactory.h"
#include "com/sun/xml/bind/v2/runtime/property/UnmarshallerChain.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Discarder.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "javax/xml/bind/JAXBElement.h"
#include "javax/xml/bind/JAXBElement/GlobalScope.h"
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


class ElementBeanInfoImpl : public JaxBeanInfo {
public:
    Loader loader;
    const Property property;
    const QName tagName;
    const Class expectedType;
    const Class scope;
   private const Constructor<? : public JAXBElement> constructor;

   ElementBeanInfoImpl(JAXBContextImpl grammar, RuntimeElementInfo rei) {
      super(grammar, rei, rei.getType(), true, false, true);
      this.property = PropertyFactory.create(grammar, rei.getProperty());
      this.tagName = rei.getElementName();
      this.expectedType = (Class)Utils.REFLECTION_NAVIGATOR.erasure(rei.getContentInMemoryType());
      this.scope = rei.getScope() == nullptr ? GlobalScope.class : (Class)rei.getScope().getClazz();
    Class type = (Class)Utils.REFLECTION_NAVIGATOR.erasure(rei.getType());
      if (type == JAXBElement.class) {
         this.constructor = nullptr;
      } else {
         try {
            this.constructor = type.getConstructor(this.expectedType);
         } catch (NoSuchMethodException var6) {
    NoSuchMethodError x = std::make_shared<NoSuchMethodError>("Failed to find the constructor for " + type + " with " + this.expectedType);
            x.initCause(var6);
    throw x;
         }
      }
   }

    protected ElementBeanInfoImpl(JAXBContextImpl grammar) {
      super(grammar, nullptr, JAXBElement.class, true, false, true);
      this.tagName = nullptr;
      this.expectedType = nullptr;
      this.scope = nullptr;
      this.constructor = nullptr;
      this.property = std::make_shared<1>(this, grammar);
   }

    std::string getElementNamespaceURI(JAXBElement e) {
      return e.getName().getNamespaceURI();
   }

    std::string getElementLocalName(JAXBElement e) {
      return e.getName().getLocalPart();
   }

    Loader getLoader(JAXBContextImpl context, bool typeSubstitutionCapable) {
      if (this.loader == nullptr) {
    UnmarshallerChain c = std::make_shared<UnmarshallerChain>(context);
         QNameMap<ChildLoader> result = std::make_unique<QNameMap>();
         this.property.buildChildElementUnmarshallers(c, result);
         if (result.size() == 1) {
            this.loader = std::make_shared<IntercepterLoader>(this, ((ChildLoader)result.getOne().getValue()).loader);
         } else {
            this.loader = Discarder.INSTANCE;
         }
      }

      return this.loader;
   }

    JAXBElement createInstance(UnmarshallingContext context) {
      return this.createInstanceFromValue(nullptr);
   }

    JAXBElement createInstanceFromValue(void* o) {
      return this.constructor == nullptr ? std::make_shared<JAXBElement>(this.tagName, this.expectedType, this.scope, o) : this.constructor.newInstance(o);
   }

    bool reset(JAXBElement e, UnmarshallingContext context) {
      e.setValue(nullptr);
    return true;
   }

    std::string getId(JAXBElement e, XMLSerializer target) {
    void* o = e.getValue();
      return dynamic_cast<std*>(o) != nullptr::string ? (std::string)o : nullptr;
   }

    void serializeBody(JAXBElement element, XMLSerializer target) {
      try {
         this.property.serializeBody(element, target, nullptr);
      } catch (AccessorException var4) {
         target.reportError(nullptr, var4);
      }
   }

    void serializeRoot(JAXBElement e, XMLSerializer target) {
      this.serializeBody(e, target);
   }

    void serializeAttributes(JAXBElement e, XMLSerializer target) {
   }

    void serializeURIs(JAXBElement e, XMLSerializer target) {
   }

   public const Transducer<JAXBElement> getTransducer() {
    return nullptr;
   }

    void wrapUp() {
      super.wrapUp();
      this.property.wrapUp();
   }

    void link(JAXBContextImpl grammar) {
      super.link(grammar);
      this.getLoader(grammar, true);
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
