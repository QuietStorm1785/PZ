package zombie.core.skinnedmodel.model;

import zombie.core.textures.TextureDraw.GenericDrawer;

public final class ModelOutlines$Drawer extends GenericDrawer {
   boolean m_startFrame;
   int m_playerIndex;

   public void render() {
      if (this.m_startFrame) {
         ModelOutlines.instance.startFrame(this.m_playerIndex);
      } else {
         ModelOutlines.instance.endFrame(this.m_playerIndex);
      }
   }

   public void postRender() {
      ModelOutlines.instance.m_drawerPool.release(this);
   }
}
