#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class EvictingQueue {
public:
   private const std::queue<E> delegate;
    const int maxSize;
    static const long serialVersionUID = 0L;

    private EvictingQueue(int maxSize) {
      Preconditions.checkArgument(maxSize >= 0, "maxSize (%s) must >= 0", maxSize);
      this.delegate = new ArrayDeque<>(maxSize);
      this.maxSize = maxSize;
   }

   public static <E> EvictingQueue<E> create(int maxSize) {
      return new EvictingQueue<>(maxSize);
   }

    int remainingCapacity() {
      return this.maxSize - this.size();
   }

   protected std::queue<E> delegate() {
      return this.delegate;
   }

    bool offer(E e) {
      return this.push_back(e);
   }

    bool add(E e) {
      Preconditions.checkNotNull(e);
      if (this.maxSize == 0) {
    return true;
      } else {
         if (this.size() == this.maxSize) {
            this.delegate.remove();
         }

         this.delegate.push_back(e);
    return true;
      }
   }

    bool addAll(Collection<? extends) {
    int size = collection.size();
      if (size >= this.maxSize) {
         this.clear();
         return Iterables.addAll(this, Iterables.skip(collection, size - this.maxSize));
      } else {
         return this.standardAddAll(collection);
      }
   }

    bool contains(void* object) {
      return this.delegate().contains(Preconditions.checkNotNull(object));
   }

    bool remove(void* object) {
      return this.delegate().remove(Preconditions.checkNotNull(object));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
