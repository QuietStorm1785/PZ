package zombie.savefile;

import zombie.core.Core;
import zombie.core.textures.MultiTextureFBO2;
import zombie.core.textures.TextureFBO;
import zombie.core.textures.TextureDraw.GenericDrawer;

final class SavefileThumbnail$TakeScreenShotDrawer extends GenericDrawer {
   int m_playerIndex;

   SavefileThumbnail$TakeScreenShotDrawer(int var1) {
      this.m_playerIndex = var1;
   }

   public void render() {
      Core var1 = Core.getInstance();
      MultiTextureFBO2 var2 = var1.OffscreenBuffer;
      if (var2.Current == null) {
         Core.getInstance().TakeScreenshot(256, 256, 1029);
      } else if (var1.RenderShader == null) {
         Core.getInstance().getOffscreenBuffer().startDrawing(false, false);
         Core.getInstance().TakeScreenshot(256, 256, TextureFBO.getFuncs().GL_COLOR_ATTACHMENT0());
         Core.getInstance().getOffscreenBuffer().endDrawing();
      } else {
         SavefileThumbnail.createWithRenderShader(this.m_playerIndex);
      }
   }
}
