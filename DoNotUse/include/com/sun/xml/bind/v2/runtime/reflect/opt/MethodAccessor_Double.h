#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {
namespace opt {


class MethodAccessor_Double : public Accessor {
public:
    public MethodAccessor_Double() {
      super(double.class);
   }

    void* get(void* bean) {
      return ((Bean)bean).get_double();
   }

    void set(void* bean, void* value) {
      ((Bean)bean).set_double(value == nullptr ? 0.0 : (double)value);
   }
}
} // namespace opt
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
