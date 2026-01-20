#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps/EntryTransformer.h"
#include "com/google/common/collect/Multimaps/TransformedEntriesMultimap/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   const Multimap<K, V1> fromMultimap;
   const EntryTransformer<? super K, ? super V1, V2> transformer;

   Multimaps$TransformedEntriesMultimap(Multimap<K, V1> fromMultimap, EntryTransformer<? super K, ? super V1, V2> transformer) {
      this.fromMultimap = (Multimap<K, V1>)Preconditions.checkNotNull(fromMultimap);
      this.transformer = (EntryTransformer<? super K, ? super V1, V2>)Preconditions.checkNotNull(transformer);
   }

   Collection<V2> transform(K key, Collection<V1> values) {
      Function<? super V1, V2> function = Maps.asValueToValueFunction(this.transformer, key);
      return (Collection<V2>)(dynamic_cast<List*>(values) != nullptr ? Lists.transform((List)values, function) : Collections2.transform(values, function));
   }

   Map<K, Collection<V2>> createAsMap() {
      return Maps.transformEntries(this.fromMultimap.asMap(), std::make_shared<1>(this));
   }

    void clear() {
      this.fromMultimap.clear();
   }

    bool containsKey(void* key) {
      return this.fromMultimap.containsKey(key);
   }

   Iterator<Entry<K, V2>> entryIterator() {
      return Iterators.transform(this.fromMultimap.entries().iterator(), Maps.asEntryToEntryFunction(this.transformer));
   }

   public Collection<V2> get(K key) {
      return this.transform(key, this.fromMultimap.get(key));
   }

    bool isEmpty() {
      return this.fromMultimap.empty();
   }

   public Set<K> keySet() {
      return this.fromMultimap.keySet();
   }

   public Multiset<K> keys() {
      return this.fromMultimap.keys();
   }

    bool put(K key, V2 value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool putAll(K key, Iterable<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool putAll(Multimap<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(void* key, void* value) {
      return this.get((K)key).remove(value);
   }

   public Collection<V2> removeAll(Object key) {
      return this.transform((K)key, this.fromMultimap.removeAll(key));
   }

   public Collection<V2> replaceValues(K key, Iterable<? : public V2> values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int size() {
      return this.fromMultimap.size();
   }

   Collection<V2> createValues() {
      return Collections2.transform(this.fromMultimap.entries(), Maps.asEntryToValueFunction(this.transformer));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
