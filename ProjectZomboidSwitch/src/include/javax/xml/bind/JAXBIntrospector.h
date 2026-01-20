#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/namespace/QName.h"

namespace javax {
namespace xml {
namespace bind {


class JAXBIntrospector {
public:
   public abstract boolean isElement(Object var1);

   public abstract QName getElementName(Object var1);

    static void* getValue(void* jaxbElement) {
      return dynamic_cast<JAXBElement*>(jaxbElement) != nullptr ? ((JAXBElement)jaxbElement).getValue() : jaxbElement;
   }
}
} // namespace bind
} // namespace xml
} // namespace javax
