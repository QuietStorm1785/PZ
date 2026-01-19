package zombie.scripting.objects;

import org.joml.Vector3f;

public final class VehicleScript$Model {
   public String id;
   public String file;
   public float scale = 1.0F;
   public final Vector3f offset = new Vector3f();
   public final Vector3f rotate = new Vector3f();

   public String getId() {
      return this.id;
   }

   public Vector3f getOffset() {
      return this.offset;
   }

   public Vector3f getRotate() {
      return this.rotate;
   }

   VehicleScript$Model makeCopy() {
      VehicleScript$Model var1 = new VehicleScript$Model();
      var1.id = this.id;
      var1.file = this.file;
      var1.scale = this.scale;
      var1.offset.set(this.offset);
      var1.rotate.set(this.rotate);
      return var1;
   }
}
