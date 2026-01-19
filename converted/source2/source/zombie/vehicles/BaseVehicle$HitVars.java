package zombie.vehicles;

import org.joml.Vector3f;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoZombie;
import zombie.iso.Vector2;

public class BaseVehicle$HitVars {
   private static final float speedCap = 10.0F;
   private final Vector3f velocity = new Vector3f();
   private final Vector2 collision = new Vector2();
   private float dot;
   protected float vehicleImpulse;
   protected float vehicleSpeed;
   public final Vector3f targetImpulse = new Vector3f();
   public boolean isVehicleHitFromFront;
   public boolean isTargetHitFromBehind;
   public int vehicleDamage;
   public float hitSpeed;

   public void calc(IsoGameCharacter var1, BaseVehicle var2) {
      var2.getLinearVelocity(this.velocity);
      this.velocity.y = 0.0F;
      if (var1 instanceof IsoZombie) {
         this.vehicleSpeed = Math.min(this.velocity.length(), 10.0F);
         this.hitSpeed = this.vehicleSpeed + var2.getClientForce() / var2.getFudgedMass();
      } else {
         this.vehicleSpeed = (float)Math.sqrt(this.velocity.x * this.velocity.x + this.velocity.z * this.velocity.z);
         if (var1.isOnFloor()) {
            this.hitSpeed = Math.max(this.vehicleSpeed * 6.0F, 5.0F);
         } else {
            this.hitSpeed = Math.max(this.vehicleSpeed * 2.0F, 5.0F);
         }
      }

      this.targetImpulse.set(var2.x - var1.x, 0.0F, var2.y - var1.y);
      this.targetImpulse.normalize();
      this.velocity.normalize();
      this.dot = this.velocity.dot(this.targetImpulse);
      this.targetImpulse.normalize();
      this.targetImpulse.mul(3.0F * this.vehicleSpeed / 10.0F);
      this.targetImpulse.set(this.targetImpulse.x, this.targetImpulse.y, this.targetImpulse.z);
      this.vehicleImpulse = var2.getFudgedMass() * 7.0F * this.vehicleSpeed / 10.0F * Math.abs(this.dot);
      this.isTargetHitFromBehind = "BEHIND".equals(var1.testDotSide(var2));
   }
}
