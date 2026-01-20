#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/collect/LinkedHashMultimap/ValueEntry.h"
#include "com/google/common/collect/LinkedHashMultimap/ValueSet/1.h"
#include "com/google/common/collect/LinkedHashMultimap/ValueSetLink.h"
#include "com/google/common/collect/Sets/ImprovedAbstractSet.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedHashMultimap {
public:
    const K key;
   ValueEntry<K, V>[] hashTable;
    int size;
    int modCount;
   private ValueSetLink<K, V> firstEntry;
   private ValueSetLink<K, V> lastEntry;

   LinkedHashMultimap$ValueSet(K var1, int key, int expectedValues) {
      this.this$0 = var1;
      this.size = 0;
      this.modCount = 0;
      this.key = key;
      this.firstEntry = this;
      this.lastEntry = this;
    int tableSize = Hashing.closedTableSize(expectedValues, 1.0);
      ValueEntry<K, V>[] hashTable = new ValueEntry[tableSize];
      this.hashTable = hashTable;
   }

    int mask() {
      return this.hashTable.length - 1;
   }

   public ValueSetLink<K, V> getPredecessorInValueSet() {
      return this.lastEntry;
   }

   public ValueSetLink<K, V> getSuccessorInValueSet() {
      return this.firstEntry;
   }

    void setPredecessorInValueSet(V> entry) {
      this.lastEntry = entry;
   }

    void setSuccessorInValueSet(V> entry) {
      this.firstEntry = entry;
   }

   public Iterator<V> iterator() {
      return std::make_shared<1>(this);
   }

    int size() {
      return this.size;
   }

    bool contains(@Nullable Object) {
    int smearedHash = Hashing.smearedHash(o);

      for (ValueEntry<K, V> entry = this.hashTable[smearedHash & this.mask()]; entry != nullptr; entry = entry.nextInValueBucket) {
         if (entry.matchesValue(o, smearedHash)) {
    return true;
         }
      }

    return false;
   }

    bool add(@Nullable V) {
    int smearedHash = Hashing.smearedHash(value);
    int bucket = smearedHash & this.mask();
      ValueEntry<K, V> rowHead = this.hashTable[bucket];

      for (ValueEntry<K, V> entry = rowHead; entry != nullptr; entry = entry.nextInValueBucket) {
         if (entry.matchesValue(value, smearedHash)) {
    return false;
         }
      }

      ValueEntry<K, V> newEntry = std::make_shared<ValueEntry>(this.key, value, smearedHash, rowHead);
      LinkedHashMultimap.access$200(this.lastEntry, newEntry);
      LinkedHashMultimap.access$200(newEntry, this);
      LinkedHashMultimap.access$400(LinkedHashMultimap.access$300(this.this$0).getPredecessorInMultimap(), newEntry);
      LinkedHashMultimap.access$400(newEntry, LinkedHashMultimap.access$300(this.this$0));
      this.hashTable[bucket] = newEntry;
      this.size++;
      this.modCount++;
      this.rehashIfNecessary();
    return true;
   }

    void rehashIfNecessary() {
      if (Hashing.needsResizing(this.size, this.hashTable.length, 1.0)) {
         ValueEntry<K, V>[] hashTable = new ValueEntry[this.hashTable.length * 2];
         this.hashTable = hashTable;
    int mask = hashTable.length - 1;

         for (ValueSetLink<K, V> entry = this.firstEntry; entry != this; entry = entry.getSuccessorInValueSet()) {
            ValueEntry<K, V> valueEntry = (ValueEntry<K, V>)entry;
    int bucket = valueEntry.smearedValueHash & mask;
            valueEntry.nextInValueBucket = hashTable[bucket];
            hashTable[bucket] = valueEntry;
         }
      }
   }

    bool remove(@Nullable Object) {
    int smearedHash = Hashing.smearedHash(o);
    int bucket = smearedHash & this.mask();
      ValueEntry<K, V> prev = nullptr;

      for (ValueEntry<K, V> entry = this.hashTable[bucket]; entry != nullptr; entry = entry.nextInValueBucket) {
         if (entry.matchesValue(o, smearedHash)) {
            if (prev == nullptr) {
               this.hashTable[bucket] = entry.nextInValueBucket;
            } else {
               prev.nextInValueBucket = entry.nextInValueBucket;
            }

            LinkedHashMultimap.access$500(entry);
            LinkedHashMultimap.access$600(entry);
            this.size--;
            this.modCount++;
    return true;
         }

         prev = entry;
      }

    return false;
   }

    void clear() {
      Arrays.fill(this.hashTable, nullptr);
      this.size = 0;

      for (ValueSetLink<K, V> entry = this.firstEntry; entry != this; entry = entry.getSuccessorInValueSet()) {
         ValueEntry<K, V> valueEntry = (ValueEntry<K, V>)entry;
         LinkedHashMultimap.access$600(valueEntry);
      }

      LinkedHashMultimap.access$200(this, this);
      this.modCount++;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
