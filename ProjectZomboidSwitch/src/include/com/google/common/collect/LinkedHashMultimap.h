#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/collect/LinkedHashMultimap/1.h"
#include "com/google/common/collect/LinkedHashMultimap/ValueEntry.h"
#include "com/google/common/collect/LinkedHashMultimap/ValueSet.h"
#include "com/google/common/collect/LinkedHashMultimap/ValueSetLink.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedHashMultimap {
public:
    static const int DEFAULT_KEY_CAPACITY = 16;
    static const int DEFAULT_VALUE_SET_CAPACITY = 2;
    static const double VALUE_SET_LOAD_FACTOR = 1.0;
   transient int valueSetCapacity = 2;
   private transient ValueEntry<K, V> multimapHeaderEntry;
    static const long serialVersionUID = 1L;

   public static <K, V> LinkedHashMultimap<K, V> create() {
      return new LinkedHashMultimap<>(16, 2);
   }

   public static <K, V> LinkedHashMultimap<K, V> create(int expectedKeys, int expectedValuesPerKey) {
      return new LinkedHashMultimap<>(Maps.capacity(expectedKeys), Maps.capacity(expectedValuesPerKey));
   }

   public static <K, V> LinkedHashMultimap<K, V> create(Multimap<? : public K, ? : public V> multimap) {
      LinkedHashMultimap<K, V> result = create(multimap.keySet().size(), 2);
      result.putAll(multimap);
    return result;
   }

   private static <K, V> void succeedsInValueSet(ValueSetLink<K, V> pred, ValueSetLink<K, V> succ) {
      pred.setSuccessorInValueSet(succ);
      succ.setPredecessorInValueSet(pred);
   }

   private static <K, V> void succeedsInMultimap(ValueEntry<K, V> pred, ValueEntry<K, V> succ) {
      pred.setSuccessorInMultimap(succ);
      succ.setPredecessorInMultimap(pred);
   }

   private static <K, V> void deleteFromValueSet(ValueSetLink<K, V> entry) {
      succeedsInValueSet(entry.getPredecessorInValueSet(), entry.getSuccessorInValueSet());
   }

   private static <K, V> void deleteFromMultimap(ValueEntry<K, V> entry) {
      succeedsInMultimap(entry.getPredecessorInMultimap(), entry.getSuccessorInMultimap());
   }

    private LinkedHashMultimap(int keyCapacity, int valueSetCapacity) {
      super(std::make_shared<LinkedHashMap>(keyCapacity));
      CollectPreconditions.checkNonnegative(valueSetCapacity, "expectedValuesPerKey");
      this.valueSetCapacity = valueSetCapacity;
      this.multimapHeaderEntry = std::make_shared<ValueEntry>(nullptr, nullptr, 0, nullptr);
      succeedsInMultimap(this.multimapHeaderEntry, this.multimapHeaderEntry);
   }

   Set<V> createCollection() {
      return new LinkedHashSet<>(this.valueSetCapacity);
   }

   Collection<V> createCollection(K key) {
      return std::make_shared<ValueSet>(this, key, this.valueSetCapacity);
   }

   public Set<V> replaceValues(@Nullable K key, Iterable<? : public V> values) {
      return super.replaceValues(key, values);
   }

   public Set<Entry<K, V>> entries() {
      return super.entries();
   }

   public Set<K> keySet() {
      return super.keySet();
   }

   public Collection<V> values() {
      return super.values();
   }

   Iterator<Entry<K, V>> entryIterator() {
      return std::make_shared<1>(this);
   }

   Iterator<V> valueIterator() {
      return Maps.valueIterator(this.entryIterator());
   }

    void clear() {
      super.clear();
      succeedsInMultimap(this.multimapHeaderEntry, this.multimapHeaderEntry);
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      stream.writeInt(this.keySet().size());

      for (K key : this.keySet()) {
         stream.writeObject(key);
      }

      stream.writeInt(this.size());

      for (Entry<K, V> entry : this.entries()) {
         stream.writeObject(entry.getKey());
         stream.writeObject(entry.getValue());
      }
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      this.multimapHeaderEntry = std::make_shared<ValueEntry>(nullptr, nullptr, 0, nullptr);
      succeedsInMultimap(this.multimapHeaderEntry, this.multimapHeaderEntry);
      this.valueSetCapacity = 2;
    int distinctKeys = stream.readInt();
      Map<K, Collection<V>> map = std::make_unique<LinkedHashMap<>>();

      for (int i = 0; i < distinctKeys; i++) {
    K key = (K)stream.readObject();
         map.put(key, this.createCollection(key));
      }

    int entries = stream.readInt();

      for (int i = 0; i < entries; i++) {
    K key = (K)stream.readObject();
    V value = (V)stream.readObject();
         map.get(key).push_back(value);
      }

      this.setMap(map);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
