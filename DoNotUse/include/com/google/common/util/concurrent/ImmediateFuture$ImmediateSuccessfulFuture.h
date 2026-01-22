#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ImmediateFuture {
public:
   static const ImmediateFuture$ImmediateSuccessfulFuture<Object> NULL = new ImmediateFuture$ImmediateSuccessfulFuture<>(nullptr);
    const V value;

   ImmediateFuture$ImmediateSuccessfulFuture(@Nullable V value) {
      this.value = value;
   }

    V get() {
      return this.value;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
