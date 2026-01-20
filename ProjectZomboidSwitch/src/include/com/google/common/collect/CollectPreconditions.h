#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class CollectPreconditions {
public:
    static void checkEntryNotNull(void* key, void* value) {
      if (key == nullptr) {
         throw NullPointerException("nullptr key in entry: nullptr=" + value);
      } else if (value == nullptr) {
         throw NullPointerException("nullptr value in entry: " + key + "=nullptr");
      }
   }

    static int checkNonnegative(int value, const std::string& name) {
      if (value < 0) {
         throw IllegalArgumentException(name + " cannot be negative but was: " + value);
      } else {
    return value;
      }
   }

    static void checkPositive(int value, const std::string& name) {
      if (value <= 0) {
         throw IllegalArgumentException(name + " must be positive but was: " + value);
      }
   }

    static void checkRemove(bool canRemove) {
      Preconditions.checkState(canRemove, "no calls to next() since the last call to remove()");
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
