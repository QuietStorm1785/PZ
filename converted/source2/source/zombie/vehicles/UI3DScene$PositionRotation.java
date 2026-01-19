package zombie.vehicles;

import org.joml.Vector3f;

final class UI3DScene$PositionRotation {
   final Vector3f pos = new Vector3f();
   final Vector3f rot = new Vector3f();

   private UI3DScene$PositionRotation() {
   }

   UI3DScene$PositionRotation set(UI3DScene$PositionRotation var1) {
      this.pos.set(var1.pos);
      this.rot.set(var1.rot);
      return this;
   }

   UI3DScene$PositionRotation set(float var1, float var2, float var3) {
      this.pos.set(var1, var2, var3);
      this.rot.set(0.0F, 0.0F, 0.0F);
      return this;
   }

   UI3DScene$PositionRotation set(float var1, float var2, float var3, float var4, float var5, float var6) {
      this.pos.set(var1, var2, var3);
      this.rot.set(var4, var5, var6);
      return this;
   }
}
