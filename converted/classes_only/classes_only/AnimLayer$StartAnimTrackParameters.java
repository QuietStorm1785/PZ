package zombie.core.skinnedmodel.advancedanimation;

import java.util.List;
import zombie.core.skinnedmodel.animation.BoneAxis;
import zombie.util.Pool;
import zombie.util.PooledObject;

class AnimLayer$StartAnimTrackParameters extends PooledObject {
   public int priority;
   List<AnimBoneWeight> subLayerBoneWeights;
   boolean syncTrackingEnabled;
   float speedScale;
   float initialWeight;
   boolean isLooped;
   boolean isReversed;
   String deferredBoneName;
   BoneAxis deferredBoneAxis;
   boolean useDeferredRotation;
   private static final Pool<AnimLayer$StartAnimTrackParameters> s_pool = new Pool(AnimLayer$StartAnimTrackParameters::new);

   private void reset() {
      this.priority = 0;
      this.subLayerBoneWeights = null;
      this.syncTrackingEnabled = false;
      this.speedScale = 1.0F;
      this.initialWeight = 0.0F;
      this.isLooped = false;
      this.isReversed = false;
      this.deferredBoneName = null;
      this.deferredBoneAxis = BoneAxis.Y;
      this.useDeferredRotation = false;
   }

   public void onReleased() {
      this.reset();
   }

   protected AnimLayer$StartAnimTrackParameters() {
   }

   public static AnimLayer$StartAnimTrackParameters alloc() {
      return (AnimLayer$StartAnimTrackParameters)s_pool.alloc();
   }
}
