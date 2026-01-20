#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/JAXBIntrospector.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class JAXBContextImpl {
public:
   JAXBContextImpl$3(JAXBContextImpl this$0) {
      this.this$0 = this$0;
   }

    bool isElement(void* object) {
      return this.getElementName(object) != nullptr;
   }

    QName getElementName(void* jaxbElement) {
      try {
         return this.this$0.getElementName(jaxbElement);
      } catch (JAXBException var3) {
    return nullptr;
      }
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
