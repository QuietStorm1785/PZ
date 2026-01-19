package zombie.gameStates;

import zombie.core.textures.Texture;

public class MainScreenState$Credit {
   public int disappearDelay;
   public Texture name;
   public float nameAlpha;
   public float nameAppearDelay;
   public float nameTargetAlpha;
   public Texture title;
   public float titleAlpha;
   public float titleTargetAlpha;

   public MainScreenState$Credit(MainScreenState var1, Texture var2, Texture var3) {
      this.this$0 = var1;
      this.disappearDelay = 200;
      this.nameAppearDelay = 40.0F;
      this.titleTargetAlpha = 1.0F;
      this.titleAlpha = 0.0F;
      this.nameTargetAlpha = 0.0F;
      this.nameAlpha = 0.0F;
      this.title = var2;
      this.name = var3;
   }
}
