package zombie.savefile;

import zombie.core.SpriteRenderer;
import zombie.core.sprite.SpriteRenderState;
import zombie.core.textures.TextureDraw.GenericDrawer;
import zombie.iso.IsoCamera;
import zombie.iso.PlayerCamera;

final class SavefileThumbnail$FixCameraDrawer extends GenericDrawer {
   int m_playerIndex;
   float m_zoom;
   int m_offscreenWidth;
   int m_offscreenHeight;

   SavefileThumbnail$FixCameraDrawer(int var1) {
      PlayerCamera var2 = IsoCamera.cameras[var1];
      this.m_playerIndex = var1;
      this.m_zoom = var2.zoom;
      this.m_offscreenWidth = var2.OffscreenWidth;
      this.m_offscreenHeight = var2.OffscreenHeight;
   }

   public void render() {
      SpriteRenderState var1 = SpriteRenderer.instance.getRenderingState();
      var1.playerCamera[this.m_playerIndex].zoom = this.m_zoom;
      var1.playerCamera[this.m_playerIndex].OffscreenWidth = this.m_offscreenWidth;
      var1.playerCamera[this.m_playerIndex].OffscreenHeight = this.m_offscreenHeight;
      var1.zoomLevel[this.m_playerIndex] = this.m_zoom;
   }
}
