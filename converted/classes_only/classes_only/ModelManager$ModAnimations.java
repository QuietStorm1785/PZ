package zombie.core.skinnedmodel;

import java.util.ArrayList;
import java.util.HashMap;
import zombie.core.skinnedmodel.model.AnimationAsset;

public final class ModelManager$ModAnimations {
   public final String m_modID;
   public final ArrayList<AnimationAsset> m_animationAssetList = new ArrayList<>();
   public final HashMap<String, AnimationAsset> m_animationAssetMap = new HashMap<>();
   public int m_priority;

   public ModelManager$ModAnimations(String var1) {
      this.m_modID = var1;
   }

   public void setPriority(int var1) {
      if (!$assertionsDisabled && var1 < -1) {
         throw new AssertionError();
      } else {
         this.m_priority = var1;
      }
   }

   public boolean isActive() {
      return this.m_priority != -1;
   }
}
