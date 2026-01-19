package zombie.vehicles;

import org.joml.Vector3f;

public final class UI3DScene$Ray {
   public final Vector3f origin = new Vector3f();
   public final Vector3f direction = new Vector3f();
   public float t;

   public UI3DScene$Ray() {
   }

   UI3DScene$Ray(UI3DScene$Ray var1) {
      this.origin.set(var1.origin);
      this.direction.set(var1.direction);
      this.t = var1.t;
   }
}
