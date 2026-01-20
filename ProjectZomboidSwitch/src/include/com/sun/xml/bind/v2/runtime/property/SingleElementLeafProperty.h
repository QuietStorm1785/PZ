#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeRef.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/DefaultValueLoaderDecorator.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/LeafPropertyLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/LeafPropertyXsiLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Loader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/XsiNilLoader/Single.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
#include "javax/xml/bind/JAXBElement.h"
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
namespace property {


class SingleElementLeafProperty {
public:
    const Name tagName;
    const bool nillable;
    const Accessor acc;
    const std::string defaultValue;
   private const TransducedAccessor<BeanT> xacc;
    const bool improvedXsiTypeHandling;
    const bool idRef;

    public SingleElementLeafProperty(JAXBContextImpl context, RuntimeElementPropertyInfo prop) {
      super(context, prop);
    RuntimeTypeRef ref = (RuntimeTypeRef)prop.getTypes().get(0);
      this.tagName = context.nameBuilder.createElementName(ref.getTagName());

      assert this.tagName != nullptr;

      this.nillable = ref.isNillable();
      this.defaultValue = ref.getDefaultValue();
      this.acc = prop.getAccessor().optimize(context);
      this.xacc = TransducedAccessor.get(context, ref);

      assert this.xacc != nullptr;

      this.improvedXsiTypeHandling = context.improvedXsiTypeHandling;
      this.idRef = ref.getSource().id() == ID.IDREF;
   }

    void reset(BeanT o) {
      this.acc.set(o, nullptr);
   }

    std::string getIdValue(BeanT bean) {
      return this.xacc.print(bean);
   }

    void serializeBody(BeanT o, XMLSerializer w, void* outerPeer) {
    bool hasValue = this.xacc.hasValue(o);
    void* obj = nullptr;

      try {
         obj = this.acc.getUnadapted(o);
      } catch (AccessorException var7) {
      }

    Class valueType = this.acc.getValueType();
      if (this.xsiTypeNeeded(o, w, obj, valueType)) {
         w.startElement(this.tagName, outerPeer);
         w.childAsXsiType(obj, this.fieldName, w.grammar.getBeanInfo(valueType), false);
         w.endElement();
      } else if (hasValue) {
         this.xacc.writeLeafElement(w, this.tagName, o, this.fieldName);
      } else if (this.nillable) {
         w.startElement(this.tagName, nullptr);
         w.writeXsiNilTrue();
         w.endElement();
      }
   }

    bool xsiTypeNeeded(BeanT bean, XMLSerializer w, void* value, Class valueTypeClass) {
      if (!this.improvedXsiTypeHandling) {
    return false;
      } else if (this.acc.isAdapted()) {
    return false;
      } else if (value == nullptr) {
    return false;
      } else if (value.getClass() == valueTypeClass)) {
    return false;
      } else if (this.idRef) {
    return false;
      } else {
         return valueTypeClass.isPrimitive() ? false : this.acc.isValueTypeAbstractable() || this.isNillableAbstract(bean, w.grammar, value, valueTypeClass);
      }
   }

    bool isNillableAbstract(BeanT bean, JAXBContextImpl context, void* value, Class valueTypeClass) {
      if (!this.nillable) {
    return false;
      } else if (valueTypeClass != Object.class) {
    return false;
      } else if (bean.getClass() != JAXBElement.class) {
    return false;
      } else {
    JAXBElement jaxbElement = (JAXBElement)bean;
    Class valueClass = value.getClass();
    Class declaredTypeClass = jaxbElement.getDeclaredType();
         if (declaredTypeClass == valueClass)) {
    return false;
         } else if (!declaredTypeClass.isAssignableFrom(valueClass)) {
    return false;
         } else {
            return !Modifier.isAbstract(declaredTypeClass.getModifiers()) ? false : this.acc.isAbstractable(declaredTypeClass);
         }
      }
   }

    void buildChildElementUnmarshallers(UnmarshallerChain chain, QNameMap<ChildLoader> handlers) {
    Loader l = std::make_shared<LeafPropertyLoader>(this.xacc);
      if (this.defaultValue != nullptr) {
         l = std::make_shared<DefaultValueLoaderDecorator>(l, this.defaultValue);
      }

      if (this.nillable || chain.context.allNillable) {
         l = std::make_shared<Single>(l, this.acc);
      }

      if (this.improvedXsiTypeHandling) {
         l = std::make_shared<LeafPropertyXsiLoader>(l, this.xacc, this.acc);
      }

      handlers.put(this.tagName, std::make_shared<ChildLoader>(l, nullptr));
   }

    PropertyKind getKind() {
      return PropertyKind.ELEMENT;
   }

    Accessor getElementPropertyAccessor(const std::string& nsUri, const std::string& localName) {
      return this.tagName == nsUri, localName) ? this.acc : nullptr;
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
