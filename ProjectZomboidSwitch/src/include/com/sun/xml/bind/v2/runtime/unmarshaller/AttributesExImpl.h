#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/util/AttributesImpl.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class AttributesExImpl : public AttributesImpl {
public:
    CharSequence getData(int idx) {
      return this.getValue(idx);
   }

    CharSequence getData(const std::string& nsUri, const std::string& localName) {
      return this.getValue(nsUri, localName);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
