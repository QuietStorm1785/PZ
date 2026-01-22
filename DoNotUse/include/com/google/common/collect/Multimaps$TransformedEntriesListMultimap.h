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
   Multimaps$TransformedEntriesListMultimap(ListMultimap<K, V1> fromMultimap, EntryTransformer<? super K, ? super V1, V2> transformer) {
      super(fromMultimap, transformer);
   }

   List<V2> transform(K key, Collection<V1> values) {
      return Lists.transform((List)values, Maps.asValueToValueFunction(this.transformer, key));
   }

   public List<V2> get(K key) {
      return this.transform(key, this.fromMultimap.get(key));
   }

   public List<V2> removeAll(Object key) {
      return this.transform((K)key, this.fromMultimap.removeAll(key));
   }

   public List<V2> replaceValues(K key, Iterable<? : public V2> values) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
