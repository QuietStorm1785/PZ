package zombie.ui;

import zombie.iso.Vector2;

class RadialProgressBar$RadSegment {
   Vector2[] vertex = new Vector2[3];
   Vector2[] uv = new Vector2[3];

   private RadialProgressBar$RadSegment() {
   }

   private RadialProgressBar$RadSegment set(int var1, float var2, float var3, float var4, float var5) {
      this.vertex[var1] = new Vector2(var2, var3);
      this.uv[var1] = new Vector2(var4, var5);
      return this;
   }

   private void set(float var1, float var2, float var3, float var4, float var5, float var6) {
      this.vertex[0] = new Vector2(var1, var2);
      this.vertex[1] = new Vector2(var3, var4);
      this.vertex[2] = new Vector2(var5, var6);
      this.uv[0] = new Vector2(var1, var2);
      this.uv[1] = new Vector2(var3, var4);
      this.uv[2] = new Vector2(var5, var6);
   }
}
