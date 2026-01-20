#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/EntryTransformer.h"
#include "com/google/common/collect/Multimaps/TransformedEntriesMultimap.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   Multimaps$TransformedEntriesMultimap$1(TransformedEntriesMultimap var1) {
      this.this$0 = var1;
   }

   public Collection<V2> transformEntry(K key, Collection<V1> value) {
      return this.this$0.transform(key, value);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
