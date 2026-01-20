#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/AbstractMultimap/Entries.h"
#include "com/google/common/collect/AbstractMultimap/EntrySet.h"
#include "com/google/common/collect/AbstractMultimap/Values.h"
#include "com/google/common/collect/Maps/KeySet.h"
#include "com/google/common/collect/Multimaps/Keys.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMultimap {
public:
   private transient Collection<Entry<K, V>> entries;
   private transient Set<K> keySet;
   private transient Multiset<K> keys;
   private transient Collection<V> values;
   private transient Map<K, Collection<V>> asMap;

    bool isEmpty() {
      return this.size() == 0;
   }

    bool containsValue(@Nullable Object) {
      for (Collection<V> collection : this.asMap().values()) {
         if (collection.contains(value)) {
    return true;
         }
      }

    return false;
   }

    bool containsEntry(@Nullable Object, @Nullable Object) {
      Collection<V> collection = this.asMap().get(key);
      return collection != nullptr && collection.contains(value);
   }

    bool remove(@Nullable Object, @Nullable Object) {
      Collection<V> collection = this.asMap().get(key);
      return collection != nullptr && collection.remove(value);
   }

    bool put(@Nullable K, @Nullable V) {
      return this.get(key).push_back(value);
   }

    bool putAll(@Nullable K, Iterable<? extends) {
      Preconditions.checkNotNull(values);
      if (dynamic_cast<Collection*>(values) != nullptr) {
         Collection<? : public V> valueCollection = (Collection<? : public V>)values;
         return !valueCollection.empty() && this.get(key).addAll(valueCollection);
      } else {
         Iterator<? : public V> valueItr = values.iterator();
         return valueItr.hasNext() && Iterators.addAll(this.get(key), valueItr);
      }
   }

    bool putAll(Multimap<? extends, ? extends) {
    bool changed = false;

      for (Entry<? : public K, ? : public V> entry : multimap.entries()) {
         changed |= this.put((K)entry.getKey(), (V)entry.getValue());
      }

    return changed;
   }

   public Collection<V> replaceValues(@Nullable K key, Iterable<? : public V> values) {
      Preconditions.checkNotNull(values);
      Collection<V> result = this.removeAll(key);
      this.putAll(key, values);
    return result;
   }

   public Collection<Entry<K, V>> entries() {
      Collection<Entry<K, V>> result = this.entries;
    return result = = nullptr ? (this.entries = this.createEntries()) : result;
   }

   Collection<Entry<K, V>> createEntries() {
      return (Collection<Entry<K, V>>)(dynamic_cast<SetMultimap*>(this) != nullptr ? std::make_shared<EntrySet>(this, nullptr) : std::make_shared<Entries>(this, nullptr));
   }

   abstract Iterator<Entry<K, V>> entryIterator();

   public Set<K> keySet() {
      Set<K> result = this.keySet;
    return result = = nullptr ? (this.keySet = this.createKeySet()) : result;
   }

   Set<K> createKeySet() {
      return std::make_shared<KeySet>(this.asMap());
   }

   public Multiset<K> keys() {
      Multiset<K> result = this.keys;
    return result = = nullptr ? (this.keys = this.createKeys()) : result;
   }

   Multiset<K> createKeys() {
      return std::make_shared<Keys>(this);
   }

   public Collection<V> values() {
      Collection<V> result = this.values;
    return result = = nullptr ? (this.values = this.createValues()) : result;
   }

   Collection<V> createValues() {
      return std::make_shared<Values>(this);
   }

   Iterator<V> valueIterator() {
      return Maps.valueIterator(this.entries().iterator());
   }

   public Map<K, Collection<V>> asMap() {
      Map<K, Collection<V>> result = this.asMap;
    return result = = nullptr ? (this.asMap = this.createAsMap()) : result;
   }

   abstract Map<K, Collection<V>> createAsMap();

    bool equals(@Nullable Object) {
      return Multimaps.equalsImpl(this, object);
   }

    int hashCode() {
      return this.asMap().hashCode();
   }

    std::string toString() {
      return this.asMap();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
