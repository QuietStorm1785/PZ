#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor/FieldReflection.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Accessor {
public:
   public Accessor$ReadOnlyFieldReflection(Field f, boolean supressAccessorWarnings) {
      super(f, supressAccessorWarnings);
   }

   public Accessor$ReadOnlyFieldReflection(Field f) {
      super(f);
   }

    void set(BeanT bean, ValueT value) {
   }

   public Accessor<BeanT, ValueT> optimize(JAXBContextImpl context) {
    return this;
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
