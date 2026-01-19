package zombie.ui;

import zombie.core.textures.Texture;

public class RadialMenu$Slice {
   public String text;
   public Texture texture;

   protected RadialMenu$Slice() {
   }

   boolean isEmpty() {
      return this.text == null && this.texture == null;
   }
}
