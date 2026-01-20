#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/ClassFactory.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
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
namespace model {
namespace impl {


class RuntimeClassInfoImpl {
public:
   private const TransducedAccessor<BeanT> xacc;
   private const Class<BeanT> ownerClass;

   public RuntimeClassInfoImpl$TransducerImpl(Class<BeanT> ownerClass, TransducedAccessor<BeanT> xacc) {
      this.xacc = xacc;
      this.ownerClass = ownerClass;
   }

    bool useNamespace() {
      return this.xacc.useNamespace();
   }

    void declareNamespace(BeanT bean, XMLSerializer w) {
      try {
         this.xacc.declareNamespace(bean, w);
      } catch (SAXException var4) {
         throw AccessorException(var4);
      }
   }

    CharSequence print(BeanT o) {
      try {
    CharSequence value = this.xacc.print(o);
         if (value == nullptr) {
            throw AccessorException(Messages.THERE_MUST_BE_VALUE_IN_XMLVALUE.format(new Object[]{o}));
         } else {
    return value;
         }
      } catch (SAXException var3) {
         throw AccessorException(var3);
      }
   }

    BeanT parse(CharSequence lexical) {
    UnmarshallingContext ctxt = UnmarshallingContext.getInstance();
    BeanT inst;
      if (ctxt != nullptr) {
         inst = (BeanT)ctxt.createInstance(this.ownerClass);
      } else {
         inst = (BeanT)ClassFactory.create(this.ownerClass);
      }

      this.xacc.parse(inst, lexical);
    return inst;
   }

    void writeText(XMLSerializer w, BeanT o, const std::string& fieldName) {
      if (!this.xacc.hasValue(o)) {
         throw AccessorException(Messages.THERE_MUST_BE_VALUE_IN_XMLVALUE.format(new Object[]{o}));
      } else {
         this.xacc.writeText(w, o, fieldName);
      }
   }

    void writeLeafElement(XMLSerializer w, Name tagName, BeanT o, const std::string& fieldName) {
      if (!this.xacc.hasValue(o)) {
         throw AccessorException(Messages.THERE_MUST_BE_VALUE_IN_XMLVALUE.format(new Object[]{o}));
      } else {
         this.xacc.writeLeafElement(w, tagName, o, fieldName);
      }
   }

    QName getTypeName(BeanT instance) {
    return nullptr;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
