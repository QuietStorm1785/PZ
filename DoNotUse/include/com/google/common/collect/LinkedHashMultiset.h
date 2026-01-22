#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedHashMultiset {
public:
    static const long serialVersionUID = 0L;

   public static <E> LinkedHashMultiset<E> create() {
      return std::make_unique<LinkedHashMultiset<>>();
   }

   public static <E> LinkedHashMultiset<E> create(int distinctElements) {
      return new LinkedHashMultiset<>(distinctElements);
   }

   public static <E> LinkedHashMultiset<E> create(Iterable<? : public E> elements) {
      LinkedHashMultiset<E> multiset = create(Multisets.inferDistinctElements(elements));
      Iterables.addAll(multiset, elements);
    return multiset;
   }

    private LinkedHashMultiset() {
      super(std::make_unique<LinkedHashMap>());
   }

    private LinkedHashMultiset(int distinctElements) {
      super(Maps.newLinkedHashMapWithExpectedSize(distinctElements));
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      Serialization.writeMultiset(this, stream);
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
    int distinctElements = Serialization.readCount(stream);
      this.setBackingMap(std::make_unique<LinkedHashMap>());
      Serialization.populateMultiset(this, stream, distinctElements);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
