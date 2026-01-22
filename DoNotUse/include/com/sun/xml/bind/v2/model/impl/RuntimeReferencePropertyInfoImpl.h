#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/impl/RuntimeClassInfoImpl/RuntimePropertySeed.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElement.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeReferencePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeReferencePropertyInfoImpl : public ReferencePropertyInfoImpl {
public:
    const Accessor acc;

    public RuntimeReferencePropertyInfoImpl(RuntimeClassInfoImpl classInfo, Method> seed) {
      super(classInfo, seed);
    Accessor rawAcc = ((RuntimePropertySeed)seed).getAccessor();
      if (this.getAdapter() != nullptr && !this.isCollection()) {
         rawAcc = rawAcc.adapt(this.getAdapter());
      }

      this.acc = rawAcc;
   }

   public Set<? : public RuntimeElement> getElements() {
      return super.getElements();
   }

   public Set<? : public RuntimeElement> ref() {
      return super.ref();
   }

    Accessor getAccessor() {
      return this.acc;
   }

    bool elementOnlyContent() {
      return !this.isMixed();
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
