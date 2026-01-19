package zombie.iso;

import zombie.GameTime;
import zombie.characters.IsoPlayer;
import zombie.core.math.PZMath;
import zombie.iso.SearchMode.SearchModeFloat;

public class SearchMode$PlayerSearchMode {
   private final int plrIndex;
   private final SearchMode parent;
   private boolean override = false;
   private boolean enabled = false;
   private final SearchModeFloat radius = new SearchModeFloat(0.0F, 50.0F, 1.0F);
   private final SearchModeFloat gradientWidth = new SearchModeFloat(0.0F, 20.0F, 1.0F);
   private final SearchModeFloat blur = new SearchModeFloat(0.0F, 1.0F, 0.01F);
   private final SearchModeFloat desat = new SearchModeFloat(0.0F, 1.0F, 0.01F);
   private final SearchModeFloat darkness = new SearchModeFloat(0.0F, 1.0F, 0.01F);
   private float timer;
   private boolean doFadeOut;
   private boolean doFadeIn;

   public SearchMode$PlayerSearchMode(int var1, SearchMode var2) {
      this.plrIndex = var1;
      this.parent = var2;
   }

   public boolean isShaderEnabled() {
      return this.enabled || this.doFadeIn || this.doFadeOut;
   }

   private boolean isPlayerExterior() {
      IsoPlayer var1 = IsoPlayer.players[this.plrIndex];
      return var1 != null && var1.getCurrentSquare() != null && !var1.getCurrentSquare().isInARoom();
   }

   public float getShaderBlur() {
      return this.isPlayerExterior() ? this.blur.getExterior() : this.blur.getInterior();
   }

   public float getShaderDesat() {
      return this.isPlayerExterior() ? this.desat.getExterior() : this.desat.getInterior();
   }

   public float getShaderRadius() {
      return this.isPlayerExterior() ? this.radius.getExterior() : this.radius.getInterior();
   }

   public float getShaderGradientWidth() {
      return this.isPlayerExterior() ? this.gradientWidth.getExterior() : this.gradientWidth.getInterior();
   }

   public float getShaderDarkness() {
      return this.isPlayerExterior() ? this.darkness.getExterior() : this.darkness.getInterior();
   }

   public SearchModeFloat getBlur() {
      return this.blur;
   }

   public SearchModeFloat getDesat() {
      return this.desat;
   }

   public SearchModeFloat getRadius() {
      return this.radius;
   }

   public SearchModeFloat getGradientWidth() {
      return this.gradientWidth;
   }

   public SearchModeFloat getDarkness() {
      return this.darkness;
   }

   private void update() {
      if (!this.override) {
         if (this.doFadeIn) {
            this.timer = this.timer + GameTime.getInstance().getTimeDelta();
            this.timer = PZMath.clamp(this.timer, 0.0F, this.parent.fadeTime);
            float var2 = PZMath.clamp(this.timer / this.parent.fadeTime, 0.0F, 1.0F);
            this.blur.update(var2);
            this.desat.update(var2);
            this.radius.update(var2);
            this.darkness.update(var2);
            this.gradientWidth.equalise();
            if (this.timer >= this.parent.fadeTime) {
               this.doFadeIn = false;
            }
         } else if (this.doFadeOut) {
            this.timer = this.timer - GameTime.getInstance().getTimeDelta();
            this.timer = PZMath.clamp(this.timer, 0.0F, this.parent.fadeTime);
            float var1 = PZMath.clamp(this.timer / this.parent.fadeTime, 0.0F, 1.0F);
            this.blur.update(var1);
            this.desat.update(var1);
            this.radius.update(var1);
            this.darkness.update(var1);
            this.gradientWidth.equalise();
            if (this.timer <= 0.0F) {
               this.doFadeOut = false;
            }
         } else {
            if (this.enabled) {
               this.blur.equalise();
               this.desat.equalise();
               this.radius.equalise();
               this.darkness.equalise();
               this.gradientWidth.equalise();
            } else {
               this.blur.reset();
               this.desat.reset();
               this.radius.reset();
               this.darkness.reset();
               this.gradientWidth.equalise();
            }
         }
      }
   }
}
