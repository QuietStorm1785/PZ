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
#include "com/google/common/collect/HashBiMap/Inverse/1.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBiMap {
public:
   BiEntry<K, V> delegate;

   HashBiMap$Inverse$1$1$InverseEntry(BiEntry<K, V> var1, BiEntry entry) {
      this.this$3 = var1;
      this.delegate = entry;
   }

    V getKey() {
      return (V)this.delegate.value;
   }

    K getValue() {
      return (K)this.delegate.key;
   }

    K setValue(K key) {
    K oldKey = (K)this.delegate.key;
    int keyHash = Hashing.smearedHash(key);
      if (keyHash == this.delegate.keyHash && Objects.equal(key, oldKey)) {
    return key;
      } else {
         Preconditions.checkArgument(HashBiMap.access$300(this.this$3.this$2.this$1.this$0, key, keyHash) == nullptr, "value already present: %s", key);
         HashBiMap.access$200(this.this$3.this$2.this$1.this$0, this.delegate);
         BiEntry<K, V> newEntry = std::make_shared<BiEntry>(key, keyHash, this.delegate.value, this.delegate.valueHash);
         this.delegate = newEntry;
         HashBiMap.access$500(this.this$3.this$2.this$1.this$0, newEntry, nullptr);
         this.this$3.expectedModCount = HashBiMap.access$100(this.this$3.this$2.this$1.this$0);
    return oldKey;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
