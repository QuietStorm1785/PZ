package zombie.core.opengl;

import zombie.core.SpriteRenderer;
import zombie.core.opengl.GLState.Base2Ints;
import zombie.core.opengl.GLState.C2IntsValue;

public final class GLState$CBlendFunc extends Base2Ints {
   void Set(C2IntsValue var1) {
      SpriteRenderer.instance.glBlendFunc(var1.a, var1.b);
   }
}
