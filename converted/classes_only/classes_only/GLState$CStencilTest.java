package zombie.core.opengl;

import zombie.core.SpriteRenderer;
import zombie.core.opengl.GLState.BaseBoolean;
import zombie.core.opengl.GLState.CBooleanValue;

public final class GLState$CStencilTest extends BaseBoolean {
   void Set(CBooleanValue var1) {
      if (var1.value) {
         SpriteRenderer.instance.glEnable(2960);
      } else {
         SpriteRenderer.instance.glDisable(2960);
      }
   }
}
