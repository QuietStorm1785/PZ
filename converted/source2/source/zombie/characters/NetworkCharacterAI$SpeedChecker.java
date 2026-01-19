package zombie.characters;

import zombie.core.utils.UpdateLimit;
import zombie.iso.IsoUtils;
import zombie.iso.Vector2;
import zombie.network.packets.hit.IMovable;

class NetworkCharacterAI$SpeedChecker implements IMovable {
   private static final int checkDelay = 5000;
   private static final int checkInterval = 1000;
   private final UpdateLimit updateLimit = new UpdateLimit(5000L);
   private final Vector2 position = new Vector2();
   private boolean isInVehicle;
   private float speed;

   private NetworkCharacterAI$SpeedChecker() {
   }

   public float getSpeed() {
      return this.speed;
   }

   public boolean isVehicle() {
      return this.isInVehicle;
   }

   private void set(float var1, float var2, boolean var3) {
      if (this.updateLimit.Check()) {
         if (5000L == this.updateLimit.getDelay()) {
            this.updateLimit.Reset(1000L);
            this.position.set(0.0F, 0.0F);
            this.speed = 0.0F;
         }

         this.isInVehicle = var3;
         if (this.position.getLength() != 0.0F) {
            this.speed = IsoUtils.DistanceTo(this.position.x, this.position.y, var1, var2);
         }

         this.position.set(var1, var2);
      }
   }

   private void reset() {
      this.updateLimit.Reset(5000L);
      this.isInVehicle = false;
      this.position.set(0.0F, 0.0F);
      this.speed = 0.0F;
   }

   public String getDescription() {
      return "SpeedChecker: speed=" + this.speed + " x=" + this.position.x + " y=" + this.position.y + " vehicle=" + this.isInVehicle;
   }
}
