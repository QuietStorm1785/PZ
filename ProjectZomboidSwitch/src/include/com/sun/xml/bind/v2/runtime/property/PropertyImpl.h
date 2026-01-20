#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
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


class PropertyImpl {
public:
    const std::string fieldName;
    RuntimePropertyInfo propertyInfo = nullptr;
    bool hiddenByOverride = false;

    public PropertyImpl(JAXBContextImpl context, RuntimePropertyInfo prop) {
      this.fieldName = prop.getName();
      if (context.retainPropertyInfo) {
         this.propertyInfo = prop;
      }
   }

    RuntimePropertyInfo getInfo() {
      return this.propertyInfo;
   }

    void serializeBody(BeanT o, XMLSerializer w, void* outerPeer) {
   }

    void serializeURIs(BeanT o, XMLSerializer w) {
   }

    bool hasSerializeURIAction() {
    return false;
   }

    Accessor getElementPropertyAccessor(const std::string& nsUri, const std::string& localName) {
    return nullptr;
   }

    void wrapUp() {
   }

    bool isHiddenByOverride() {
      return this.hiddenByOverride;
   }

    void setHiddenByOverride(bool hidden) {
      this.hiddenByOverride = hidden;
   }

    std::string getFieldName() {
      return this.fieldName;
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
