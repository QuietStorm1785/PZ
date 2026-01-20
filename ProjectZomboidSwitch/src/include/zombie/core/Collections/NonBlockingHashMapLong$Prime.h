#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace Collections {

class NonBlockingHashMapLong {
public:
    const void* _V;

   NonBlockingHashMapLong$Prime(Object var1) {
      this._V = var1;
   }

    static void* unbox(void* var0) {
      return dynamic_cast<NonBlockingHashMapLong*>(var0) != nullptr$Prime ? ((NonBlockingHashMapLong$Prime)var0)._V : var0;
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
