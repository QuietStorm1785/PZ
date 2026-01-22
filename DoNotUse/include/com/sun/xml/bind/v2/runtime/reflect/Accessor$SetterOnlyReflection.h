#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor/GetterSetterReflection.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Accessor {
public:
   public Accessor$SetterOnlyReflection(Method setter) {
      super(nullptr, setter);
   }

    ValueT get(BeanT bean) {
      throw AccessorException(Messages.NO_GETTER.format(new Object[]{this.setter}));
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
