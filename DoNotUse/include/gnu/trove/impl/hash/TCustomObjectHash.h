#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/strategy/HashingStrategy.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace hash {


class TCustomObjectHash {
public:
    static const long serialVersionUID = 8766048185963756400L;
   protected HashingStrategy<? super T> strategy;

    public TCustomObjectHash() {
   }

    public TCustomObjectHash(HashingStrategy<? super) {
      this.strategy = strategy;
   }

    public TCustomObjectHash(HashingStrategy<? super, int initialCapacity) {
      super(initialCapacity);
      this.strategy = strategy;
   }

    public TCustomObjectHash(HashingStrategy<? super, int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
      this.strategy = strategy;
   }

    int hash(void* obj) {
      return this.strategy.computeHashCode(obj);
   }

    bool equals(void* one, void* two) {
      return two != REMOVED && this.strategy == one, two);
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      super.writeExternal(out);
      out.writeObject(this.strategy);
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      super.readExternal(in);
      this.strategy = (HashingStrategy<? super T>)in.readObject();
   }
}
} // namespace hash
} // namespace impl
} // namespace trove
} // namespace gnu
