package zombie.core.opengl;

import zombie.core.SpriteRenderer;
import zombie.core.opengl.GLState.Base3Ints;
import zombie.core.opengl.GLState.C3IntsValue;

public final class GLState$CStencilFunc extends Base3Ints {
   void Set(C3IntsValue var1) {
      SpriteRenderer.instance.glStencilFunc(var1.a, var1.b, var1.c);
   }
}
