package zombie.iso.sprite.shapers;

import javax.xml.bind.annotation.XmlType;
import zombie.iso.sprite.shapers.FloorShaperAttachedSprites.Settings.ASBorderSetting;
import zombie.iso.sprite.shapers.SpritePaddingSettings.GenericZoomBasedSettingGroup;

@XmlType(name = "FloorShaperAttachedSpritesSettings")
public class FloorShaperAttachedSprites$Settings extends GenericZoomBasedSettingGroup {
   public ASBorderSetting ZoomedIn = new ASBorderSetting(2.0F, 1.0F, 3.0F, 0.01F);
   public ASBorderSetting NotZoomed = new ASBorderSetting(2.0F, 1.0F, 3.0F, 0.01F);
   public ASBorderSetting ZoomedOut = new ASBorderSetting(2.0F, 0.0F, 2.5F, 0.0F);

   public ASBorderSetting getCurrentZoomSetting() {
      return (ASBorderSetting)getCurrentZoomSetting(this.ZoomedIn, this.NotZoomed, this.ZoomedOut);
   }
}
