package zombie.scripting.objects;

import java.util.ArrayList;
import zombie.scripting.objects.VehicleScript.Anim;
import zombie.scripting.objects.VehicleScript.Position;
import zombie.scripting.objects.VehicleScript.Passenger.SwitchSeat;

public final class VehicleScript$Passenger {
   public String id;
   public final ArrayList<Anim> anims = new ArrayList<>();
   public final ArrayList<SwitchSeat> switchSeats = new ArrayList<>();
   public boolean hasRoof = true;
   public boolean showPassenger = false;
   public String door;
   public String door2;
   public String area;
   public final ArrayList<Position> positions = new ArrayList<>();

   public String getId() {
      return this.id;
   }

   public VehicleScript$Passenger makeCopy() {
      VehicleScript$Passenger var1 = new VehicleScript$Passenger();
      var1.id = this.id;

      for (int var2 = 0; var2 < this.anims.size(); var2++) {
         var1.anims.add(this.anims.get(var2).makeCopy());
      }

      for (int var3 = 0; var3 < this.switchSeats.size(); var3++) {
         var1.switchSeats.add(this.switchSeats.get(var3).makeCopy());
      }

      var1.hasRoof = this.hasRoof;
      var1.showPassenger = this.showPassenger;
      var1.door = this.door;
      var1.door2 = this.door2;
      var1.area = this.area;

      for (int var4 = 0; var4 < this.positions.size(); var4++) {
         var1.positions.add(this.positions.get(var4).makeCopy());
      }

      return var1;
   }

   public int getPositionCount() {
      return this.positions.size();
   }

   public Position getPosition(int var1) {
      return this.positions.get(var1);
   }

   public Position getPositionById(String var1) {
      for (int var2 = 0; var2 < this.positions.size(); var2++) {
         Position var3 = this.positions.get(var2);
         if (var3.id != null && var3.id.equals(var1)) {
            return var3;
         }
      }

      return null;
   }

   public SwitchSeat getSwitchSeatById(String var1) {
      for (int var2 = 0; var2 < this.switchSeats.size(); var2++) {
         SwitchSeat var3 = this.switchSeats.get(var2);
         if (var3.id != null && var3.id.equals(var1)) {
            return var3;
         }
      }

      return null;
   }
}
