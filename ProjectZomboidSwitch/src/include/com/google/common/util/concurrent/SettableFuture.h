#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/util/concurrent/AbstractFuture/TrustedFuture.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class SettableFuture {
public:
   public static <V> SettableFuture<V> create() {
      return std::make_unique<SettableFuture<>>();
   }

    bool set(@Nullable V) {
      return super.set(value);
   }

    bool setException(std::exception throwable) {
      return super.setException(throwable);
   }

    bool setFuture(ListenableFuture<? extends) {
      return super.setFuture(future);
   }

    private SettableFuture() {
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
