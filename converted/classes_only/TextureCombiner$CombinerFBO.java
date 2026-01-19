package zombie.core.textures;

import java.util.ArrayDeque;

final class TextureCombiner$CombinerFBO {
   TextureFBO fbo;
   final ArrayDeque<Texture> textures = new ArrayDeque<>();

   private TextureCombiner$CombinerFBO() {
   }
}
