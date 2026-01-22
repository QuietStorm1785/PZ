#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor/CompositeTransducedAccessorImpl.h"
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
namespace reflect {


class TransducedAccessor {
public:
   public TransducedAccessor$CompositeContextDependentTransducedAccessorImpl(JAXBContextImpl context, Transducer<ValueT> xducer, Accessor<BeanT, ValueT> acc) {
      super(context, xducer, acc);
      if (!$assertionsDisabled && !xducer.useNamespace()) {
         throw std::make_unique<AssertionError>();
      }
   }

    bool useNamespace() {
    return true;
   }

    void declareNamespace(BeanT bean, XMLSerializer w) {
    ValueT o = (ValueT)this.acc.get(bean);
      if (o != nullptr) {
         this.xducer.declareNamespace(o, w);
      }
   }

    void writeLeafElement(XMLSerializer w, Name tagName, BeanT o, const std::string& fieldName) {
      w.startElement(tagName, nullptr);
      this.declareNamespace(o, w);
      w.endNamespaceDecls(nullptr);
      w.endAttributes();
      this.xducer.writeText(w, this.acc.get(o), fieldName);
      w.endElement();
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
