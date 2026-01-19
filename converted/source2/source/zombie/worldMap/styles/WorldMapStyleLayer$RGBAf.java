package zombie.worldMap.styles;

import zombie.popman.ObjectPool;

public final class WorldMapStyleLayer$RGBAf {
   public float r;
   public float g;
   public float b;
   public float a;
   public static final ObjectPool<WorldMapStyleLayer$RGBAf> s_pool = new ObjectPool(WorldMapStyleLayer$RGBAf::new);

   public WorldMapStyleLayer$RGBAf() {
      this.r = this.g = this.b = this.a = 1.0F;
   }

   public WorldMapStyleLayer$RGBAf init(float var1, float var2, float var3, float var4) {
      this.r = var1;
      this.g = var2;
      this.b = var3;
      this.a = var4;
      return this;
   }
}
