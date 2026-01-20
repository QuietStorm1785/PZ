#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/JAXBElement.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Accessor {
public:
   Accessor$2(Class valueType) {
      super(valueType);
   }

    void* get(JAXBElement jaxbElement) {
      return jaxbElement.getValue();
   }

    void set(JAXBElement jaxbElement, void* o) {
      jaxbElement.setValue(o);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
