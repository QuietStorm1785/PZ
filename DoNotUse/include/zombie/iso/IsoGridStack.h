#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {


class IsoGridStack {
public:
   public std::vector<std::vector<IsoGridSquare>> Squares;

    public IsoGridStack(int var1) {
      this.Squares = new std::vector<>(var1);

      for (int var2 = 0; var2 < var1; var2++) {
         this.Squares.push_back(new std::vector<>(5000));
      }
   }
}
} // namespace iso
} // namespace zombie
