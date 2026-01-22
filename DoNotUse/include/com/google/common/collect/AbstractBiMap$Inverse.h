#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractBiMap {
public:
    static const long serialVersionUID = 0L;

   AbstractBiMap$Inverse(Map<K, V> backward, AbstractBiMap<V, K> forward) {
      super(backward, forward, nullptr);
   }

    K checkKey(K key) {
      return (K)this.inverse.checkValue(key);
   }

    V checkValue(V value) {
      return (V)this.inverse.checkKey(value);
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      stream.writeObject(this.inverse());
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      this.setInverse((AbstractBiMap)stream.readObject());
   }

    void* readResolve() {
      return this.inverse().inverse();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
