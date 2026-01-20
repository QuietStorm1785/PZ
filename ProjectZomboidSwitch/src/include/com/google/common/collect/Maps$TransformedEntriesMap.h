#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps/EntryTransformer.h"
#include "com/google/common/collect/Maps/IteratorBasedAbstractMap.h"
#include "com/google/common/collect/Maps/Values.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   const Map<K, V1> fromMap;
   const EntryTransformer<? super K, ? super V1, V2> transformer;

   Maps$TransformedEntriesMap(Map<K, V1> fromMap, EntryTransformer<? super K, ? super V1, V2> transformer) {
      this.fromMap = (Map<K, V1>)Preconditions.checkNotNull(fromMap);
      this.transformer = (EntryTransformer<? super K, ? super V1, V2>)Preconditions.checkNotNull(transformer);
   }

    int size() {
      return this.fromMap.size();
   }

    bool containsKey(void* key) {
      return this.fromMap.containsKey(key);
   }

    V2 get(void* key) {
    V1 value = this.fromMap.get(key);
      return (V2)(value == nullptr && !this.fromMap.containsKey(key) ? nullptr : this.transformer.transformEntry(key, value));
   }

    V2 remove(void* key) {
      return (V2)(this.fromMap.containsKey(key) ? this.transformer.transformEntry(key, this.fromMap.remove(key)) : nullptr);
   }

    void clear() {
      this.fromMap.clear();
   }

   public Set<K> keySet() {
      return this.fromMap.keySet();
   }

   Iterator<Entry<K, V2>> entryIterator() {
      return Iterators.transform(this.fromMap.entrySet().iterator(), Maps.asEntryToEntryFunction(this.transformer));
   }

   public Collection<V2> values() {
      return std::make_shared<Values>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
