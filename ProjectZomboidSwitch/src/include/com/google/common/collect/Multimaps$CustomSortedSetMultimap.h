#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Supplier.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   transient Supplier<? : public SortedSet<V>> factory;
   transient Comparator<? super V> valueComparator;
    static const long serialVersionUID = 0L;

   Multimaps$CustomSortedSetMultimap(Map<K, Collection<V>> map, Supplier<? : public SortedSet<V>> factory) {
      super(map);
      this.factory = (Supplier<? : public SortedSet<V>>)Preconditions.checkNotNull(factory);
      this.valueComparator = ((SortedSet)factory.get()).comparator();
   }

   protected SortedSet<V> createCollection() {
      return (SortedSet<V>)this.factory.get();
   }

   public Comparator<? super V> valueComparator() {
      return this.valueComparator;
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      stream.writeObject(this.factory);
      stream.writeObject(this.backingMap());
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      this.factory = (Supplier<? : public SortedSet<V>>)stream.readObject();
      this.valueComparator = ((SortedSet)this.factory.get()).comparator();
      Map<K, Collection<V>> map = (Map<K, Collection<V>>)stream.readObject();
      this.setMap(map);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
