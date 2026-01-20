#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Objects/ToStringHelper.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class Objects : public ExtraObjectsMethodsForWeb {
public:
    private Objects() {
   }

    static bool equal(@Nullable Object, @Nullable Object) {
    return a = = b || a != nullptr && a == b);
   }

    static int hashCode(@Nullable Object...) {
      return Arrays.hashCode(objects);
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

   public static <T> T firstNonNull(@Nullable T first, @Nullable T second) {
      return (T)MoreObjects.firstNonNull(first, second);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
