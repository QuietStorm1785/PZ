package zombie.iso;

import zombie.iso.SearchMode.PlayerSearchMode;
import zombie.iso.SearchMode.SearchModeFloat;

public class SearchMode {
   private static SearchMode instance;
   private float fadeTime = 1.0F;
   private PlayerSearchMode[] plrModes = new PlayerSearchMode[4];

   public static SearchMode getInstance() {
      if (instance == null) {
         instance = new SearchMode();
      }

      return instance;
   }

   private SearchMode() {
      for (int var1 = 0; var1 < this.plrModes.length; var1++) {
         this.plrModes[var1] = new PlayerSearchMode(var1, this);
         this.plrModes[var1].blur.setTargets(1.0F, 1.0F);
         this.plrModes[var1].desat.setTargets(0.85F, 0.85F);
         this.plrModes[var1].radius.setTargets(4.0F, 4.0F);
         this.plrModes[var1].darkness.setTargets(0.0F, 0.0F);
         this.plrModes[var1].gradientWidth.setTargets(4.0F, 4.0F);
      }
   }

   public PlayerSearchMode getSearchModeForPlayer(int var1) {
      return this.plrModes[var1];
   }

   public float getFadeTime() {
      return this.fadeTime;
   }

   public void setFadeTime(float var1) {
      this.fadeTime = var1;
   }

   public boolean isOverride(int var1) {
      return this.plrModes[var1].override;
   }

   public void setOverride(int var1, boolean var2) {
      this.plrModes[var1].override = var2;
   }

   public SearchModeFloat getRadius(int var1) {
      return this.plrModes[var1].radius;
   }

   public SearchModeFloat getGradientWidth(int var1) {
      return this.plrModes[var1].gradientWidth;
   }

   public SearchModeFloat getBlur(int var1) {
      return this.plrModes[var1].blur;
   }

   public SearchModeFloat getDesat(int var1) {
      return this.plrModes[var1].desat;
   }

   public SearchModeFloat getDarkness(int var1) {
      return this.plrModes[var1].darkness;
   }

   public boolean isEnabled(int var1) {
      return this.plrModes[var1].enabled;
   }

   public void setEnabled(int var1, boolean var2) {
      PlayerSearchMode var3 = this.plrModes[var1];
      if (var2 && !var3.enabled) {
         var3.enabled = true;
         this.FadeIn(var1);
      } else if (!var2 && var3.enabled) {
         var3.enabled = false;
         this.FadeOut(var1);
      }
   }

   private void FadeIn(int var1) {
      PlayerSearchMode var2 = this.plrModes[var1];
      var2.timer = Math.max(var2.timer, 0.0F);
      var2.doFadeIn = true;
      var2.doFadeOut = false;
   }

   private void FadeOut(int var1) {
      PlayerSearchMode var2 = this.plrModes[var1];
      var2.timer = Math.min(var2.timer, this.fadeTime);
      var2.doFadeIn = false;
      var2.doFadeOut = true;
   }

   public void update() {
      for (int var1 = 0; var1 < this.plrModes.length; var1++) {
         PlayerSearchMode var2 = this.plrModes[var1];
         var2.update();
      }
   }

   public static void reset() {
      instance = null;
   }
}
