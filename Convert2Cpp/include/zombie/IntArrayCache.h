#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TIntObjectHashMap.h"
#include <algorithm>

namespace zombie {


class IntArrayCache {
public:
    static IntArrayCache instance = new IntArrayCache();
   TIntObjectHashMap<Stack<Integer[]>> Map = std::make_unique<TIntObjectHashMap>();

    void Init() {
      for (int var1 = 0; var1 < 100; var1++) {
    std::stack var2 = new Stack();

         for (int var3 = 0; var3 < 1000; var3++) {
            var2.push(new Integer[var1]);
         }
      }
   }

    void put(Integer[] var1) {
      if (this.Map.containsKey(var1.length)) {
         ((Stack)this.Map.get(var1.length)).push(var1);
      } else {
    std::stack var2 = new Stack();
         var2.push(var1);
         this.Map.put(var1.length, var2);
      }
   }

   public Integer[] get(int var1) {
      if (this.Map.containsKey(var1)) {
    std::stack var2 = (Stack)this.Map.get(var1);
         if (!var2.isEmpty()) {
            return (Integer[])var2.pop();
         }
      }

      return new Integer[var1];
   }
}
} // namespace zombie
