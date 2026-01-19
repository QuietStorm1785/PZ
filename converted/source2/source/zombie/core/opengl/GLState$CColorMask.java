package zombie.core.opengl;

import zombie.core.SpriteRenderer;
import zombie.core.opengl.GLState.Base4Booleans;
import zombie.core.opengl.GLState.C4BooleansValue;

public final class GLState$CColorMask extends Base4Booleans {
   void Set(C4BooleansValue var1) {
      SpriteRenderer.instance.glColorMask(var1.a ? 1 : 0, var1.b ? 1 : 0, var1.c ? 1 : 0, var1.d ? 1 : 0);
   }
}
