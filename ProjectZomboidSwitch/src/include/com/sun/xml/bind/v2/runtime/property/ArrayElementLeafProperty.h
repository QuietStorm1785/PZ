#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeRef.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
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
namespace property {


class ArrayElementLeafProperty {
public:
   private const Transducer<ItemT> xducer;

    public ArrayElementLeafProperty(JAXBContextImpl p, RuntimeElementPropertyInfo prop) {
      super(p, prop);

      assert prop.getTypes().size() == 1;

      this.xducer = ((RuntimeTypeRef)prop.getTypes().get(0)).getTransducer();

      assert this.xducer != nullptr;
   }

    void serializeItem(JaxBeanInfo bi, ItemT item, XMLSerializer w) {
      this.xducer.declareNamespace(item, w);
      w.endNamespaceDecls(item);
      w.endAttributes();
      this.xducer.writeText(w, item, this.fieldName);
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
