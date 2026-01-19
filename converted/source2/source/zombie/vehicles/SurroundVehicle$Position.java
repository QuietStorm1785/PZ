package zombie.vehicles;

import org.joml.Vector2f;
import org.joml.Vector3f;
import zombie.characters.IsoZombie;
import zombie.vehicles.SurroundVehicle.PositionSide;

final class SurroundVehicle$Position {
   final Vector2f posLocal = new Vector2f();
   final Vector3f posWorld = new Vector3f();
   final Vector3f posAxis = new Vector3f();
   PositionSide side;
   IsoZombie zombie;
   float targetX;
   float targetY;
   boolean bBlocked;

   private SurroundVehicle$Position() {
   }

   boolean isOccupied() {
      return this.zombie != null;
   }

   void checkBlocked(BaseVehicle var1) {
      this.bBlocked = PolygonalMap2.instance.lineClearCollide(this.posWorld.x, this.posWorld.y, this.posAxis.x, this.posAxis.y, (int)var1.z, var1);
      if (!this.bBlocked) {
         this.bBlocked = !PolygonalMap2.instance.canStandAt(this.posWorld.x, this.posWorld.y, (int)var1.z, var1, false, false);
      }
   }
}
