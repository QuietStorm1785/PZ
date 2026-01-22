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


class TransducedAccessor_field_Short : public DefaultTransducedAccessor {
public:
    std::string print(void* o) {
      return DatatypeConverterImpl._printShort(((Bean)o).f_short);
   }

    void parse(void* o, CharSequence lexical) {
      ((Bean)o).f_short = DatatypeConverterImpl._parseShort(lexical);
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
