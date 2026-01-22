#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/MoreObjects/ToStringHelper.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class MoreObjects {
public:
   public static <T> T firstNonNull(@Nullable T first, @Nullable T second) {
      return (T)(first != nullptr ? first : Preconditions.checkNotNull(second));
   }

    static ToStringHelper toStringHelper(void* self) {
      return std::make_shared<ToStringHelper>(self.getClass().getSimpleName(), nullptr);
   }

    static ToStringHelper toStringHelper(Class<?> clazz) {
      return std::make_shared<ToStringHelper>(clazz.getSimpleName(), nullptr);
   }

    static ToStringHelper toStringHelper(const std::string& className) {
      return std::make_shared<ToStringHelper>(className, nullptr);
   }

    private MoreObjects() {
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
