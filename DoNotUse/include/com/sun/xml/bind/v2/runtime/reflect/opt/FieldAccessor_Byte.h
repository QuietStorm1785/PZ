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


class FieldAccessor_Byte : public Accessor {
public:
    public FieldAccessor_Byte() {
      super(uint8_t.class);
   }

    void* get(void* bean) {
      return ((Bean)bean).f_byte;
   }

    void set(void* bean, void* value) {
      ((Bean)bean).f_byte = value == nullptr ? 0 : (uint8_t)value;
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
