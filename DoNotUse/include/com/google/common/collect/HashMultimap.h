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
#include "com/google/common/base/Preconditions.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class HashMultimap {
public:
    static const int DEFAULT_VALUES_PER_KEY = 2;
   transient int expectedValuesPerKey = 2;
    static const long serialVersionUID = 0L;

   public static <K, V> HashMultimap<K, V> create() {
      return std::make_unique<HashMultimap<>>();
   }

   public static <K, V> HashMultimap<K, V> create(int expectedKeys, int expectedValuesPerKey) {
      return new HashMultimap<>(expectedKeys, expectedValuesPerKey);
   }

   public static <K, V> HashMultimap<K, V> create(Multimap<? : public K, ? : public V> multimap) {
      return new HashMultimap<>(multimap);
   }

    private HashMultimap() {
      super(std::make_unique<std::unordered_map>());
   }

    private HashMultimap(int expectedKeys, int expectedValuesPerKey) {
      super(Maps.newHashMapWithExpectedSize(expectedKeys));
      Preconditions.checkArgument(expectedValuesPerKey >= 0);
      this.expectedValuesPerKey = expectedValuesPerKey;
   }

    private HashMultimap(Multimap<? extends, ? extends) {
      super(Maps.newHashMapWithExpectedSize(multimap.keySet().size()));
      this.putAll(multimap);
   }

   Set<V> createCollection() {
      return Sets.newHashSetWithExpectedSize(this.expectedValuesPerKey);
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      Serialization.writeMultimap(this, stream);
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      this.expectedValuesPerKey = 2;
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
