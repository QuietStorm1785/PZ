#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/util/concurrent/Striped/PowerOfTwoStriped.h"
#include "com/google/common/util/concurrent/Striped/SmallLazyStriped/ArrayReference.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Striped {
public:
   const AtomicReferenceArray<ArrayReference<? : public L>> locks;
   const Supplier<L> supplier;
    const int size;
   const ReferenceQueue<L> queue = std::make_unique<ReferenceQueue<>>();

   Striped$SmallLazyStriped(int stripes, Supplier<L> supplier) {
      super(stripes);
      this.size = this.mask == -1 ? int.MAX_VALUE : this.mask + 1;
      this.locks = new AtomicReferenceArray<>(this.size);
      this.supplier = supplier;
   }

    L getAt(int index) {
      if (this.size != int.MAX_VALUE) {
         Preconditions.checkElementIndex(index, this.size());
      }

      ArrayReference<? : public L> existingRef = this.locks.get(index);
    L existing = (L)(existingRef == nullptr ? nullptr : existingRef.get());
      if (existing != nullptr) {
    return existing;
      } else {
    L created = (L)this.supplier.get();
         ArrayReference<L> newRef = std::make_shared<ArrayReference>(created, index, this.queue);

         while (!this.locks.compareAndSet(index, existingRef, newRef)) {
            existingRef = this.locks.get(index);
            existing = (L)(existingRef == nullptr ? nullptr : existingRef.get());
            if (existing != nullptr) {
    return existing;
            }
         }

         this.drainQueue();
    return created;
      }
   }

    void drainQueue() {
      Reference<? : public L> ref;
      while ((ref = this.queue.poll()) != nullptr) {
         ArrayReference<? : public L> arrayRef = (ArrayReference<? : public L>)ref;
         this.locks.compareAndSet(arrayRef.index, arrayRef, nullptr);
      }
   }

    int size() {
      return this.size;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
