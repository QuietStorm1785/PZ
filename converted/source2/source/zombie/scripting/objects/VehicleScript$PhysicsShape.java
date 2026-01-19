package zombie.scripting.objects;

import org.joml.Vector3f;
import zombie.core.math.PZMath;

public final class VehicleScript$PhysicsShape {
   public int type;
   public final Vector3f offset = new Vector3f();
   public final Vector3f rotate = new Vector3f();
   public final Vector3f extents = new Vector3f();
   public float radius;

   public String getTypeString() {
      switch (this.type) {
         case 1:
            return "box";
         case 2:
            return "sphere";
         default:
            throw new RuntimeException("unhandled VehicleScript.PhysicsShape");
      }
   }

   public Vector3f getOffset() {
      return this.offset;
   }

   public Vector3f getExtents() {
      return this.extents;
   }

   public Vector3f getRotate() {
      return this.rotate;
   }

   public float getRadius() {
      return this.radius;
   }

   public void setRadius(float var1) {
      this.radius = PZMath.clamp(var1, 0.05F, 5.0F);
   }
}
