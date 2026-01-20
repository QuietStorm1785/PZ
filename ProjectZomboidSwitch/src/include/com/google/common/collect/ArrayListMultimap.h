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
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ArrayListMultimap {
public:
    static const int DEFAULT_VALUES_PER_KEY = 3;
   transient int expectedValuesPerKey;
    static const long serialVersionUID = 0L;

   public static <K, V> ArrayListMultimap<K, V> create() {
      return std::make_unique<ArrayListMultimap<>>();
   }

   public static <K, V> ArrayListMultimap<K, V> create(int expectedKeys, int expectedValuesPerKey) {
      return new ArrayListMultimap<>(expectedKeys, expectedValuesPerKey);
   }

   public static <K, V> ArrayListMultimap<K, V> create(Multimap<? : public K, ? : public V> multimap) {
      return new ArrayListMultimap<>(multimap);
   }

    private ArrayListMultimap() {
      super(std::make_unique<std::unordered_map>());
      this.expectedValuesPerKey = 3;
   }

    private ArrayListMultimap(int expectedKeys, int expectedValuesPerKey) {
      super(Maps.newHashMapWithExpectedSize(expectedKeys));
      CollectPreconditions.checkNonnegative(expectedValuesPerKey, "expectedValuesPerKey");
      this.expectedValuesPerKey = expectedValuesPerKey;
   }

    private ArrayListMultimap(Multimap<? extends, ? extends) {
      this(multimap.keySet().size(), dynamic_cast<ArrayListMultimap*>(multimap) != nullptr ? ((ArrayListMultimap)multimap).expectedValuesPerKey : 3);
      this.putAll(multimap);
   }

   List<V> createCollection() {
      return new std::vector<>(this.expectedValuesPerKey);
   }

    void trimToSize() {
      for (Collection<V> collection : this.backingMap().values()) {
         std::vector<V> arrayList = (std::vector<V>)collection;
         arrayList.trimToSize();
      }
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      Serialization.writeMultimap(this, stream);
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      this.expectedValuesPerKey = 3;
    int distinctKeys = Serialization.readCount(stream);
      Map<K, Collection<V>> map = Maps.newHashMap();
      this.setMap(map);
      Serialization.populateMultimap(this, stream, distinctKeys);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
