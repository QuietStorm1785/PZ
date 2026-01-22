#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/states/SwipeStatePlayer/LOSVisitor.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject/VisionResult.h"
#include "zombie/iso/LosUtil/TestResults.h"
#include "zombie/iso/objects/IsoWindow.h"

namespace zombie {
namespace ai {
namespace states {


class SwipeStatePlayer {
public:
    TestResults test;
    IsoWindow window;

   private SwipeStatePlayer$WindowVisitor() {
   }

    void init() {
      this.test = TestResults.Clear;
      this.window = nullptr;
   }

    bool visit(IsoGridSquare var1, IsoGridSquare var2) {
      if (var1 != nullptr && var2 != nullptr) {
    bool var3 = true;
    bool var4 = false;
    TestResults var5 = var1.testVisionAdjacent(var2.getX() - var1.getX(), var2.getY() - var1.getY(), var2.getZ() - var1.getZ(), var3, var4);
         if (var5 == TestResults.ClearThroughWindow) {
    IsoWindow var6 = var1.getWindowTo(var2);
            if (this.isHittable(var6) && var6.TestVision(var1, var2) == VisionResult.Unblocked) {
               this.window = var6;
    return true;
            }
         }

         if (var5 != TestResults.Blocked
            && this.test != TestResults.Clear
            && (var5 != TestResults.ClearThroughWindow || this.test != TestResults.ClearThroughOpenDoor)) {
            if (var5 == TestResults.ClearThroughClosedDoor && this.test == TestResults.ClearThroughOpenDoor) {
               this.test = var5;
            }
         } else {
            this.test = var5;
         }

         return this.test == TestResults.Blocked;
      } else {
    return false;
      }
   }

    TestResults getResult() {
      return this.test;
   }

    bool isHittable(IsoWindow var1) {
      if (var1 == nullptr) {
    return false;
      } else {
         return var1.isBarricaded() ? true : !var1.isDestroyed() && !var1.IsOpen();
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
