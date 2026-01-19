package zombie.scripting.objects;

import org.joml.Vector3f;

public final class VehicleScript$Wheel {
   public String id;
   public String model;
   public boolean front;
   public final Vector3f offset = new Vector3f();
   public float radius = 0.5F;
   public float width = 0.4F;

   public String getId() {
      return this.id;
   }

   public Vector3f getOffset() {
      return this.offset;
   }

   VehicleScript$Wheel makeCopy() {
      VehicleScript$Wheel var1 = new VehicleScript$Wheel();
      var1.id = this.id;
      var1.model = this.model;
      var1.front = this.front;
      var1.offset.set(this.offset);
      var1.radius = this.radius;
      var1.width = this.width;
      return var1;
   }
}
