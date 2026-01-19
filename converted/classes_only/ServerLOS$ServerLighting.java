package zombie.network;

import zombie.core.textures.ColorInfo;
import zombie.iso.IsoGridSquare.ILighting;
import zombie.iso.IsoGridSquare.ResultLight;

public final class ServerLOS$ServerLighting implements ILighting {
   private static final byte LOS_SEEN = 1;
   private static final byte LOS_COULD_SEE = 2;
   private static final byte LOS_CAN_SEE = 4;
   private static ColorInfo lightInfo = new ColorInfo();
   private byte los;

   public int lightverts(int var1) {
      return 0;
   }

   public float lampostTotalR() {
      return 0.0F;
   }

   public float lampostTotalG() {
      return 0.0F;
   }

   public float lampostTotalB() {
      return 0.0F;
   }

   public boolean bSeen() {
      return (this.los & 1) != 0;
   }

   public boolean bCanSee() {
      return (this.los & 4) != 0;
   }

   public boolean bCouldSee() {
      return (this.los & 2) != 0;
   }

   public float darkMulti() {
      return 0.0F;
   }

   public float targetDarkMulti() {
      return 0.0F;
   }

   public ColorInfo lightInfo() {
      lightInfo.r = 1.0F;
      lightInfo.g = 1.0F;
      lightInfo.b = 1.0F;
      return lightInfo;
   }

   public void lightverts(int var1, int var2) {
   }

   public void lampostTotalR(float var1) {
   }

   public void lampostTotalG(float var1) {
   }

   public void lampostTotalB(float var1) {
   }

   public void bSeen(boolean var1) {
      if (var1) {
         this.los = (byte)(this.los | 1);
      } else {
         this.los &= -2;
      }
   }

   public void bCanSee(boolean var1) {
      if (var1) {
         this.los = (byte)(this.los | 4);
      } else {
         this.los &= -5;
      }
   }

   public void bCouldSee(boolean var1) {
      if (var1) {
         this.los = (byte)(this.los | 2);
      } else {
         this.los &= -3;
      }
   }

   public void darkMulti(float var1) {
   }

   public void targetDarkMulti(float var1) {
   }

   public int resultLightCount() {
      return 0;
   }

   public ResultLight getResultLight(int var1) {
      return null;
   }

   public void reset() {
      this.los = 0;
   }
}
