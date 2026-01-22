#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/ValueReference.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    void* get() {
    return nullptr;
   }

    int getWeight() {
    return 0;
   }

   public ReferenceEntry<Object, Object> getEntry() {
    return nullptr;
   }

   public ValueReference<Object, Object> copyFor(ReferenceQueue<Object> queue, @Nullable Object value, ReferenceEntry<Object, Object> entry) {
    return this;
   }

    bool isLoading() {
    return false;
   }

    bool isActive() {
    return false;
   }

    void* waitForValue() {
    return nullptr;
   }

    void notifyNewValue(void* newValue) {
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
