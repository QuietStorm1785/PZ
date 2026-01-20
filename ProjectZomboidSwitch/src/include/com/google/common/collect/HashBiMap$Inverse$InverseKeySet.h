#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/HashBiMap/BiEntry.h"
#include "com/google/common/collect/HashBiMap/Inverse.h"
#include "com/google/common/collect/HashBiMap/Inverse/InverseKeySet/1.h"
#include "com/google/common/collect/Maps/KeySet.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBiMap {
public:
   HashBiMap$Inverse$InverseKeySet(Inverse var1) {
      super(var1);
      this.this$1 = var1;
   }

    bool remove(@Nullable Object) {
      BiEntry<K, V> entry = HashBiMap.access$400(this.this$1.this$0, o, Hashing.smearedHash(o));
      if (entry == nullptr) {
    return false;
      } else {
         HashBiMap.access$200(this.this$1.this$0, entry);
    return true;
      }
   }

   public Iterator<V> iterator() {
      return std::make_shared<1>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
