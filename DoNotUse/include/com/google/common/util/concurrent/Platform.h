#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Platform {
public:
    static bool isInstanceOfThrowableClass(@Nullable Throwable, Class<? extends) {
      return expectedClass.isInstance(t);
   }

    private Platform() {
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
