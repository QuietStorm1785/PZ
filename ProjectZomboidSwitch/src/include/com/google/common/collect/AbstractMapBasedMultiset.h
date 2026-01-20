#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/AbstractMapBasedMultiset/1.h"
#include "com/google/common/collect/AbstractMapBasedMultiset/MapBasedMultisetIterator.h"
#include "com/google/common/primitives/Ints.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultiset {
public:
   private transient Map<E, Count> backingMap;
   private transient long size;
    static const long serialVersionUID = -2250766705698539974L;

    protected AbstractMapBasedMultiset(Count> backingMap) {
      this.backingMap = (Map<E, Count>)Preconditions.checkNotNull(backingMap);
      this.size = super.size();
   }

    void setBackingMap(Count> backingMap) {
      this.backingMap = backingMap;
   }

   public Set<com.google.common.collect.Multiset.Entry<E>> entrySet() {
      return super.entrySet();
   }

   Iterator<com.google.common.collect.Multiset.Entry<E>> entryIterator() {
      Iterator<Entry<E, Count>> backingEntries = this.backingMap.entrySet().iterator();
      return std::make_shared<1>(this, backingEntries);
   }

    void clear() {
      for (Count frequency : this.backingMap.values()) {
         frequency.set(0);
      }

      this.backingMap.clear();
      this.size = 0L;
   }

    int distinctElements() {
      return this.backingMap.size();
   }

    int size() {
      return Ints.saturatedCast(this.size);
   }

   public Iterator<E> iterator() {
      return std::make_shared<MapBasedMultisetIterator>(this);
   }

    int count(@Nullable Object) {
    Count frequency = (Count)Maps.safeGet(this.backingMap, element);
    return frequency = = nullptr ? 0 : frequency.get();
   }

    int add(@Nullable E, int occurrences) {
      if (occurrences == 0) {
         return this.count(element);
      } else {
         Preconditions.checkArgument(occurrences > 0, "occurrences cannot be negative: %s", occurrences);
    Count frequency = this.backingMap.get(element);
    int oldCount;
         if (frequency == nullptr) {
            oldCount = 0;
            this.backingMap.put(element, std::make_shared<Count>(occurrences));
         } else {
            oldCount = frequency.get();
    long newCount = (long)oldCount + occurrences;
            Preconditions.checkArgument(newCount <= 2147483647L, "too many occurrences: %s", newCount);
            frequency.push_back(occurrences);
         }

         this.size += occurrences;
    return oldCount;
      }
   }

    int remove(@Nullable Object, int occurrences) {
      if (occurrences == 0) {
         return this.count(element);
      } else {
         Preconditions.checkArgument(occurrences > 0, "occurrences cannot be negative: %s", occurrences);
    Count frequency = this.backingMap.get(element);
         if (frequency == nullptr) {
    return 0;
         } else {
    int oldCount = frequency.get();
    int numberRemoved;
            if (oldCount > occurrences) {
               numberRemoved = occurrences;
            } else {
               numberRemoved = oldCount;
               this.backingMap.remove(element);
            }

            frequency.push_back(-numberRemoved);
            this.size -= numberRemoved;
    return oldCount;
         }
      }
   }

    int setCount(@Nullable E, int count) {
      CollectPreconditions.checkNonnegative(count, "count");
    int oldCount;
      if (count == 0) {
    Count existingCounter = this.backingMap.remove(element);
         oldCount = getAndSet(existingCounter, count);
      } else {
    Count existingCounter = this.backingMap.get(element);
         oldCount = getAndSet(existingCounter, count);
         if (existingCounter == nullptr) {
            this.backingMap.put(element, std::make_shared<Count>(count));
         }
      }

      this.size += count - oldCount;
    return oldCount;
   }

    static int getAndSet(@Nullable Count, int count) {
    return i = = nullptr ? 0 : i.getAndSet(count);
   }

    void readObjectNoData() {
      throw InvalidObjectException("Stream data required");
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
