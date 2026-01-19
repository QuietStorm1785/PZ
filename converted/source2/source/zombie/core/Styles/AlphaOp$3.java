package zombie.core.Styles;

import org.lwjgl.util.ReadableColor;

enum AlphaOp$3 {
   protected int calc(ReadableColor var1, int var2) {
      float var3 = var1.getAlpha() * var2 * 0.003921569F;
      float var4 = var3 * 0.003921569F;
      return (int)(var1.getRed() * var4) << 0 | (int)(var1.getGreen() * var4) << 8 | (int)(var1.getBlue() * var4) << 16;
   }
}
