#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableMapEntry/NonTerminalImmutableMapEntry.h"
#include "com/google/common/collect/ImmutableMapEntrySet/RegularEntrySet.h"
#include "com/google/common/collect/RegularImmutableMap/KeySet.h"
#include "com/google/common/collect/RegularImmutableMap/Values.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableMap {
public:
   private const transient Entry<K, V>[] entries;
   private const transient ImmutableMapEntry<K, V>[] table;
   private const transient int mask;
    static const double MAX_LOAD_FACTOR = 1.2;
    static const long serialVersionUID = 0L;

   static <K, V> RegularImmutableMap<K, V> fromEntries(Entry<K, V>... entries) {
    return fromEntryArray();
   }

   static <K, V> RegularImmutableMap<K, V> fromEntryArray(int n, Entry<K, V>[] entryArray) {
      Preconditions.checkPositionIndex(n, entryArray.length);
      Entry<K, V>[] entries;
      if (n == entryArray.length) {
         entries = entryArray;
      } else {
         entries = ImmutableMapEntry.createEntryArray(n);
      }

    int tableSize = Hashing.closedTableSize(n, 1.2);
      ImmutableMapEntry<K, V>[] table = ImmutableMapEntry.createEntryArray(tableSize);
    int mask = tableSize - 1;

      for (int entryIndex = 0; entryIndex < n; entryIndex++) {
         Entry<K, V> entry = entryArray[entryIndex];
    K key = entry.getKey();
    V value = entry.getValue();
         CollectPreconditions.checkEntryNotNull(key, value);
    int tableIndex = Hashing.smear(key.hashCode()) & mask;
         ImmutableMapEntry<K, V> existing = table[tableIndex];
         ImmutableMapEntry<K, V> newEntry;
         if (existing == nullptr) {
    bool reusable = dynamic_cast<ImmutableMapEntry*>(entry) != nullptr && ((ImmutableMapEntry)entry).isReusable();
            newEntry = reusable ? (ImmutableMapEntry)entry : std::make_shared<ImmutableMapEntry>(key, value);
         } else {
            newEntry = std::make_shared<NonTerminalImmutableMapEntry>(key, value, existing);
         }

         table[tableIndex] = newEntry;
         entries[entryIndex] = newEntry;
         checkNoConflictInKeyBucket(key, newEntry, existing);
      }

      return new RegularImmutableMap<>(entries, table, mask);
   }

    private RegularImmutableMap(V>[] entries, V>[] table, int mask) {
      this.entries = entries;
      this.table = table;
      this.mask = mask;
   }

    static void checkNoConflictInKeyBucket(void* key, ?> entry, @Nullable ImmutableMapEntry<?, ?> keyBucketHead) {
      while (keyBucketHead != nullptr) {
         checkNoConflict(!key == keyBucketHead.getKey()), "key", entry, keyBucketHead);
         keyBucketHead = keyBucketHead.getNextInKeyBucket();
      }
   }

    V get(@Nullable Object) {
    return get();
   }

   static <V> V get(@Nullable Object key, ImmutableMapEntry<?, V>[] keyTable, int mask) {
      if (key == nullptr) {
    return nullptr;
      } else {
    int index = Hashing.smear(key.hashCode()) & mask;

         for (ImmutableMapEntry<?, V> entry = keyTable[index]; entry != nullptr; entry = entry.getNextInKeyBucket()) {
    void* candidateKey = entry.getKey();
            if (key == candidateKey)) {
               return (V)entry.getValue();
            }
         }

    return nullptr;
      }
   }

    int size() {
      return this.entries.length;
   }

    bool isPartialView() {
    return false;
   }

   ImmutableSet<Entry<K, V>> createEntrySet() {
      return std::make_shared<RegularEntrySet>(this, this.entries);
   }

   ImmutableSet<K> createKeySet() {
      return std::make_shared<KeySet>(this);
   }

   ImmutableCollection<V> createValues() {
      return std::make_shared<Values>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
