#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class HashMultiset {
public:
    static const long serialVersionUID = 0L;

   public static <E> HashMultiset<E> create() {
      return std::make_unique<HashMultiset<>>();
   }

   public static <E> HashMultiset<E> create(int distinctElements) {
      return new HashMultiset<>(distinctElements);
   }

   public static <E> HashMultiset<E> create(Iterable<? : public E> elements) {
      HashMultiset<E> multiset = create(Multisets.inferDistinctElements(elements));
      Iterables.addAll(multiset, elements);
    return multiset;
   }

    private HashMultiset() {
      super(std::make_unique<std::unordered_map>());
   }

    private HashMultiset(int distinctElements) {
      super(Maps.newHashMapWithExpectedSize(distinctElements));
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      Serialization.writeMultiset(this, stream);
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
    int distinctElements = Serialization.readCount(stream);
      this.setBackingMap(Maps.newHashMap());
      Serialization.populateMultiset(this, stream, distinctElements);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
