#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/reflect/TypeToken/TypeCollector.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   TypeToken$TypeCollector$2() {
      super(nullptr);
   }

   Class<?> getRawType(Class<?> type) {
    return type;
   }

   Iterable<? : public Class<?>> getInterfaces(Class<?> type) {
      return Arrays.asList(type.getInterfaces());
   }

   Class<?> getSuperclass(Class<?> type) {
      return type.getSuperclass();
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
