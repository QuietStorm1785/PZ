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

class NonBlockingHashMap {
public:
   NonBlockingHashMap$NBHMEntry(TypeK var1, TypeV var2, Object var3) {
      super(var2, var3);
      this.this$0 = var1;
   }

    TypeV setValue(TypeV var1) {
      if (var1 == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this._val = var1;
         return (TypeV)this.this$0.put(this._key, var1);
      }
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
