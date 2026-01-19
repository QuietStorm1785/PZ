package zombie.iso.sprite.shapers;

import zombie.core.Core;

public abstract class SpritePaddingSettings$GenericZoomBasedSettingGroup {
   public abstract <ZoomBasedSetting> ZoomBasedSetting getCurrentZoomSetting();

   public static <ZoomBasedSetting> ZoomBasedSetting getCurrentZoomSetting(ZoomBasedSetting var0, ZoomBasedSetting var1, ZoomBasedSetting var2) {
      float var3 = Core.getInstance().getCurrentPlayerZoom();
      if (var3 < 1.0F) {
         return (ZoomBasedSetting)var0;
      } else {
         return (ZoomBasedSetting)(var3 == 1.0F ? var1 : var2);
      }
   }
}
