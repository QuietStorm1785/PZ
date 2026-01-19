package zombie.core.skinnedmodel.advancedanimation;

import zombie.core.skinnedmodel.animation.AnimationTrack;

class LiveAnimNode$TransitionIn {
   private float m_time;
   private String m_transitionedFrom;
   private boolean m_active;
   private AnimationTrack m_track;
   private AnimTransition m_data;
   private float m_weight;
   private float m_rawWeight;
   private boolean m_blendingIn;
   private boolean m_blendingOut;

   private LiveAnimNode$TransitionIn() {
   }

   private void reset() {
      this.m_time = 0.0F;
      this.m_transitionedFrom = null;
      this.m_active = false;
      this.m_track = null;
      this.m_data = null;
      this.m_weight = 0.0F;
      this.m_rawWeight = 0.0F;
      this.m_blendingIn = false;
      this.m_blendingOut = false;
   }
}
