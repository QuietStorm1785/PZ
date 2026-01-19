package zombie.iso.sprite.shapers;

import javax.xml.bind.annotation.XmlRootElement;
import zombie.iso.sprite.shapers.FloorShaperDeDiamond.Settings;
import zombie.iso.sprite.shapers.SpritePadding.IsoPaddingSettings;

@XmlRootElement(name = "FloorShaperDeDiamondSettings")
public class SpritePaddingSettings$Settings {
   public IsoPaddingSettings IsoPadding = new IsoPaddingSettings();
   public Settings FloorDeDiamond = new Settings();
   public zombie.iso.sprite.shapers.FloorShaperAttachedSprites.Settings AttachedSprites = new zombie.iso.sprite.shapers.FloorShaperAttachedSprites.Settings();
}
