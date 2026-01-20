#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/IntIterator.h"
#include "zombie/util/map/IntKeyOpenHashMap/KeySet/1.h"
#include "zombie/util/set/AbstractIntSet.h"

namespace zombie {
namespace util {
namespace map {


class IntKeyOpenHashMap {
public:
   private IntKeyOpenHashMap$KeySet(IntKeyOpenHashMap var1) {
      this.this$0 = var1;
   }

    void clear() {
      this.this$0.clear();
   }

    bool contains(int var1) {
      return this.this$0.containsKey(var1);
   }

    IntIterator iterator() {
      return std::make_shared<1>(this);
   }

    bool remove(int var1) {
    bool var2 = this.this$0.containsKey(var1);
      if (var2) {
         this.this$0.remove(var1);
      }

    return var2;
   }

    int size() {
      return this.this$0.size;
   }
}
} // namespace map
} // namespace util
} // namespace zombie
