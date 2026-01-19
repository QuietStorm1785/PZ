package zombie.radio;

import zombie.radio.devices.DeviceData;

final class ZomboidRadio$FreqListEntry {
   public boolean isInvItem = false;
   public DeviceData deviceData;
   public int sourceX = 0;
   public int sourceY = 0;

   public ZomboidRadio$FreqListEntry(boolean var1, DeviceData var2, int var3, int var4) {
      this.isInvItem = var1;
      this.deviceData = var2;
      this.sourceX = var3;
      this.sourceY = var4;
   }
}
