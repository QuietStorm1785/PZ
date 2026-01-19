package zombie.ai.states;

import zombie.ai.states.SwipeStatePlayer.LOSVisitor;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject.VisionResult;
import zombie.iso.LosUtil.TestResults;
import zombie.iso.objects.IsoWindow;

final class SwipeStatePlayer$WindowVisitor implements LOSVisitor {
   TestResults test;
   IsoWindow window;

   private SwipeStatePlayer$WindowVisitor() {
   }

   void init() {
      this.test = TestResults.Clear;
      this.window = null;
   }

   public boolean visit(IsoGridSquare var1, IsoGridSquare var2) {
      if (var1 != null && var2 != null) {
         boolean var3 = true;
         boolean var4 = false;
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

   public TestResults getResult() {
      return this.test;
   }

   boolean isHittable(IsoWindow var1) {
      if (var1 == null) {
         return false;
      } else {
         return var1.isBarricaded() ? true : !var1.isDestroyed() && !var1.IsOpen();
      }
   }
}
