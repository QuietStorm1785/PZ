#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "absl/container/flat_hash_map.h"
#include <algorithm>

namespace zombie {



class IntArrayCache {
public:
   static std::shared_ptr<IntArrayCache> instance;
   absl::flat_hash_map<int, std::stack<std::vector<int>>> Map;


   void Init() {
      for (int var1 = 0; var1 < 100; var1++) {
         std::stack<std::vector<int>> var2;
         for (int var3 = 0; var3 < 1000; var3++) {
            var2.push(std::vector<int>(var1));
         }
         Map[var1] = std::move(var2);
      }
   }


    void put(const std::vector<int>& var1) {
        auto& stackRef = Map[var1.size()];
        stackRef.push(var1);
    }

      std::vector<int> get(int var1) {
         auto it = Map.find(var1);
         if (it != Map.end() && !it->second.empty()) {
            auto result = it->second.top();
            it->second.pop();
            return result;
         }
         return std::vector<int>(var1);
      }
}
} // namespace zombie
