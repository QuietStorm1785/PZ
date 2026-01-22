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


class FieldAccessor_Short : public Accessor {
public:
    public FieldAccessor_Short() {
      super(int16_t.class);
   }

    void* get(void* bean) {
      return ((Bean)bean).f_short;
   }

    void set(void* bean, void* value) {
      ((Bean)bean).f_short = value == nullptr ? 0 : (int16_t)value;
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
