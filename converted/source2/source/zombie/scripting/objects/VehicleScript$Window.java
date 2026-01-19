package zombie.scripting.objects;

public final class VehicleScript$Window {
   public boolean openable;

   VehicleScript$Window makeCopy() {
      VehicleScript$Window var1 = new VehicleScript$Window();
      var1.openable = this.openable;
      return var1;
   }
}
