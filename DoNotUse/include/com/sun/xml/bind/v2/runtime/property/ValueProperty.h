#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeValuePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ChildLoader.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/ValuePropertyLoader.h"
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


class ValueProperty {
public:
   private const TransducedAccessor<BeanT> xacc;
   private const Accessor<BeanT, ?> acc;

    public ValueProperty(JAXBContextImpl context, RuntimeValuePropertyInfo prop) {
      super(context, prop);
      this.xacc = TransducedAccessor.get(context, prop);
      this.acc = prop.getAccessor();
   }

    void serializeBody(BeanT o, XMLSerializer w, void* outerPeer) {
      if (this.xacc.hasValue(o)) {
         this.xacc.writeText(w, o, this.fieldName);
      }
   }

    void serializeURIs(BeanT o, XMLSerializer w) {
      this.xacc.declareNamespace(o, w);
   }

    bool hasSerializeURIAction() {
      return this.xacc.useNamespace();
   }

    void buildChildElementUnmarshallers(UnmarshallerChain chainElem, QNameMap<ChildLoader> handlers) {
      handlers.put(StructureLoaderBuilder.TEXT_HANDLER, std::make_shared<ChildLoader>(std::make_shared<ValuePropertyLoader>(this.xacc), nullptr));
   }

    PropertyKind getKind() {
      return PropertyKind.VALUE;
   }

    void reset(BeanT o) {
      this.acc.set(o, nullptr);
   }

    std::string getIdValue(BeanT bean) {
      return this.xacc.print(bean);
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
