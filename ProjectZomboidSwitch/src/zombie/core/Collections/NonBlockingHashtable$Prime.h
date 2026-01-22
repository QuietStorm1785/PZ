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

class NonBlockingHashtable {
public:
    const void* _V;

   NonBlockingHashtable$Prime(Object var1) {
      this._V = var1;
   }

    static void* unbox(void* var0) {
      return dynamic_cast<NonBlockingHashtable*>(var0) != nullptr$Prime ? ((NonBlockingHashtable$Prime)var0)._V : var0;
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
