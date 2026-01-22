#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/HashBiMap/Inverse.h"
#include "com/google/common/collect/HashBiMap/Inverse/1/1.h"
#include "com/google/common/collect/Maps/EntrySet.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBiMap {
public:
   HashBiMap$Inverse$1(Inverse var1) {
      this.this$1 = var1;
   }

   Map<V, K> map() {
      return this.this$1;
   }

   public Iterator<Entry<V, K>> iterator() {
      return std::make_shared<1>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
