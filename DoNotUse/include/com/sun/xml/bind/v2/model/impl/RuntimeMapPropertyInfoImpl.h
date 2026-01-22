#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/impl/RuntimeClassInfoImpl/RuntimePropertySeed.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeMapPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElement.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeInfo.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeMapPropertyInfoImpl : public MapPropertyInfoImpl {
public:
    const Accessor acc;

   RuntimeMapPropertyInfoImpl(RuntimeClassInfoImpl classInfo, PropertySeed<Type, Class, Field, Method> seed) {
      super(classInfo, seed);
      this.acc = ((RuntimePropertySeed)seed).getAccessor();
   }

    Accessor getAccessor() {
      return this.acc;
   }

    bool elementOnlyContent() {
    return true;
   }

    RuntimeNonElement getKeyType() {
      return (RuntimeNonElement)super.getKeyType();
   }

    RuntimeNonElement getValueType() {
      return (RuntimeNonElement)super.getValueType();
   }

   public List<? : public RuntimeTypeInfo> ref() {
      return (List<? : public RuntimeTypeInfo>)super.ref();
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
