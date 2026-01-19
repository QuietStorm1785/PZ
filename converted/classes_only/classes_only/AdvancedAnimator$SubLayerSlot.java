package zombie.core.skinnedmodel.advancedanimation;

public class AdvancedAnimator$SubLayerSlot {
   public boolean shouldBeActive = false;
   public final AnimLayer animLayer;

   public AdvancedAnimator$SubLayerSlot(AnimLayer var1, IAnimatable var2, IAnimEventCallback var3) {
      this.animLayer = new AnimLayer(var1, var2, var3);
   }

   public void update() {
      this.animLayer.Update();
   }

   public void transitionTo(AnimState var1, boolean var2) {
      this.animLayer.TransitionTo(var1, var2);
      this.shouldBeActive = var1 != null;
   }

   public void applyTransition() {
      if (!this.shouldBeActive) {
         this.transitionTo(null, false);
      }
   }
}
