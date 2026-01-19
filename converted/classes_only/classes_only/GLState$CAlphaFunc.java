package zombie.core.opengl;

import zombie.core.SpriteRenderer;
import zombie.core.opengl.GLState.BaseIntFloat;
import zombie.core.opengl.GLState.CIntFloatValue;

public final class GLState$CAlphaFunc extends BaseIntFloat {
   void Set(CIntFloatValue var1) {
      SpriteRenderer.instance.glAlphaFunc(var1.a, var1.b);
   }
}
