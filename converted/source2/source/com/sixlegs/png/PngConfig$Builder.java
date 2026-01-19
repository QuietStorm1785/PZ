package com.sixlegs.png;

import java.awt.Rectangle;

public final class PngConfig$Builder {
   private static final int[] DEFAULT_SUBSAMPLING = new int[]{1, 1, 0, 0};
   int readLimit = 0;
   float defaultGamma = 0.45455F;
   float displayExponent = 2.2F;
   boolean warningsFatal;
   boolean progressive;
   boolean reduce16 = true;
   boolean gammaCorrect = true;
   Rectangle sourceRegion;
   int[] subsampling = DEFAULT_SUBSAMPLING;
   boolean convertIndexed;

   public PngConfig$Builder() {
   }

   public PngConfig$Builder(PngConfig var1) {
      this.readLimit = var1.readLimit;
      this.defaultGamma = var1.defaultGamma;
      this.displayExponent = var1.displayExponent;
      this.warningsFatal = var1.warningsFatal;
      this.progressive = var1.progressive;
      this.reduce16 = var1.reduce16;
      this.gammaCorrect = var1.gammaCorrect;
      this.subsampling = var1.subsampling;
   }

   public PngConfig build() {
      return new PngConfig(this);
   }

   public PngConfig$Builder reduce16(boolean var1) {
      this.reduce16 = var1;
      return this;
   }

   public PngConfig$Builder defaultGamma(float var1) {
      this.defaultGamma = var1;
      return this;
   }

   public PngConfig$Builder displayExponent(float var1) {
      this.displayExponent = var1;
      return this;
   }

   public PngConfig$Builder gammaCorrect(boolean var1) {
      this.gammaCorrect = var1;
      return this;
   }

   public PngConfig$Builder progressive(boolean var1) {
      this.progressive = var1;
      return this;
   }

   public PngConfig$Builder readLimit(int var1) {
      this.readLimit = var1;
      return this;
   }

   public PngConfig$Builder warningsFatal(boolean var1) {
      this.warningsFatal = var1;
      return this;
   }

   public PngConfig$Builder sourceRegion(Rectangle var1) {
      if (var1 != null) {
         if (var1.x < 0 || var1.y < 0 || var1.width <= 0 || var1.height <= 0) {
            throw new IllegalArgumentException("invalid source region: " + var1);
         }

         this.sourceRegion = new Rectangle(var1);
      } else {
         this.sourceRegion = null;
      }

      return this;
   }

   public PngConfig$Builder sourceSubsampling(int var1, int var2, int var3, int var4) {
      if (var1 > 0 && var2 > 0 && var3 >= 0 && var3 < var1 && var4 >= 0 && var4 < var2) {
         this.subsampling = new int[]{var1, var2, var3, var4};
         return this;
      } else {
         throw new IllegalArgumentException("invalid subsampling values");
      }
   }

   public PngConfig$Builder convertIndexed(boolean var1) {
      this.convertIndexed = var1;
      return this;
   }
}
