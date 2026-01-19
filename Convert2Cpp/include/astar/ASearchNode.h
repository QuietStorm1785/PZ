#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace astar {

class ASearchNode {
public:
    double g = 0.0;
    int depth;

    double f() {
      return this.g() + this.h();
   }

    double g() {
      return this.g;
   }

    void setG(double var1) {
      this.g = var1;
   }

    int getDepth() {
      return this.depth;
   }

    void setDepth(int var1) {
      this.depth = var1;
   }
}
} // namespace astar
