package zombie.iso.sprite.shapers;

import javax.xml.bind.annotation.XmlType;
import zombie.iso.sprite.shapers.FloorShaperDeDiamond.Settings.BorderSetting;
import zombie.iso.sprite.shapers.SpritePaddingSettings.GenericZoomBasedSettingGroup;

@XmlType(name = "FloorShaperDeDiamondSettings")
public class FloorShaperDeDiamond$Settings extends GenericZoomBasedSettingGroup {
   public BorderSetting ZoomedIn = new BorderSetting(2.0F, 1.0F, 2.0F, 0.01F);
   public BorderSetting NotZoomed = new BorderSetting(2.0F, 1.0F, 2.0F, 0.01F);
   public BorderSetting ZoomedOut = new BorderSetting(2.0F, 0.0F, 2.5F, 0.0F);

   public BorderSetting getCurrentZoomSetting() {
      return (BorderSetting)getCurrentZoomSetting(this.ZoomedIn, this.NotZoomed, this.ZoomedOut);
   }
}
