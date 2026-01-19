package zombie.core.opengl;

import zombie.core.SpriteRenderer;
import zombie.core.opengl.GLState.BaseInt;
import zombie.core.opengl.GLState.CIntValue;

public final class GLState$CStencilMask extends BaseInt {
   void Set(CIntValue var1) {
      SpriteRenderer.instance.glStencilMask(var1.value);
   }
}
