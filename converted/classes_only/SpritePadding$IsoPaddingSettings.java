package zombie.iso.sprite.shapers;

import zombie.iso.sprite.shapers.SpritePadding.IsoPaddingSettings.IsoBorderSetting;
import zombie.iso.sprite.shapers.SpritePaddingSettings.GenericZoomBasedSettingGroup;

public class SpritePadding$IsoPaddingSettings extends GenericZoomBasedSettingGroup {
   public IsoBorderSetting ZoomedIn = new IsoBorderSetting(1.0F, 0.99F);
   public IsoBorderSetting NotZoomed = new IsoBorderSetting(1.0F, 0.99F);
   public IsoBorderSetting ZoomedOut = new IsoBorderSetting(2.0F, 0.01F);

   public IsoBorderSetting getCurrentZoomSetting() {
      return (IsoBorderSetting)getCurrentZoomSetting(this.ZoomedIn, this.NotZoomed, this.ZoomedOut);
   }
}
