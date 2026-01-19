package zombie.core.opengl;

import zombie.core.SpriteRenderer;
import zombie.core.opengl.GLState.Base4Ints;
import zombie.core.opengl.GLState.C4IntsValue;

public final class GLState$CBlendFuncSeparate extends Base4Ints {
   void Set(C4IntsValue var1) {
      SpriteRenderer.instance.glBlendFuncSeparate(var1.a, var1.b, var1.c, var1.d);
   }
}
