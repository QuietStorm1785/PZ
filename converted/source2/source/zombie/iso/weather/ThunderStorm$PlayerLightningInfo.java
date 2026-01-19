package zombie.iso.weather;

import zombie.GameTime.AnimTimer;
import zombie.iso.weather.ThunderStorm.LightningState;

class ThunderStorm$PlayerLightningInfo {
   public LightningState lightningState;
   public AnimTimer timer;
   public float lightningStrength;
   public float lightningMod;
   public ClimateColorInfo lightningColor;
   public ClimateColorInfo outColor;
   public int x;
   public int y;
   public int distance;

   private ThunderStorm$PlayerLightningInfo(ThunderStorm var1) {
      this.this$0 = var1;
      this.lightningState = LightningState.Idle;
      this.timer = new AnimTimer();
      this.lightningStrength = 1.0F;
      this.lightningMod = 0.0F;
      this.lightningColor = new ClimateColorInfo(1.0F, 1.0F, 1.0F, 1.0F);
      this.outColor = new ClimateColorInfo(1.0F, 1.0F, 1.0F, 1.0F);
      this.x = 0;
      this.y = 0;
      this.distance = 0;
   }
}
