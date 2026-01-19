package zombie.core.skinnedmodel.model;

import java.util.HashMap;
import zombie.asset.Asset;
import zombie.asset.AssetManager;
import zombie.asset.AssetPath;
import zombie.asset.AssetType;
import zombie.asset.AssetManager.AssetParams;
import zombie.core.skinnedmodel.ModelManager.ModAnimations;
import zombie.core.skinnedmodel.animation.AnimationClip;
import zombie.core.skinnedmodel.model.AnimationAsset.AnimationAssetParams;
import zombie.core.skinnedmodel.model.jassimp.ProcessedAiScene;

public final class AnimationAsset extends Asset {
   public HashMap<String, AnimationClip> AnimationClips;
   public AnimationAssetParams assetParams;
   public SkinningData skinningData;
   public String modelManagerKey;
   public ModAnimations modAnimations;
   public static final AssetType ASSET_TYPE = new AssetType("Animation");

   public AnimationAsset(AssetPath var1, AssetManager var2, AnimationAssetParams var3) {
      super(var1, var2);
      this.assetParams = var3;
   }

   protected void onLoadedX(ProcessedAiScene var1) {
      var1.applyToAnimation(this);
   }

   protected void onLoadedTxt(ModelTxt var1) {
      ModelLoader.instance.applyToAnimation(var1, this);
   }

   public void onBeforeReady() {
      super.onBeforeReady();
      if (this.assetParams != null) {
         this.assetParams.animationsMesh = null;
         this.assetParams = null;
      }
   }

   public void setAssetParams(AssetParams var1) {
      this.assetParams = (AnimationAssetParams)var1;
   }

   public AssetType getType() {
      return ASSET_TYPE;
   }
}
