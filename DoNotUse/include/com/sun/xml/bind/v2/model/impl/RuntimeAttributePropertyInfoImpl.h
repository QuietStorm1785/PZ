#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/runtime/RuntimeAttributePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElement.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeAttributePropertyInfoImpl : public AttributePropertyInfoImpl {
public:
   RuntimeAttributePropertyInfoImpl(RuntimeClassInfoImpl classInfo, PropertySeed<Type, Class, Field, Method> seed) {
      super(classInfo, seed);
   }

    bool elementOnlyContent() {
    return true;
   }

    RuntimeNonElement getTarget() {
      return (RuntimeNonElement)super.getTarget();
   }

   public List<? : public RuntimeNonElement> ref() {
      return super.ref();
   }

    RuntimePropertyInfo getSource() {
    return this;
   }

    void link() {
      this.getTransducer();
      super.link();
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
