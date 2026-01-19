package zombie.vehicles;

import org.joml.Vector3f;

public final class UI3DScene$Plane {
   public final Vector3f point = new Vector3f();
   public final Vector3f normal = new Vector3f();

   public UI3DScene$Plane() {
   }

   public UI3DScene$Plane(Vector3f var1, Vector3f var2) {
      this.point.set(var2);
      this.normal.set(var1);
   }

   public UI3DScene$Plane set(Vector3f var1, Vector3f var2) {
      this.point.set(var2);
      this.normal.set(var1);
      return this;
   }
}
