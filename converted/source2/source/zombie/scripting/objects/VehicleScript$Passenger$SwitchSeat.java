package zombie.scripting.objects;

public final class VehicleScript$Passenger$SwitchSeat {
   public String id;
   public int seat;
   public String anim;
   public float rate = 1.0F;
   public String sound;

   public String getId() {
      return this.id;
   }

   public VehicleScript$Passenger$SwitchSeat makeCopy() {
      VehicleScript$Passenger$SwitchSeat var1 = new VehicleScript$Passenger$SwitchSeat();
      var1.id = this.id;
      var1.seat = this.seat;
      var1.anim = this.anim;
      var1.rate = this.rate;
      var1.sound = this.sound;
      return var1;
   }
}
