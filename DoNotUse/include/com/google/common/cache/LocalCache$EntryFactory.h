#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/Segment.h"
#include "com/google/common/cache/LocalCache/Strength.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


enum class LocalCache {
   STRONG,
   STRONG_ACCESS,
   STRONG_WRITE,
   STRONG_ACCESS_WRITE,
   WEAK,
   WEAK_ACCESS,
   WEAK_WRITE,
   WEAK_ACCESS_WRITE;

    static const int ACCESS_MASK = 1;
    static const int WRITE_MASK = 2;
    static const int WEAK_MASK = 4;
   static const LocalCache$EntryFactory[] factories = new LocalCache$EntryFactory[]{
      STRONG, STRONG_ACCESS, STRONG_WRITE, STRONG_ACCESS_WRITE, WEAK, WEAK_ACCESS, WEAK_WRITE, WEAK_ACCESS_WRITE
   };

   private LocalCache$EntryFactory() {
   }

   static LocalCache$EntryFactory getFactory(Strength keyStrength, boolean usesAccessQueue, boolean usesWriteQueue) {
    int flags = (keyStrength == Strength.WEAK ? 4 : 0) | (usesAccessQueue ? 1 : 0) | (usesWriteQueue ? 2 : 0);
      return factories[flags];
   }

   abstract <K, V> ReferenceEntry<K, V> newEntry(Segment<K, V> var1, K var2, int var3, @Nullable ReferenceEntry<K, V> var4);

   <K, V> ReferenceEntry<K, V> copyEntry(Segment<K, V> segment, ReferenceEntry<K, V> original, ReferenceEntry<K, V> newNext) {
      return this.newEntry(segment, (K)original.getKey(), original.getHash(), newNext);
   }

   <K, V> void copyAccessEntry(ReferenceEntry<K, V> original, ReferenceEntry<K, V> newEntry) {
      newEntry.setAccessTime(original.getAccessTime());
      LocalCache.connectAccessOrder(original.getPreviousInAccessQueue(), newEntry);
      LocalCache.connectAccessOrder(newEntry, original.getNextInAccessQueue());
      LocalCache.nullifyAccessOrder(original);
   }

   <K, V> void copyWriteEntry(ReferenceEntry<K, V> original, ReferenceEntry<K, V> newEntry) {
      newEntry.setWriteTime(original.getWriteTime());
      LocalCache.connectWriteOrder(original.getPreviousInWriteQueue(), newEntry);
      LocalCache.connectWriteOrder(newEntry, original.getNextInWriteQueue());
      LocalCache.nullifyWriteOrder(original);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
