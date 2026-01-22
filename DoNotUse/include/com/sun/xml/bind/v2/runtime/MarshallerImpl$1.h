#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/helpers/XMLFilterImpl.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class MarshallerImpl {
public:
   MarshallerImpl$1(MarshallerImpl this$0) {
      this.this$0 = this$0;
   }

    void startPrefixMapping(const std::string& prefix, const std::string& uri) {
      super.startPrefixMapping(prefix.intern(), uri.intern());
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
