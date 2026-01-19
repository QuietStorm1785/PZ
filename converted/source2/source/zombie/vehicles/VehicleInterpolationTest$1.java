package zombie.vehicles;

import org.junit.rules.TestWatcher;
import org.junit.runner.Description;

class VehicleInterpolationTest$1 extends TestWatcher {
   VehicleInterpolationTest$1(VehicleInterpolationTest var1) {
      this.this$0 = var1;
   }

   protected void failed(Throwable var1, Description var2) {
      System.out.println("interpolation.buffer:");
      System.out.print("TIME: ");

      for (VehicleInterpolationData var4 : this.this$0.interpolation.buffer) {
         System.out.print(String.format(" %5d", var4.time));
      }

      System.out.println();
      System.out.print("   X: ");

      for (VehicleInterpolationData var6 : this.this$0.interpolation.buffer) {
         System.out.print(String.format(" %5.0f", var6.x));
      }
   }
}
