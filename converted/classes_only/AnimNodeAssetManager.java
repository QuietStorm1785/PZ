package zombie.core.skinnedmodel.advancedanimation;

import zombie.asset.Asset;
import zombie.asset.AssetManager;
import zombie.asset.AssetPath;
import zombie.asset.Asset.State;
import zombie.asset.AssetManager.AssetParams;

public class AnimNodeAssetManager extends AssetManager {
   public static final AnimNodeAssetManager instance = new AnimNodeAssetManager();

   protected void startLoading(Asset var1) {
      AnimNodeAsset var2 = (AnimNodeAsset)var1;
      var2.m_animNode = AnimNode.Parse(var1.getPath().getPath());
      if (var2.m_animNode == null) {
         this.onLoadingFailed(var1);
      } else {
         this.onLoadingSucceeded(var1);
      }
   }

   public void onStateChanged(State var1, State var2, Asset var3) {
      super.onStateChanged(var1, var2, var3);
      if (var2 == State.READY) {
      }
   }

   protected Asset createAsset(AssetPath var1, AssetParams var2) {
      return new AnimNodeAsset(var1, this);
   }

   protected void destroyAsset(Asset var1) {
   }
}
