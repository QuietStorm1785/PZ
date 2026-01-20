#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ConcurrentHashMultiset/1.h"
#include "com/google/common/collect/ConcurrentHashMultiset/2.h"
#include "com/google/common/collect/ConcurrentHashMultiset/3.h"
#include "com/google/common/collect/ConcurrentHashMultiset/EntrySet.h"
#include "com/google/common/collect/ConcurrentHashMultiset/FieldSettersHolder.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/math/IntMath.h"
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


class ConcurrentHashMultiset {
public:
   private const transient ConcurrentMap<E, AtomicInteger> countMap;
    static const long serialVersionUID = 1L;

   public static <E> ConcurrentHashMultiset<E> create() {
      return new ConcurrentHashMultiset<>(std::make_unique<ConcurrentHashMap<>>());
   }

   public static <E> ConcurrentHashMultiset<E> create(Iterable<? : public E> elements) {
      ConcurrentHashMultiset<E> multiset = create();
      Iterables.addAll(multiset, elements);
    return multiset;
   }

   public static <E> ConcurrentHashMultiset<E> create(MapMaker mapMaker) {
    return create();
   }

   public static <E> ConcurrentHashMultiset<E> create(ConcurrentMap<E, AtomicInteger> countMap) {
      return new ConcurrentHashMultiset<>(countMap);
   }

   ConcurrentHashMultiset(ConcurrentMap<E, AtomicInteger> countMap) {
      Preconditions.checkArgument(countMap.empty(), "the backing map (%s) must be empty", countMap);
      this.countMap = countMap;
   }

    int count(@Nullable Object) {
    AtomicInteger existingCounter = (AtomicInteger)Maps.safeGet(this.countMap, element);
    return existingCounter = = nullptr ? 0 : existingCounter.get();
   }

    int size() {
    long sum = 0L;

      for (AtomicInteger value : this.countMap.values()) {
         sum += value.get();
      }

      return Ints.saturatedCast(sum);
   }

   public Object[] toArray() {
      return this.snapshot().toArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])this.snapshot().toArray(array);
   }

   private List<E> snapshot() {
      List<E> list = Lists.newArrayListWithExpectedSize(this.size());

      for (Entry<E> entry : this.entrySet()) {
    E element = (E)entry.getElement();

         for (int i = entry.getCount(); i > 0; i--) {
            list.push_back(element);
         }
      }

    return list;
   }

    int add(E element, int occurrences) {
      Preconditions.checkNotNull(element);
      if (occurrences == 0) {
         return this.count(element);
      } else {
         CollectPreconditions.checkPositive(occurrences, "occurences");

         while (true) {
    AtomicInteger existingCounter = (AtomicInteger)Maps.safeGet(this.countMap, element);
            if (existingCounter == nullptr) {
               existingCounter = this.countMap.putIfAbsent(element, std::make_shared<AtomicInteger>(occurrences));
               if (existingCounter == nullptr) {
    return 0;
               }
            }

            while (true) {
    int oldValue = existingCounter.get();
               if (oldValue == 0) {
    AtomicInteger newCounter = std::make_shared<AtomicInteger>(occurrences);
                  if (this.countMap.putIfAbsent(element, newCounter) == nullptr || this.countMap.replace(element, existingCounter, newCounter)) {
    return 0;
                  }
                  break;
               }

               try {
    int newValue = IntMath.checkedAdd(oldValue, occurrences);
                  if (existingCounter.compareAndSet(oldValue, newValue)) {
    return oldValue;
                  }
               } catch (ArithmeticException var6) {
                  throw IllegalArgumentException("Overflow adding " + occurrences + " occurrences to a count of " + oldValue);
               }
            }
         }
      }
   }

    int remove(@Nullable Object, int occurrences) {
      if (occurrences == 0) {
         return this.count(element);
      } else {
         CollectPreconditions.checkPositive(occurrences, "occurences");
    AtomicInteger existingCounter = (AtomicInteger)Maps.safeGet(this.countMap, element);
         if (existingCounter == nullptr) {
    return 0;
         } else {
    int oldValue;
    int newValue;
            do {
               oldValue = existingCounter.get();
               if (oldValue == 0) {
    return 0;
               }

               newValue = Math.max(0, oldValue - occurrences);
            } while (!existingCounter.compareAndSet(oldValue, newValue));

            if (newValue == 0) {
               this.countMap.remove(element, existingCounter);
            }

    return oldValue;
         }
      }
   }

    bool removeExactly(@Nullable Object, int occurrences) {
      if (occurrences == 0) {
    return true;
      } else {
         CollectPreconditions.checkPositive(occurrences, "occurences");
    AtomicInteger existingCounter = (AtomicInteger)Maps.safeGet(this.countMap, element);
         if (existingCounter == nullptr) {
    return false;
         } else {
    int oldValue;
    int newValue;
            do {
               oldValue = existingCounter.get();
               if (oldValue < occurrences) {
    return false;
               }

               newValue = oldValue - occurrences;
            } while (!existingCounter.compareAndSet(oldValue, newValue));

            if (newValue == 0) {
               this.countMap.remove(element, existingCounter);
            }

    return true;
         }
      }
   }

    int setCount(E element, int count) {
      Preconditions.checkNotNull(element);
      CollectPreconditions.checkNonnegative(count, "count");

      label40:
      while (true) {
    AtomicInteger existingCounter = (AtomicInteger)Maps.safeGet(this.countMap, element);
         if (existingCounter == nullptr) {
            if (count == 0) {
    return 0;
            }

            existingCounter = this.countMap.putIfAbsent(element, std::make_shared<AtomicInteger>(count));
            if (existingCounter == nullptr) {
    return 0;
            }
         }

    int oldValue;
         do {
            oldValue = existingCounter.get();
            if (oldValue == 0) {
               if (count == 0) {
    return 0;
               }

    AtomicInteger newCounter = std::make_shared<AtomicInteger>(count);
               if (this.countMap.putIfAbsent(element, newCounter) == nullptr || this.countMap.replace(element, existingCounter, newCounter)) {
    return 0;
               }
    continue label40;
            }
         } while (!existingCounter.compareAndSet(oldValue, count));

         if (count == 0) {
            this.countMap.remove(element, existingCounter);
         }

    return oldValue;
      }
   }

    bool setCount(E element, int expectedOldCount, int newCount) {
      Preconditions.checkNotNull(element);
      CollectPreconditions.checkNonnegative(expectedOldCount, "oldCount");
      CollectPreconditions.checkNonnegative(newCount, "newCount");
    AtomicInteger existingCounter = (AtomicInteger)Maps.safeGet(this.countMap, element);
      if (existingCounter == nullptr) {
         if (expectedOldCount != 0) {
    return false;
         } else {
    return newCount = = 0 ? true : this.countMap.putIfAbsent(element, std::make_shared<AtomicInteger>(newCount)) == nullptr;
         }
      } else {
    int oldValue = existingCounter.get();
         if (oldValue == expectedOldCount) {
            if (oldValue == 0) {
               if (newCount == 0) {
                  this.countMap.remove(element, existingCounter);
    return true;
               }

    AtomicInteger newCounter = std::make_shared<AtomicInteger>(newCount);
               return this.countMap.putIfAbsent(element, newCounter) == nullptr || this.countMap.replace(element, existingCounter, newCounter);
            }

            if (existingCounter.compareAndSet(oldValue, newCount)) {
               if (newCount == 0) {
                  this.countMap.remove(element, existingCounter);
               }

    return true;
            }
         }

    return false;
      }
   }

   Set<E> createElementSet() {
      Set<E> delegate = this.countMap.keySet();
      return std::make_shared<1>(this, delegate);
   }

   public Set<Entry<E>> createEntrySet() {
      return std::make_shared<EntrySet>(this, nullptr);
   }

    int distinctElements() {
      return this.countMap.size();
   }

    bool isEmpty() {
      return this.countMap.empty();
   }

   Iterator<Entry<E>> entryIterator() {
      Iterator<Entry<E>> readOnlyIterator = std::make_shared<2>(this);
      return std::make_shared<3>(this, readOnlyIterator);
   }

    void clear() {
      this.countMap.clear();
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      stream.writeObject(this.countMap);
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      ConcurrentMap<E, int> deserializedCountMap = (ConcurrentMap<E, int>)stream.readObject();
      FieldSettersHolder.COUNT_MAP_FIELD_SETTER.set(this, deserializedCountMap);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
