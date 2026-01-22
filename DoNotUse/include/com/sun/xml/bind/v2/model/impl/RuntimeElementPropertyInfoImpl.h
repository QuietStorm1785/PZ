#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/impl/RuntimeClassInfoImpl/RuntimePropertySeed.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeInfo.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeElementPropertyInfoImpl : public ElementPropertyInfoImpl {
public:
    const Accessor acc;

   RuntimeElementPropertyInfoImpl(RuntimeClassInfoImpl classInfo, PropertySeed<Type, Class, Field, Method> seed) {
      super(classInfo, seed);
    Accessor rawAcc = ((RuntimePropertySeed)seed).getAccessor();
      if (this.getAdapter() != nullptr && !this.isCollection()) {
         rawAcc = rawAcc.adapt(this.getAdapter());
      }

      this.acc = rawAcc;
   }

    Accessor getAccessor() {
      return this.acc;
   }

    bool elementOnlyContent() {
    return true;
   }

   public List<? : public RuntimeTypeInfo> ref() {
      return super.ref();
   }

    RuntimeTypeRefImpl createTypeRef(QName name, Type type, bool isNillable, const std::string& defaultValue) {
      return std::make_shared<RuntimeTypeRefImpl>(this, name, type, isNillable, defaultValue);
   }

   public List<RuntimeTypeRefImpl> getTypes() {
      return super.getTypes();
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
