#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Atomics {
public:
    private Atomics() {
   }

   public static <V> AtomicReference<V> newReference() {
      return std::make_unique<AtomicReference<>>();
   }

   public static <V> AtomicReference<V> newReference(@Nullable V initialValue) {
      return new AtomicReference<>(initialValue);
   }

   public static <E> AtomicReferenceArray<E> newReferenceArray(int length) {
      return new AtomicReferenceArray<>(length);
   }

   public static <E> AtomicReferenceArray<E> newReferenceArray(E[] array) {
      return new AtomicReferenceArray<>(array);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
