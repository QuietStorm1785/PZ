#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class RemovalNotification {
public:
    const RemovalCause cause;
    static const long serialVersionUID = 0L;

   public static <K, V> RemovalNotification<K, V> create(@Nullable K key, @Nullable V value, RemovalCause cause) {
      return new RemovalNotification<>(key, value, cause);
   }

    private RemovalNotification(@Nullable K, @Nullable V, RemovalCause cause) {
      super(key, value);
      this.cause = (RemovalCause)Preconditions.checkNotNull(cause);
   }

    RemovalCause getCause() {
      return this.cause;
   }

    bool wasEvicted() {
      return this.cause.wasEvicted();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
