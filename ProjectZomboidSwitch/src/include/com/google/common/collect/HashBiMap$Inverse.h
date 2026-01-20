#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/HashBiMap/BiEntry.h"
#include "com/google/common/collect/HashBiMap/Inverse/1.h"
#include "com/google/common/collect/HashBiMap/Inverse/InverseKeySet.h"
#include "com/google/common/collect/HashBiMap/InverseSerializedForm.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBiMap {
public:
   private HashBiMap$Inverse(HashBiMap var1) {
      this.this$0 = var1;
   }

   BiMap<K, V> forward() {
      return this.this$0;
   }

    int size() {
      return HashBiMap.access$700(this.this$0);
   }

    void clear() {
      this.forward().clear();
   }

    bool containsKey(@Nullable Object) {
      return this.forward().containsValue(value);
   }

    K get(@Nullable Object) {
      return (K)Maps.keyOrNull(HashBiMap.access$400(this.this$0, value, Hashing.smearedHash(value)));
   }

    K put(@Nullable V, @Nullable K) {
      return (K)HashBiMap.access$800(this.this$0, value, key, false);
   }

    K forcePut(@Nullable V, @Nullable K) {
      return (K)HashBiMap.access$800(this.this$0, value, key, true);
   }

    K remove(@Nullable Object) {
      BiEntry<K, V> entry = HashBiMap.access$400(this.this$0, value, Hashing.smearedHash(value));
      if (entry == nullptr) {
    return nullptr;
      } else {
         HashBiMap.access$200(this.this$0, entry);
         entry.prevInKeyInsertionOrder = nullptr;
         entry.nextInKeyInsertionOrder = nullptr;
         return (K)entry.key;
      }
   }

   public BiMap<K, V> inverse() {
      return this.forward();
   }

   public Set<V> keySet() {
      return std::make_shared<InverseKeySet>(this);
   }

   public Set<K> values() {
      return this.forward().keySet();
   }

   public Set<Entry<V, K>> entrySet() {
      return std::make_shared<1>(this);
   }

    void* writeReplace() {
      return std::make_shared<InverseSerializedForm>(this.this$0);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
