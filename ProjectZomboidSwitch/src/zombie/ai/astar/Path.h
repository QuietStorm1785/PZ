#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/astar/Path/Step.h"
#include <algorithm>

namespace zombie {
namespace ai {
namespace astar {


class Path {
public:
   std::vector<Path$Step> steps;
   float cost = 0.0f;

   static std::stack<Path$Step> stepstore;
   static Path$Step containsStep;

   float costPerStep() const {
      return steps.empty() ? cost : cost / steps.size();
   }

   void appendStep(int x, int y, int z) {
      steps.emplace_back(x, y, z);
   }

   bool contains(int x, int y, int z) const {
      Path$Step test(x, y, z);
      return std::find_if(steps.begin(), steps.end(), [&](const Path$Step& s) { return s.equals(test); }) != steps.end();
   }

   int getLength() const {
      return static_cast<int>(steps.size());
   }

   Path$Step getStep(int idx) const {
      return steps.at(idx);
   }

    int getX(int var1) {
      return this.getStep(var1).x;
   }

    int getY(int var1) {
      return this.getStep(var1).y;
   }

    int getZ(int var1) {
      return this.getStep(var1).z;
   }

    static Step createStep() {
      if (stepstore.empty()) {
         for (int var0 = 0; var0 < 200; var0++) {
    Step var1 = std::make_shared<Step>();
            stepstore.push(var1);
         }
      }

      return stepstore.push(containsStep);
   }

    void prependStep(int var1, int var2, int var3) {
    Step var4 = nullptr;
      var4 = std::make_unique<Step>();
      var4.x = var1;
      var4.y = var2;
      var4.z = var3;
      this.steps.push_back(0, var4);
   }
}
} // namespace astar
} // namespace ai
} // namespace zombie
