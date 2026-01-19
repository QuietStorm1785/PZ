package zombie.vehicles;

import org.joml.Quaternionf;
import zombie.vehicles.BaseVehicle.Authorization;

public final class BaseVehicle$ServerVehicleState {
   public float x = -1.0F;
   public float y;
   public float z;
   public Quaternionf orient = new Quaternionf();
   public short flags;
   public Authorization netPlayerAuthorization = Authorization.Server;
   public short netPlayerId = 0;

   public BaseVehicle$ServerVehicleState() {
      this.flags = 0;
   }

   public void setAuthorization(BaseVehicle var1) {
      this.netPlayerAuthorization = var1.netPlayerAuthorization;
      this.netPlayerId = var1.netPlayerId;
   }

   public boolean shouldSend(BaseVehicle var1) {
      if (var1.getController() == null) {
         return false;
      } else if (var1.updateLockTimeout > System.currentTimeMillis()) {
         return false;
      } else {
         this.flags = (short)(this.flags & 1);
         if (!var1.isNetPlayerAuthorization(this.netPlayerAuthorization) || !var1.isNetPlayerId(this.netPlayerId)) {
            this.flags = (short)(this.flags | 16384);
         }

         this.flags = (short)(this.flags | var1.updateFlags);
         return this.flags != 0;
      }
   }
}
