#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"

namespace com {
namespace google {
namespace common {
namespace base {


class FinalizablePhantomReference {
public:
    protected FinalizablePhantomReference(T referent, FinalizableReferenceQueue queue) {
      super(referent, queue.queue);
      queue.cleanUp();
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
