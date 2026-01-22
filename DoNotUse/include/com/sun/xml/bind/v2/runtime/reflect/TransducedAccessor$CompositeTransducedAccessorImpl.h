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
   protected const Transducer<ValueT> xducer;
   protected const Accessor<BeanT, ValueT> acc;

   public TransducedAccessor$CompositeTransducedAccessorImpl(JAXBContextImpl context, Transducer<ValueT> xducer, Accessor<BeanT, ValueT> acc) {
      this.xducer = xducer;
      this.acc = acc.optimize(context);
   }

    CharSequence print(BeanT bean) {
    ValueT o = (ValueT)this.acc.get(bean);
    return o = = nullptr ? nullptr : this.xducer.print(o);
   }

    void parse(BeanT bean, CharSequence lexical) {
      this.acc.set(bean, this.xducer.parse(lexical));
   }

    bool hasValue(BeanT bean) {
      return this.acc.getUnadapted(bean) != nullptr;
   }

    void writeLeafElement(XMLSerializer w, Name tagName, BeanT o, const std::string& fieldName) {
      this.xducer.writeLeafElement(w, tagName, this.acc.get(o), fieldName);
   }

    void writeText(XMLSerializer w, BeanT o, const std::string& fieldName) {
      this.xducer.writeText(w, this.acc.get(o), fieldName);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
