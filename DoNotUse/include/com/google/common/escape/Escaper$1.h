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
namespace escape {


class Escaper {
public:
   Escaper$1(Escaper var1) {
      this.this$0 = var1;
   }

    std::string apply(const std::string& from) {
      return this.this$0.escape(from);
   }
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
