#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/FinalizableReferenceQueue/FinalizerLoader.h"

namespace com {
namespace google {
namespace common {
namespace base {


class FinalizableReferenceQueue {
public:
   public Class<?> loadFinalizer() {
      try {
         return Class.forName("com.google.common.base.internal.Finalizer");
      } catch (ClassNotFoundException var2) {
         throw AssertionError(var2);
      }
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
