package zombie.worldMap.styles;

import zombie.core.textures.Texture;
import zombie.worldMap.styles.WorldMapStyleLayer.Stop;

public class WorldMapStyleLayer$TextureStop extends Stop {
   public String texturePath;
   public Texture texture;

   public WorldMapStyleLayer$TextureStop(float var1, String var2) {
      super(var1);
      this.texturePath = var2;
      this.texture = Texture.getTexture(var2);
   }
}
