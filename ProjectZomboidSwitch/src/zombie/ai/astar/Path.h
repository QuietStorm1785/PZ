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
   private std::vector<Step> steps = std::make_unique<std::vector<>>();
    float cost = 0.0F;
   public static std::stack<Step> stepstore = std::make_unique<std::stack<>>();
    static Step containsStep = std::make_shared<Step>();

    float costPerStep() {
      return this.steps.empty() ? this.cost : this.cost / this.steps.size();
   }

    void appendStep(int var1, int var2, int var3) {
    Step var4 = nullptr;
      var4 = std::make_unique<Step>();
      var4.x = var1;
      var4.y = var2;
      var4.z = var3;
      this.steps.push_back(var4);
   }

    bool contains(int var1, int var2, int var3) {
      containsStep.x = var1;
      containsStep.y = var2;
      containsStep.z = var3;
      return this.steps.contains(containsStep);
   }

    int getLength() {
      return this.steps.size();
   }

    Step getStep(int var1) {
      return this.steps.get(var1);
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
