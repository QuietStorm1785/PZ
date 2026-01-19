package zombie.core.textures;

public enum PNGDecoder$Format {
   ALPHA(1, true),
   LUMINANCE(1, false),
   LUMINANCE_ALPHA(2, true),
   RGB(3, false),
   RGBA(4, true),
   BGRA(4, true),
   ABGR(4, true);

   final int numComponents;
   final boolean hasAlpha;

   private PNGDecoder$Format(int var3, boolean var4) {
      this.numComponents = var3;
      this.hasAlpha = var4;
   }

   public int getNumComponents() {
      return this.numComponents;
   }

   public boolean isHasAlpha() {
      return this.hasAlpha;
   }
}
