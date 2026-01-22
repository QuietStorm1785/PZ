#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/DatatypeConverterImpl.h"
#include "com/sun/xml/bind/v2/runtime/reflect/DefaultTransducedAccessor.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {
namespace opt {


class TransducedAccessor_field_Float : public DefaultTransducedAccessor {
public:
    std::string print(void* o) {
      return DatatypeConverterImpl._printFloat(((Bean)o).f_float);
   }

    void parse(void* o, CharSequence lexical) {
      ((Bean)o).f_float = DatatypeConverterImpl._parseFloat(lexical);
   }

    bool hasValue(void* o) {
    return true;
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
