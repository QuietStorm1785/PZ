package zombie.scripting.objects;

import org.joml.Vector3f;

public final class VehicleScript$Position {
   public String id;
   public final Vector3f offset = new Vector3f();
   public final Vector3f rotate = new Vector3f();
   public String area = null;

   public String getId() {
      return this.id;
   }

   public Vector3f getOffset() {
      return this.offset;
   }

   public Vector3f getRotate() {
      return this.rotate;
   }

   public String getArea() {
      return this.area;
   }

   VehicleScript$Position makeCopy() {
      VehicleScript$Position var1 = new VehicleScript$Position();
      var1.id = this.id;
      var1.offset.set(this.offset);
      var1.rotate.set(this.rotate);
      return var1;
   }
}
