package zombie.gameStates;

import zombie.core.Core;
import zombie.core.SpriteRenderer;
import zombie.core.textures.Texture;

final class TISLogoState$LogoElement {
   Texture m_texture;
   int m_x;
   int m_y;
   int m_width;
   int m_height;

   TISLogoState$LogoElement(String var1) {
      this.m_texture = Texture.getSharedTexture(var1);
      if (this.m_texture != null) {
         this.m_width = this.m_texture.getWidth();
         this.m_height = this.m_texture.getHeight();
      }
   }

   void centerOnScreen() {
      this.m_x = (Core.getInstance().getScreenWidth() - this.m_width) / 2;
      this.m_y = (Core.getInstance().getScreenHeight() - this.m_height) / 2;
   }

   void setPos(int var1, int var2) {
      this.m_x = var1;
      this.m_y = var2;
   }

   void setSize(int var1, int var2) {
      this.m_width = var1;
      this.m_height = var2;
   }

   void render(float var1) {
      if (this.m_texture != null && this.m_texture.isReady()) {
         SpriteRenderer.instance.renderi(this.m_texture, this.m_x, this.m_y, this.m_width, this.m_height, 1.0F, 1.0F, 1.0F, var1, null);
      }
   }
}
