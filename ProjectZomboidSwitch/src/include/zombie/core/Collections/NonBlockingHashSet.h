#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashSet {
public:
    static const void* V = "";
   private const NonBlockingHashMap<E, Object> _map = std::make_unique<NonBlockingHashMap>();

    bool add(E var1) {
      return this._map.putIfAbsent(var1, V) != V;
   }

    bool contains(void* var1) {
      return this._map.containsKey(var1);
   }

    bool remove(void* var1) {
      return this._map.remove(var1) == V;
   }

    int size() {
      return this._map.size();
   }

    void clear() {
      this._map.clear();
   }

   public Iterator<E> iterator() {
      return this._map.keySet().iterator();
   }

    void readOnly() {
      throw RuntimeException("Unimplemented");
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
