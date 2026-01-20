#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/reflect/TypeToken/TypeCollector.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   TypeToken$TypeCollector$1() {
      super(nullptr);
   }

   Class<?> getRawType(TypeToken<?> type) {
      return type.getRawType();
   }

   Iterable<? : public TypeToken<?>> getInterfaces(TypeToken<?> type) {
      return type.getGenericInterfaces();
   }

   TypeToken<?> getSuperclass(TypeToken<?> type) {
      return type.getGenericSuperclass();
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
