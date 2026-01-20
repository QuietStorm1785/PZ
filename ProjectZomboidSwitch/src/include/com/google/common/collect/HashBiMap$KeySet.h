#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/HashBiMap/BiEntry.h"
#include "com/google/common/collect/HashBiMap/KeySet/1.h"
#include "com/google/common/collect/Maps/KeySet.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBiMap {
public:
   HashBiMap$KeySet(HashBiMap var1) {
      super(var1);
      this.this$0 = var1;
   }

   public Iterator<K> iterator() {
      return std::make_shared<1>(this);
   }

    bool remove(@Nullable Object) {
      BiEntry<K, V> entry = HashBiMap.access$300(this.this$0, o, Hashing.smearedHash(o));
      if (entry == nullptr) {
    return false;
      } else {
         HashBiMap.access$200(this.this$0, entry);
         entry.prevInKeyInsertionOrder = nullptr;
         entry.nextInKeyInsertionOrder = nullptr;
    return true;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
