package zombie.core.raknet;

import java.nio.ByteBuffer;

public class UdpConnection$MPClientStatistic {
   public byte enable;
   public int diff;
   public float pingAVG;
   public int zombiesCount;
   public int zombiesLocalOwnership;
   public float zombiesDesyncAVG;
   public float zombiesDesyncMax;
   public int zombiesTeleports;
   public int remotePlayersCount;
   public float remotePlayersDesyncAVG;
   public float remotePlayersDesyncMax;
   public int remotePlayersTeleports;
   public float FPS;
   public float FPSMin;
   public float FPSAvg;
   public float FPSMax;
   public short[] FPSHistogramm;

   public UdpConnection$MPClientStatistic(UdpConnection var1) {
      this.this$0 = var1;
      this.enable = 0;
      this.diff = 0;
      this.pingAVG = 0.0F;
      this.zombiesCount = 0;
      this.zombiesLocalOwnership = 0;
      this.zombiesDesyncAVG = 0.0F;
      this.zombiesDesyncMax = 0.0F;
      this.zombiesTeleports = 0;
      this.remotePlayersCount = 0;
      this.remotePlayersDesyncAVG = 0.0F;
      this.remotePlayersDesyncMax = 0.0F;
      this.remotePlayersTeleports = 0;
      this.FPS = 0.0F;
      this.FPSMin = 0.0F;
      this.FPSAvg = 0.0F;
      this.FPSMax = 0.0F;
      this.FPSHistogramm = new short[32];
   }

   public void parse(ByteBuffer var1) {
      long var2 = var1.getLong();
      long var4 = System.currentTimeMillis();
      this.diff = (int)(var4 - var2);
      this.pingAVG = this.pingAVG + (this.diff * 0.5F - this.pingAVG) * 0.1F;
      this.zombiesCount = var1.getInt();
      this.zombiesLocalOwnership = var1.getInt();
      this.zombiesDesyncAVG = var1.getFloat();
      this.zombiesDesyncMax = var1.getFloat();
      this.zombiesTeleports = var1.getInt();
      this.remotePlayersCount = var1.getInt();
      this.remotePlayersDesyncAVG = var1.getFloat();
      this.remotePlayersDesyncMax = var1.getFloat();
      this.remotePlayersTeleports = var1.getInt();
      this.FPS = var1.getFloat();
      this.FPSMin = var1.getFloat();
      this.FPSAvg = var1.getFloat();
      this.FPSMax = var1.getFloat();

      for (int var6 = 0; var6 < 32; var6++) {
         this.FPSHistogramm[var6] = var1.getShort();
      }
   }
}
