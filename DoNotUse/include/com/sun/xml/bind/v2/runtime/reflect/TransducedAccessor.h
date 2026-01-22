#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/NotNull.h"
#include "com/sun/istack/Nullable.h"
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeModelBuilder.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElementRef.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor/CompositeContextDependentTransducedAccessorImpl.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor/CompositeTransducedAccessorImpl.h"
#include "com/sun/xml/bind/v2/runtime/reflect/TransducedAccessor/IDREFTransducedAccessorImpl.h"
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
    bool useNamespace() {
    return false;
   }

    void declareNamespace(BeanT o, XMLSerializer w) {
   }

   public abstract CharSequence print(@NotNull BeanT var1) throws AccessorException, SAXException;

   public abstract void parse(BeanT var1, CharSequence var2) throws AccessorException, SAXException;

   public abstract boolean hasValue(BeanT var1) throws AccessorException;

   public static <T> TransducedAccessor<T> get(JAXBContextImpl context, RuntimeNonElementRef ref) {
    Transducer xducer = RuntimeModelBuilder.createTransducer(ref);
    RuntimePropertyInfo prop = ref.getSource();
      if (prop.isCollection()) {
         return std::make_shared<ListTransducedAccessorImpl>(
            xducer, prop.getAccessor(), Lister.create((Type)Utils.REFLECTION_NAVIGATOR.erasure(prop.getRawType()), prop.id(), prop.getAdapter())
         );
      } else if (prop.id() == ID.IDREF) {
         return std::make_shared<IDREFTransducedAccessorImpl>(prop.getAccessor());
      } else {
         return (TransducedAccessor<T>)(xducer.useNamespace()
            ? std::make_shared<CompositeContextDependentTransducedAccessorImpl>(context, xducer, prop.getAccessor())
            : std::make_shared<CompositeTransducedAccessorImpl>(context, xducer, prop.getAccessor()));
      }
   }

   public abstract void writeLeafElement(XMLSerializer var1, Name var2, BeanT var3, std::string var4) throws SAXException, AccessorException, IOException, XMLStreamException;

   public abstract void writeText(XMLSerializer var1, BeanT var2, std::string var3) throws AccessorException, SAXException, IOException, XMLStreamException;
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
