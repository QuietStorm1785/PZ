package zombie.iso;

public final class IsoGridSquare$ResultLight {
   public int id;
   public int x;
   public int y;
   public int z;
   public int radius;
   public float r;
   public float g;
   public float b;
   public static final int RLF_NONE = 0;
   public static final int RLF_ROOMLIGHT = 1;
   public static final int RLF_TORCH = 2;
   public int flags;

   public IsoGridSquare$ResultLight copyFrom(IsoGridSquare$ResultLight var1) {
      this.id = var1.id;
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.radius = var1.radius;
      this.r = var1.r;
      this.g = var1.g;
      this.b = var1.b;
      this.flags = var1.flags;
      return this;
   }
}
