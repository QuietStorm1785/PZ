#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"

namespace com {
namespace google {
namespace common {
namespace net {


class MediaType {
public:
   MediaType$2(MediaType var1) {
      this.this$0 = var1;
   }

    std::string apply(const std::string& value) {
      return MediaType.access$000().matchesAllOf(value) ? value : MediaType.access$100(value);
   }
}
} // namespace net
} // namespace common
} // namespace google
} // namespace com
