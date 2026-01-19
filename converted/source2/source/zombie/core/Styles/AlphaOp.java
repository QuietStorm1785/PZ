package zombie.core.Styles;

import java.nio.FloatBuffer;
import org.lwjgl.util.ReadableColor;

public enum AlphaOp {
   PREMULTIPLY,
   KEEP,
   ZERO;

   private static final float PREMULT_ALPHA = 0.003921569F;

   public final void op(ReadableColor var1, int var2, FloatBuffer var3) {
      var3.put(Float.intBitsToFloat(this.calc(var1, var2)));
   }

   public final void op(int var1, int var2, FloatBuffer var3) {
      var3.put(Float.intBitsToFloat(var1));
   }

   protected abstract int calc(ReadableColor var1, int var2);
}
