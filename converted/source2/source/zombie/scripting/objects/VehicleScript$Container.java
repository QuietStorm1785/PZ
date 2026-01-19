package zombie.scripting.objects;

public final class VehicleScript$Container {
   public int capacity;
   public int seat = -1;
   public String seatID;
   public String luaTest;
   public String contentType;
   public boolean conditionAffectsCapacity = false;

   VehicleScript$Container makeCopy() {
      VehicleScript$Container var1 = new VehicleScript$Container();
      var1.capacity = this.capacity;
      var1.seat = this.seat;
      var1.seatID = this.seatID;
      var1.luaTest = this.luaTest;
      var1.contentType = this.contentType;
      var1.conditionAffectsCapacity = this.conditionAffectsCapacity;
      return var1;
   }
}
