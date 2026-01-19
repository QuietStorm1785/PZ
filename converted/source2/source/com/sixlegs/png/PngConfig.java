package com.sixlegs.png;

import com.sixlegs.png.PngConfig.Builder;
import java.awt.Rectangle;

public final class PngConfig {
   public static final int READ_ALL = 0;
   public static final int READ_HEADER = 1;
   public static final int READ_UNTIL_DATA = 2;
   public static final int READ_EXCEPT_DATA = 3;
   public static final int READ_EXCEPT_METADATA = 4;
   final int readLimit;
   final float defaultGamma;
   final float displayExponent;
   final boolean warningsFatal;
   final boolean progressive;
   final boolean reduce16;
   final boolean gammaCorrect;
   final Rectangle sourceRegion;
   final int[] subsampling;
   final boolean convertIndexed;

   PngConfig(Builder var1) {
      this.readLimit = var1.readLimit;
      this.defaultGamma = var1.defaultGamma;
      this.displayExponent = var1.displayExponent;
      this.warningsFatal = var1.warningsFatal;
      this.progressive = var1.progressive;
      this.reduce16 = var1.reduce16;
      this.gammaCorrect = var1.gammaCorrect;
      this.sourceRegion = var1.sourceRegion;
      this.subsampling = var1.subsampling;
      this.convertIndexed = var1.convertIndexed;
      boolean var2 = this.getSourceXSubsampling() != 1 || this.getSourceYSubsampling() != 1;
      if (this.progressive && (var2 || this.getSourceRegion() != null)) {
         throw new IllegalStateException("Progressive rendering cannot be used with source regions or subsampling");
      }
   }

   public boolean getConvertIndexed() {
      return this.convertIndexed;
   }

   public boolean getReduce16() {
      return this.reduce16;
   }

   public float getDefaultGamma() {
      return this.defaultGamma;
   }

   public boolean getGammaCorrect() {
      return this.gammaCorrect;
   }

   public boolean getProgressive() {
      return this.progressive;
   }

   public float getDisplayExponent() {
      return this.displayExponent;
   }

   public int getReadLimit() {
      return this.readLimit;
   }

   public boolean getWarningsFatal() {
      return this.warningsFatal;
   }

   public Rectangle getSourceRegion() {
      return this.sourceRegion != null ? new Rectangle(this.sourceRegion) : null;
   }

   public int getSourceXSubsampling() {
      return this.subsampling[0];
   }

   public int getSourceYSubsampling() {
      return this.subsampling[1];
   }

   public int getSubsamplingXOffset() {
      return this.subsampling[2];
   }

   public int getSubsamplingYOffset() {
      return this.subsampling[3];
   }
}
