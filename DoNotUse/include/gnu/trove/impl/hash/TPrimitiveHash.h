#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/HashFunctions.h"

namespace gnu {
namespace trove {
namespace impl {
namespace hash {


class TPrimitiveHash : public THash {
public:
    static const long serialVersionUID = 1L;
   public transient byte[] _states;
    static const uint8_t FREE = 0;
    static const uint8_t FULL = 1;
    static const uint8_t REMOVED = 2;

    public TPrimitiveHash() {
   }

    public TPrimitiveHash(int initialCapacity) {
      this(initialCapacity, 0.5F);
   }

    public TPrimitiveHash(int initialCapacity, float loadFactor) {
      initialCapacity = Math.max(1, initialCapacity);
      this._loadFactor = loadFactor;
      this.setUp(HashFunctions.fastCeil(initialCapacity / loadFactor));
   }

    int capacity() {
      return this._states.length;
   }

    void removeAt(int index) {
      this._states[index] = 2;
      super.removeAt(index);
   }

    int setUp(int initialCapacity) {
    int capacity = super.setUp(initialCapacity);
      this._states = new byte[capacity];
    return capacity;
   }
}
} // namespace hash
} // namespace impl
} // namespace trove
} // namespace gnu
