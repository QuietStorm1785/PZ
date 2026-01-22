#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/escape/Platform/1.h"

namespace com {
namespace google {
namespace common {
namespace escape {


class Platform {
public:
   private static const ThreadLocal<char[]> DEST_TL = std::make_unique<1>();

    private Platform() {
   }

   static char[] charBufferFromThreadLocal() {
      return DEST_TL.get();
   }
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
