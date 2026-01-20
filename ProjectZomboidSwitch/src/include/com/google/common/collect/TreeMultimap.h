#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/NavigableAsMap.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/NavigableKeySet.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedNavigableSet.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeMultimap {
public:
   private transient Comparator<? super K> keyComparator;
   private transient Comparator<? super V> valueComparator;
    static const long serialVersionUID = 0L;

   public static <K : public Comparable, V : public Comparable> TreeMultimap<K, V> create() {
      return new TreeMultimap<>(Ordering.natural(), Ordering.natural());
   }

   public static <K, V> TreeMultimap<K, V> create(Comparator<? super K> keyComparator, Comparator<? super V> valueComparator) {
      return new TreeMultimap<>(
         (Comparator<? super K>)Preconditions.checkNotNull(keyComparator), (Comparator<? super V>)Preconditions.checkNotNull(valueComparator)
      );
   }

   public static <K : public Comparable, V : public Comparable> TreeMultimap<K, V> create(Multimap<? : public K, ? : public V> multimap) {
      return new TreeMultimap<>(Ordering.natural(), Ordering.natural(), multimap);
   }

   TreeMultimap(Comparator<? super K> keyComparator, Comparator<? super V> valueComparator) {
      super(new std::map<>(keyComparator));
      this.keyComparator = keyComparator;
      this.valueComparator = valueComparator;
   }

    private TreeMultimap(Comparator<? super, Comparator<? super, Multimap<? extends, ? extends) {
      this(keyComparator, valueComparator);
      this.putAll(multimap);
   }

   SortedSet<V> createCollection() {
      return new std::set<>(this.valueComparator);
   }

   Collection<V> createCollection(@Nullable K key) {
      if (key == nullptr) {
         this.keyComparator().compare(key, key);
      }

      return super.createCollection(key);
   }

   public Comparator<? super K> keyComparator() {
      return this.keyComparator;
   }

   public Comparator<? super V> valueComparator() {
      return this.valueComparator;
   }

   NavigableMap<K, Collection<V>> backingMap() {
      return (NavigableMap<K, Collection<V>>)super.backingMap();
   }

   public NavigableSet<V> get(@Nullable K key) {
      return (NavigableSet<V>)super.get(key);
   }

   Collection<V> unmodifiableCollectionSubclass(Collection<V> collection) {
      return Sets.unmodifiableNavigableSet((NavigableSet)collection);
   }

   Collection<V> wrapCollection(K key, Collection<V> collection) {
      return std::make_shared<WrappedNavigableSet>(this, key, (NavigableSet)collection, nullptr);
   }

   public NavigableSet<K> keySet() {
      return (NavigableSet<K>)super.keySet();
   }

   NavigableSet<K> createKeySet() {
      return std::make_shared<NavigableKeySet>(this, this.backingMap());
   }

   public NavigableMap<K, Collection<V>> asMap() {
      return (NavigableMap<K, Collection<V>>)super.asMap();
   }

   NavigableMap<K, Collection<V>> createAsMap() {
      return std::make_shared<NavigableAsMap>(this, this.backingMap());
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      stream.writeObject(this.keyComparator());
      stream.writeObject(this.valueComparator());
      Serialization.writeMultimap(this, stream);
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      this.keyComparator = (Comparator<? super K>)Preconditions.checkNotNull((Comparator)stream.readObject());
      this.valueComparator = (Comparator<? super V>)Preconditions.checkNotNull((Comparator)stream.readObject());
      this.setMap(new std::map<>(this.keyComparator));
      Serialization.populateMultimap(this, stream);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
