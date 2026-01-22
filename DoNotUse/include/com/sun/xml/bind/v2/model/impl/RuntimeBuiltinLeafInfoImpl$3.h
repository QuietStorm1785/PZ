#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/DatatypeConverterImpl.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/StringImpl.h"
#include "javax/xml/namespace/QName.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
   RuntimeBuiltinLeafInfoImpl$3(Class type, QName... typeNames) {
      super(type, typeNames);
   }

    Calendar parse(CharSequence text) {
      return DatatypeConverterImpl._parseDateTime(text);
   }

    std::string print(Calendar v) {
      return DatatypeConverterImpl._printDateTime(v);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
