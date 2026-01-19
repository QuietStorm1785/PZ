package zombie.core.textures;

import zombie.asset.Asset;
import zombie.asset.AssetManager;
import zombie.asset.AssetPath;
import zombie.asset.AssetManager.AssetParams;
import zombie.core.textures.Texture.TextureAssetParams;

public final class TextureAssetManager extends AssetManager {
   public static final TextureAssetManager instance = new TextureAssetManager();

   protected void startLoading(Asset var1) {
   }

   protected Asset createAsset(AssetPath var1, AssetParams var2) {
      return new Texture(var1, this, (TextureAssetParams)var2);
   }

   protected void destroyAsset(Asset var1) {
   }
}
