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


class TransducedAccessor_method_Long : public DefaultTransducedAccessor {
public:
    std::string print(void* o) {
      return DatatypeConverterImpl._printLong(((Bean)o).get_long());
   }

    void parse(void* o, CharSequence lexical) {
      ((Bean)o).set_long(DatatypeConverterImpl._parseLong(lexical));
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
