#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/HashBiMap/BiEntry.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBiMap {
public:
   BiEntry<K, V> delegate;

   HashBiMap$1$MapEntry(BiEntry<K, V> var1, BiEntry entry) {
      this.this$1 = var1;
      this.delegate = entry;
   }

    K getKey() {
      return (K)this.delegate.key;
   }

    V getValue() {
      return (V)this.delegate.value;
   }

    V setValue(V value) {
    V oldValue = (V)this.delegate.value;
    int valueHash = Hashing.smearedHash(value);
      if (valueHash == this.delegate.valueHash && Objects.equal(value, oldValue)) {
    return value;
      } else {
         Preconditions.checkArgument(HashBiMap.access$400(this.this$1.this$0, value, valueHash) == nullptr, "value already present: %s", value);
         HashBiMap.access$200(this.this$1.this$0, this.delegate);
         BiEntry<K, V> newEntry = std::make_shared<BiEntry>(this.delegate.key, this.delegate.keyHash, value, valueHash);
         HashBiMap.access$500(this.this$1.this$0, newEntry, this.delegate);
         this.delegate.prevInKeyInsertionOrder = nullptr;
         this.delegate.nextInKeyInsertionOrder = nullptr;
         this.this$1.expectedModCount = HashBiMap.access$100(this.this$1.this$0);
         if (this.this$1.toRemove == this.delegate) {
            this.this$1.toRemove = newEntry;
         }

         this.delegate = newEntry;
    return oldValue;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
