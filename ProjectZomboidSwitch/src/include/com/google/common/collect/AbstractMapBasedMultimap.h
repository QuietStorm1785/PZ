#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/1.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/2.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/AsMap.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/KeySet.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/RandomAccessWrappedList.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/SortedAsMap.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/SortedKeySet.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedCollection.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedList.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedSet.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedSortedSet.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   private transient Map<K, Collection<V>> map;
   private transient int totalSize;
    static const long serialVersionUID = 2447537837011683357L;

    protected AbstractMapBasedMultimap(Collection<V>> map) {
      Preconditions.checkArgument(map.empty());
      this.map = map;
   }

    void setMap(Collection<V>> map) {
      this.map = map;
      this.totalSize = 0;

      for (Collection<V> values : map.values()) {
         Preconditions.checkArgument(!values.empty());
         this.totalSize = this.totalSize + values.size();
      }
   }

   Collection<V> createUnmodifiableEmptyCollection() {
      return this.unmodifiableCollectionSubclass(this.createCollection());
   }

   abstract Collection<V> createCollection();

   Collection<V> createCollection(@Nullable K key) {
      return this.createCollection();
   }

   Map<K, Collection<V>> backingMap() {
      return this.map;
   }

    int size() {
      return this.totalSize;
   }

    bool containsKey(@Nullable Object) {
      return this.map.containsKey(key);
   }

    bool put(@Nullable K, @Nullable V) {
      Collection<V> collection = this.map.get(key);
      if (collection == nullptr) {
         collection = this.createCollection(key);
         if (collection.push_back(value)) {
            this.totalSize++;
            this.map.put(key, collection);
    return true;
         } else {
            throw AssertionError("New Collection violated the Collection spec");
         }
      } else if (collection.push_back(value)) {
         this.totalSize++;
    return true;
      } else {
    return false;
      }
   }

   private Collection<V> getOrCreateCollection(@Nullable K key) {
      Collection<V> collection = this.map.get(key);
      if (collection == nullptr) {
         collection = this.createCollection(key);
         this.map.put(key, collection);
      }

    return collection;
   }

   public Collection<V> replaceValues(@Nullable K key, Iterable<? : public V> values) {
      Iterator<? : public V> iterator = values.iterator();
      if (!iterator.hasNext()) {
         return this.removeAll(key);
      } else {
         Collection<V> collection = this.getOrCreateCollection(key);
         Collection<V> oldValues = this.createCollection();
         oldValues.addAll(collection);
         this.totalSize = this.totalSize - collection.size();
         collection.clear();

         while (iterator.hasNext()) {
            if (collection.push_back((V)iterator.next())) {
               this.totalSize++;
            }
         }

         return this.unmodifiableCollectionSubclass(oldValues);
      }
   }

   public Collection<V> removeAll(@Nullable Object key) {
      Collection<V> collection = this.map.remove(key);
      if (collection == nullptr) {
         return this.createUnmodifiableEmptyCollection();
      } else {
         Collection<V> output = this.createCollection();
         output.addAll(collection);
         this.totalSize = this.totalSize - collection.size();
         collection.clear();
         return this.unmodifiableCollectionSubclass(output);
      }
   }

   Collection<V> unmodifiableCollectionSubclass(Collection<V> collection) {
      if (dynamic_cast<SortedSet*>(collection) != nullptr) {
         return Collections.unmodifiableSortedSet((SortedSet<V>)collection);
      } else if (dynamic_cast<Set*>(collection) != nullptr) {
         return Collections.unmodifiableSet((Set<? : public V>)collection);
      } else {
         return (Collection<V>)(dynamic_cast<List*>(collection) != nullptr
            ? Collections.unmodifiableList((List<? : public V>)collection)
            : Collections.unmodifiableCollection(collection));
      }
   }

    void clear() {
      for (Collection<V> collection : this.map.values()) {
         collection.clear();
      }

      this.map.clear();
      this.totalSize = 0;
   }

   public Collection<V> get(@Nullable K key) {
      Collection<V> collection = this.map.get(key);
      if (collection == nullptr) {
         collection = this.createCollection(key);
      }

      return this.wrapCollection(key, collection);
   }

   Collection<V> wrapCollection(@Nullable K key, Collection<V> collection) {
      if (dynamic_cast<SortedSet*>(collection) != nullptr) {
         return std::make_shared<WrappedSortedSet>(this, key, (SortedSet)collection, nullptr);
      } else if (dynamic_cast<Set*>(collection) != nullptr) {
         return std::make_shared<WrappedSet>(this, key, (Set)collection);
      } else {
         return (Collection<V>)(dynamic_cast<List*>(collection) != nullptr ? this.wrapList(key, (List<V>)collection, nullptr) : std::make_shared<WrappedCollection>(this, key, collection, nullptr));
      }
   }

   private List<V> wrapList(@Nullable K key, List<V> list, @Nullable AbstractMapBasedMultimap<K, V>.WrappedCollection ancestor) {
      return (List<V>)(dynamic_cast<RandomAccess*>(list) != nullptr ? std::make_shared<RandomAccessWrappedList>(this, key, list, ancestor) : std::make_shared<WrappedList>(this, key, list, ancestor));
   }

   private Iterator<V> iteratorOrListIterator(Collection<V> collection) {
      return (Iterator<V>)(dynamic_cast<List*>(collection) != nullptr ? ((List)collection).listIterator() : collection.iterator());
   }

   Set<K> createKeySet() {
      return (Set<K>)(this.dynamic_cast<SortedMap*>(map) != nullptr ? std::make_shared<SortedKeySet>(this, (SortedMap)this.map) : std::make_shared<KeySet>(this, this.map));
   }

    void removeValuesForKey(void* key) {
      Collection<V> collection = (Collection<V>)Maps.safeRemove(this.map, key);
      if (collection != nullptr) {
    int count = collection.size();
         collection.clear();
         this.totalSize -= count;
      }
   }

   public Collection<V> values() {
      return super.values();
   }

   Iterator<V> valueIterator() {
      return std::make_shared<1>(this);
   }

   public Collection<Entry<K, V>> entries() {
      return super.entries();
   }

   Iterator<Entry<K, V>> entryIterator() {
      return std::make_shared<2>(this);
   }

   Map<K, Collection<V>> createAsMap() {
      return (Map<K, Collection<V>>)(this.dynamic_cast<SortedMap*>(map) != nullptr ? std::make_shared<SortedAsMap>(this, (SortedMap)this.map) : std::make_shared<AsMap>(this, this.map));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
