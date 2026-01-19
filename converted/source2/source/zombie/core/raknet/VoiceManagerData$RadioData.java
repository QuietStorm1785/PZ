package zombie.core.raknet;

import zombie.radio.devices.DeviceData;

public class VoiceManagerData$RadioData {
   DeviceData deviceData;
   public int freq;
   public float distance;
   public short x;
   public short y;
   float lastReceiveDistance;

   public VoiceManagerData$RadioData(float var1, float var2, float var3) {
      this(null, 0, var1, var2, var3);
   }

   public VoiceManagerData$RadioData(int var1, float var2, float var3, float var4) {
      this(null, var1, var2, var3, var4);
   }

   public VoiceManagerData$RadioData(DeviceData var1, float var2, float var3) {
      this(var1, var1.getChannel(), var1.getMicIsMuted() ? 0.0F : var1.getTransmitRange(), var2, var3);
   }

   private VoiceManagerData$RadioData(DeviceData var1, int var2, float var3, float var4, float var5) {
      this.deviceData = var1;
      this.freq = var2;
      this.distance = var3;
      this.x = (short)var4;
      this.y = (short)var5;
   }

   public boolean isTransmissionAvailable() {
      return this.freq != 0
         && this.deviceData != null
         && this.deviceData.getIsTurnedOn()
         && this.deviceData.getIsTwoWay()
         && !this.deviceData.isNoTransmit()
         && !this.deviceData.getMicIsMuted();
   }

   public boolean isReceivingAvailable(int var1) {
      return this.freq != 0
         && this.deviceData != null
         && this.deviceData.getIsTurnedOn()
         && this.deviceData.getChannel() == var1
         && this.deviceData.getDeviceVolume() != 0.0F
         && !this.deviceData.isPlayingMedia();
   }

   public DeviceData getDeviceData() {
      return this.deviceData;
   }
}
