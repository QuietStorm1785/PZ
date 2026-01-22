#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/junit/rules/TestWatcher.h"
#include "org/junit/runner/Description.h"

namespace zombie {
namespace vehicles {


class VehicleInterpolationTest {
public:
   VehicleInterpolationTest$1(VehicleInterpolationTest var1) {
      this.this$0 = var1;
   }

    void failed(std::exception var1, Description var2) {
      System.out.println("interpolation.buffer:");
      System.out.print("TIME: ");

      for (VehicleInterpolationData var4 : this.this$0.interpolation.buffer) {
         System.out.print(std::string.format(" %5d", var4.time));
      }

      System.out.println();
      System.out.print("   X: ");

      for (VehicleInterpolationData var6 : this.this$0.interpolation.buffer) {
         System.out.print(std::string.format(" %5.0f", var6.x));
      }
   }
}
} // namespace vehicles
} // namespace zombie
