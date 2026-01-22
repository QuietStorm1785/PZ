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

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
   RuntimeBuiltinLeafInfoImpl$19(Class type, QName... typeNames) {
      super(type, typeNames);
   }

    long parse(CharSequence text) {
      return DatatypeConverterImpl._parseLong(text);
   }

    std::string print(long v) {
      return DatatypeConverterImpl._printLong(v);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
