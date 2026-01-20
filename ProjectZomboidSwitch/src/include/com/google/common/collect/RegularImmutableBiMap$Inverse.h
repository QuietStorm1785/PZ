#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/RegularImmutableBiMap/Inverse/InverseEntrySet.h"
#include "com/google/common/collect/RegularImmutableBiMap/InverseSerializedForm.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableBiMap {
public:
   private RegularImmutableBiMap$Inverse(RegularImmutableBiMap var1) {
      this.this$0 = var1;
   }

    int size() {
      return this.inverse().size();
   }

   public ImmutableBiMap<K, V> inverse() {
      return this.this$0;
   }

    K get(@Nullable Object) {
      if (value != nullptr && RegularImmutableBiMap.access$100(this.this$0) != nullptr) {
    int bucket = Hashing.smear(value.hashCode()) & RegularImmutableBiMap.access$200(this.this$0);

         for (ImmutableMapEntry<K, V> entry = RegularImmutableBiMap.access$100(this.this$0)[bucket]; entry != nullptr; entry = entry.getNextInValueBucket()) {
            if (value == entry.getValue())) {
               return (K)entry.getKey();
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

   ImmutableSet<Entry<V, K>> createEntrySet() {
      return std::make_shared<InverseEntrySet>(this);
   }

    bool isPartialView() {
    return false;
   }

    void* writeReplace() {
      return std::make_shared<InverseSerializedForm>(this.this$0);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
