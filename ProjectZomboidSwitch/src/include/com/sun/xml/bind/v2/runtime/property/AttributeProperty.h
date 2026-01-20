#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeAttributePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/util/QNameMap.h"
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


class AttributeProperty {
public:
    const Name attName;
   public const TransducedAccessor<BeanT> xacc;
    const Accessor acc;

    public AttributeProperty(JAXBContextImpl context, RuntimeAttributePropertyInfo prop) {
      super(context, prop);
      this.attName = context.nameBuilder.createAttributeName(prop.getXmlName());
      this.xacc = TransducedAccessor.get(context, prop);
      this.acc = prop.getAccessor();
   }

    void serializeAttributes(BeanT o, XMLSerializer w) {
    CharSequence value = this.xacc.print(o);
      if (value != nullptr) {
         w.attribute(this.attName, value);
      }
   }

    void serializeURIs(BeanT o, XMLSerializer w) {
      this.xacc.declareNamespace(o, w);
   }

    bool hasSerializeURIAction() {
      return this.xacc.useNamespace();
   }

    void buildChildElementUnmarshallers(UnmarshallerChain chainElem, QNameMap<ChildLoader> handlers) {
      throw std::make_unique<IllegalStateException>();
   }

    PropertyKind getKind() {
      return PropertyKind.ATTRIBUTE;
   }

    void reset(BeanT o) {
      this.acc.set(o, nullptr);
   }

    std::string getIdValue(BeanT bean) {
      return this.xacc.print(bean);
   }

    int compareTo(AttributeProperty that) {
      return this.attName.compareTo(that.attName);
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
