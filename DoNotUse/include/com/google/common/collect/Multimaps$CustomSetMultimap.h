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
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   transient Supplier<? : public Set<V>> factory;
    static const long serialVersionUID = 0L;

   Multimaps$CustomSetMultimap(Map<K, Collection<V>> map, Supplier<? : public Set<V>> factory) {
      super(map);
      this.factory = (Supplier<? : public Set<V>>)Preconditions.checkNotNull(factory);
   }

   protected Set<V> createCollection() {
      return (Set<V>)this.factory.get();
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      stream.writeObject(this.factory);
      stream.writeObject(this.backingMap());
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      this.factory = (Supplier<? : public Set<V>>)stream.readObject();
      Map<K, Collection<V>> map = (Map<K, Collection<V>>)stream.readObject();
      this.setMap(map);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
