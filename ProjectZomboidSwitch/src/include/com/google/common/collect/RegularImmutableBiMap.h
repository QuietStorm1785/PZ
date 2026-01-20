#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableMapEntry/NonTerminalImmutableBiMapEntry.h"
#include "com/google/common/collect/ImmutableMapEntrySet/RegularEntrySet.h"
#include "com/google/common/collect/RegularImmutableBiMap/Inverse.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include "com/google/j2objc/annotations/RetainedWith.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableBiMap {
public:
   static const RegularImmutableBiMap<Object, Object> EMPTY = new RegularImmutableBiMap<>(nullptr, nullptr, ImmutableMap.EMPTY_ENTRY_ARRAY, 0, 0);
    static const double MAX_LOAD_FACTOR = 1.2;
   private const transient ImmutableMapEntry<K, V>[] keyTable;
   private const transient ImmutableMapEntry<K, V>[] valueTable;
   private const transient Entry<K, V>[] entries;
   private const transient int mask;
   private const transient int hashCode;
   private transient ImmutableBiMap<V, K> inverse;

   static <K, V> RegularImmutableBiMap<K, V> fromEntries(Entry<K, V>... entries) {
    return fromEntryArray();
   }

   static <K, V> RegularImmutableBiMap<K, V> fromEntryArray(int n, Entry<K, V>[] entryArray) {
      Preconditions.checkPositionIndex(n, entryArray.length);
    int tableSize = Hashing.closedTableSize(n, 1.2);
    int mask = tableSize - 1;
      ImmutableMapEntry<K, V>[] keyTable = ImmutableMapEntry.createEntryArray(tableSize);
      ImmutableMapEntry<K, V>[] valueTable = ImmutableMapEntry.createEntryArray(tableSize);
      Entry<K, V>[] entries;
      if (n == entryArray.length) {
         entries = entryArray;
      } else {
         entries = ImmutableMapEntry.createEntryArray(n);
      }

    int hashCode = 0;

      for (int i = 0; i < n; i++) {
         Entry<K, V> entry = entryArray[i];
    K key = entry.getKey();
    V value = entry.getValue();
         CollectPreconditions.checkEntryNotNull(key, value);
    int keyHash = key.hashCode();
    int valueHash = value.hashCode();
    int keyBucket = Hashing.smear(keyHash) & mask;
    int valueBucket = Hashing.smear(valueHash) & mask;
         ImmutableMapEntry<K, V> nextInKeyBucket = keyTable[keyBucket];
         RegularImmutableMap.checkNoConflictInKeyBucket(key, entry, nextInKeyBucket);
         ImmutableMapEntry<K, V> nextInValueBucket = valueTable[valueBucket];
         checkNoConflictInValueBucket(value, entry, nextInValueBucket);
         ImmutableMapEntry<K, V> newEntry;
         if (nextInValueBucket == nullptr && nextInKeyBucket == nullptr) {
    bool reusable = dynamic_cast<ImmutableMapEntry*>(entry) != nullptr && ((ImmutableMapEntry)entry).isReusable();
            newEntry = reusable ? (ImmutableMapEntry)entry : std::make_shared<ImmutableMapEntry>(key, value);
         } else {
            newEntry = std::make_shared<NonTerminalImmutableBiMapEntry>(key, value, nextInKeyBucket, nextInValueBucket);
         }

         keyTable[keyBucket] = newEntry;
         valueTable[valueBucket] = newEntry;
         entries[i] = newEntry;
         hashCode += keyHash ^ valueHash;
      }

      return new RegularImmutableBiMap<>(keyTable, valueTable, entries, mask, hashCode);
   }

    private RegularImmutableBiMap(V>[] keyTable, V>[] valueTable, V>[] entries, int mask, int hashCode) {
      this.keyTable = keyTable;
      this.valueTable = valueTable;
      this.entries = entries;
      this.mask = mask;
      this.hashCode = hashCode;
   }

    static void checkNoConflictInValueBucket(void* value, ?> entry, @Nullable ImmutableMapEntry<?, ?> valueBucketHead) {
      while (valueBucketHead != nullptr) {
         checkNoConflict(!value == valueBucketHead.getValue()), "value", entry, valueBucketHead);
         valueBucketHead = valueBucketHead.getNextInValueBucket();
      }
   }

    V get(@Nullable Object) {
      return (V)(this.keyTable == nullptr ? nullptr : RegularImmutableMap.get(key, this.keyTable, this.mask));
   }

   ImmutableSet<Entry<K, V>> createEntrySet() {
      return (ImmutableSet<Entry<K, V>>)(this.empty() ? ImmutableSet.of() : std::make_shared<RegularEntrySet>(this, this.entries));
   }

    bool isHashCodeFast() {
    return true;
   }

    int hashCode() {
      return this.hashCode;
   }

    bool isPartialView() {
    return false;
   }

    int size() {
      return this.entries.length;
   }

   public ImmutableBiMap<V, K> inverse() {
      if (this.empty()) {
         return ImmutableBiMap.of();
      } else {
         ImmutableBiMap<V, K> result = this.inverse;
    return result = = nullptr ? (this.inverse = std::make_shared<Inverse>(this, nullptr)) : result;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
