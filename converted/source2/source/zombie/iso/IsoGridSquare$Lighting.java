package zombie.iso;

import zombie.core.textures.ColorInfo;
import zombie.iso.IsoGridSquare.ILighting;
import zombie.iso.IsoGridSquare.ResultLight;

public final class IsoGridSquare$Lighting implements ILighting {
   private final int[] lightverts = new int[8];
   private float lampostTotalR = 0.0F;
   private float lampostTotalG = 0.0F;
   private float lampostTotalB = 0.0F;
   private boolean bSeen;
   private boolean bCanSee;
   private boolean bCouldSee;
   private float darkMulti;
   private float targetDarkMulti;
   private final ColorInfo lightInfo = new ColorInfo();

   public int lightverts(int var1) {
      return this.lightverts[var1];
   }

   public float lampostTotalR() {
      return this.lampostTotalR;
   }

   public float lampostTotalG() {
      return this.lampostTotalG;
   }

   public float lampostTotalB() {
      return this.lampostTotalB;
   }

   public boolean bSeen() {
      return this.bSeen;
   }

   public boolean bCanSee() {
      return this.bCanSee;
   }

   public boolean bCouldSee() {
      return this.bCouldSee;
   }

   public float darkMulti() {
      return this.darkMulti;
   }

   public float targetDarkMulti() {
      return this.targetDarkMulti;
   }

   public ColorInfo lightInfo() {
      return this.lightInfo;
   }

   public void lightverts(int var1, int var2) {
      this.lightverts[var1] = var2;
   }

   public void lampostTotalR(float var1) {
      this.lampostTotalR = var1;
   }

   public void lampostTotalG(float var1) {
      this.lampostTotalG = var1;
   }

   public void lampostTotalB(float var1) {
      this.lampostTotalB = var1;
   }

   public void bSeen(boolean var1) {
      this.bSeen = var1;
   }

   public void bCanSee(boolean var1) {
      this.bCanSee = var1;
   }

   public void bCouldSee(boolean var1) {
      this.bCouldSee = var1;
   }

   public void darkMulti(float var1) {
      this.darkMulti = var1;
   }

   public void targetDarkMulti(float var1) {
      this.targetDarkMulti = var1;
   }

   public int resultLightCount() {
      return 0;
   }

   public ResultLight getResultLight(int var1) {
      return null;
   }

   public void reset() {
      this.lampostTotalR = 0.0F;
      this.lampostTotalG = 0.0F;
      this.lampostTotalB = 0.0F;
      this.bSeen = false;
      this.bCouldSee = false;
      this.bCanSee = false;
      this.targetDarkMulti = 0.0F;
      this.darkMulti = 0.0F;
      this.lightInfo.r = 0.0F;
      this.lightInfo.g = 0.0F;
      this.lightInfo.b = 0.0F;
      this.lightInfo.a = 1.0F;
   }
}
