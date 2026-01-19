package zombie.core.skinnedmodel;

import zombie.core.skinnedmodel.DeadBodyAtlas.RenderJob;
import zombie.core.textures.TextureDraw.GenericDrawer;

final class DeadBodyAtlas$DebugDrawInWorld extends GenericDrawer {
   RenderJob job;
   boolean bRendered;

   private DeadBodyAtlas$DebugDrawInWorld() {
   }

   public void init(RenderJob var1) {
      this.job = var1;
      this.bRendered = false;
   }

   public void render() {
      this.job.animatedModel.DoRenderToWorld(this.job.body.x, this.job.body.y, this.job.body.z, this.job.m_animPlayerAngle);
      this.bRendered = true;
   }

   public void postRender() {
      if (this.job.animatedModel != null) {
         if (this.bRendered) {
            if (!$assertionsDisabled && DeadBodyAtlas.JobPool.contains(this.job)) {
               throw new AssertionError();
            }

            DeadBodyAtlas.JobPool.push(this.job);
         } else {
            if (!$assertionsDisabled && DeadBodyAtlas.JobPool.contains(this.job)) {
               throw new AssertionError();
            }

            DeadBodyAtlas.JobPool.push(this.job);
         }

         this.job.animatedModel.postRender(this.bRendered);
      }
   }
}
