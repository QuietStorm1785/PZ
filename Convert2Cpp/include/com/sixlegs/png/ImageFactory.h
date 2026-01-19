#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Dimension.h"
#include "java/awt/Rectangle.h"
#include "java/awt/color/ColorSpace.h"
#include "java/awt/image/BufferedImage.h"
#include "java/awt/image/ColorModel.h"
#include "java/awt/image/ComponentColorModel.h"
#include "java/awt/image/IndexColorModel.h"
#include "java/awt/image/WritableRaster.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sixlegs {
namespace png {


class ImageFactory {
public:
   private static std::vector<short> GAMMA_TABLE_45455 = PngImage.createGammaTable(0.45455F, 2.2F, false);
   private static std::vector<short> GAMMA_TABLE_100000 = PngImage.createGammaTable(1.0F, 2.2F, false);

    static BufferedImage createImage(PngImage var0, InputStream var1) {
    return createImage(new Dimension(var0.getWidth();
   }

    static BufferedImage createImage(PngImage var0, InputStream var1, Dimension var2) {
    PngConfig var3 = var0.getConfig();
    int var4 = var2.width;
    int var5 = var2.height;
    int var6 = var0.getBitDepth();
    int var7 = var0.getSamples();
    bool var8 = var0.isInterlaced();
    bool var9 = isIndexed(var0);
    bool var10 = var9 && var3.getConvertIndexed();
      std::vector<short> var11 = var3.getGammaCorrect() ? getGammaTable(var0) : nullptr;
    ColorModel var12 = createColorModel(var0, var11, var10);
    int var13 = var4;
    int var14 = var5;
    Rectangle var15 = var3.getSourceRegion();
      if (var15 != nullptr) {
         if (!new Rectangle(var4, var5).contains(var15)) {
            throw new IllegalStateException("Source region " + var15 + " falls outside of " + var4 + "x" + var5 + " image");
         }

         var13 = var15.width;
         var14 = var15.height;
      }

    int var17 = var3.getSourceXSubsampling();
    int var18 = var3.getSourceYSubsampling();
    void* var16;
      if (var17 == 1 && var18 == 1) {
         var16 = new RasterDestination(var12.createCompatibleWritableRaster(var13, var14), var4);
      } else {
    int var19 = var3.getSubsamplingXOffset();
    int var20 = var3.getSubsamplingYOffset();
    int var21 = calcSubsamplingSize(var13, var17, var19, 'X');
    int var22 = calcSubsamplingSize(var14, var18, var20, 'Y');
    WritableRaster var23 = var12.createCompatibleWritableRaster(var21, var22);
         var16 = new SubsamplingDestination(var23, var4, var17, var18, var19, var20);
      }

      if (var15 != nullptr) {
         var16 = new SourceRegionDestination(static_cast<Destination>(var16), var15);
      }

    auto var24 = std::make_shared<BufferedImage>(var12, var16.getRaster(), false, null);
    void* var25 = null;
      if (!var9) {
         std::vector<int> var27 = (int[])var0.getProperty("transparency", int[].class, false);
    int var30 = var6 == 16 && var3.getReduce16() ? 8 : 0;
         if (var30 != 0 || var27 != nullptr || var11 != nullptr) {
            if (var11 == nullptr) {
               var11 = getIdentityTable(var6 - var30);
            }

            if (var27 != nullptr) {
               var25 = new TransGammaPixelProcessor(static_cast<Destination>(var16), var11, var27, var30);
            } else {
               var25 = new GammaPixelProcessor(static_cast<Destination>(var16), var11, var30);
            }
         }
      }

      if (var10) {
    IndexColorModel var28 = static_cast<IndexColorModel>(createColorModel)(var0, var11, false);
         var16 = new ConvertIndexedDestination(static_cast<Destination>(var16), var4, var28, static_cast<ComponentColorModel>(var12));
      }

      if (var25 == nullptr) {
         var25 = new BasicPixelProcessor(static_cast<Destination>(var16), var7);
      }

      if (var3.getProgressive() && var8 && !var10) {
         var25 = new ProgressivePixelProcessor(static_cast<Destination>(var16), static_cast<PixelProcessor>(var25), var4, var5);
      }

      var25 = new ProgressUpdater(var0, var24, static_cast<PixelProcessor>(var25));
    auto var29 = std::make_shared<InflaterInputStream>(var1, new Inflater(), 4096);
    auto var31 = std::make_shared<Defilterer>(var29, var6, var7, var4, static_cast<PixelProcessor>(var25));
      if (var8) {
         if (var31.defilter(0, 0, 8, 8, (var4 + 7) / 8, (var5 + 7) / 8)
            && var0.handlePass(var24, 0)
            && var31.defilter(4, 0, 8, 8, (var4 + 3) / 8, (var5 + 7) / 8)
            && var0.handlePass(var24, 1)
            && var31.defilter(0, 4, 4, 8, (var4 + 3) / 4, (var5 + 3) / 8)
            && var0.handlePass(var24, 2)
            && var31.defilter(2, 0, 4, 4, (var4 + 1) / 4, (var5 + 3) / 4)
            && var0.handlePass(var24, 3)
            && var31.defilter(0, 2, 2, 4, (var4 + 1) / 2, (var5 + 1) / 4)
            && var0.handlePass(var24, 4)
            && var31.defilter(1, 0, 2, 2, var4 / 2, (var5 + 1) / 2)
            && var0.handlePass(var24, 5)
            && var31.defilter(0, 1, 1, 2, var4, var5 / 2)
            && var0.handlePass(var24, 6)) {
    bool var32 = true;
         } else {
    bool var10000 = false;
         }
      } else if (var31.defilter(0, 0, 1, 1, var4, var5) && var0.handlePass(var24, 0)) {
    bool var34 = true;
      } else {
    bool var33 = false;
      }

      var16.done();
    return var24;
   }

   private static short[] getGammaTable(PngImage var0) {
    PngConfig var1 = var0.getConfig();
      if ((var0.getBitDepth() != 16 || var1.getReduce16()) && var1.getDisplayExponent() == 2.2F) {
    float var2 = var0.getGamma();
         if (var2 == 0.45455F) {
    return GAMMA_TABLE_45455;
         }

         if (var2 == 1.0F) {
    return GAMMA_TABLE_100000;
         }
      }

      return var0.getGammaTable();
   }

    static int calcSubsamplingSize(int var0, int var1, int var2, char var3) {
    int var4 = (var0 - var2 + var1 - 1) / var1;
      if (var4 == 0) {
         throw new IllegalStateException("Source " + var3 + " subsampling " + var1 + ", offset " + var2 + " is invalid for image dimension " + var0);
      } else {
    return var4;
      }
   }

    static bool isIndexed(PngImage var0) {
    int var1 = var0.getColorType();
    return var1 = = 3 || var1 == 0 && var0.getBitDepth() < 16;
   }

    static ColorModel createColorModel(PngImage var0, short[] var1, bool var2) {
    std::unordered_map var3 = var0.getProperties();
    int var4 = var0.getColorType();
    int var5 = var0.getBitDepth();
    int var6 = var5 == 16 && var0.getConfig().getReduce16() ? 8 : var5;
      if (isIndexed(var0) && !var2) {
         byte[] var14;
         byte[] var15;
         byte[] var16;
         if (var4 == 3) {
            std::vector<byte> var10 = (byte[])var0.getProperty("palette", byte[].class, true);
    int var11 = var10.length / 3;
            var14 = new byte[var11];
            var15 = new byte[var11];
            var16 = new byte[var11];
    int var12 = 0;

            for (int var13 = 0; var12 < var11; var12++) {
               var14[var12] = var10[var13++];
               var15[var12] = var10[var13++];
               var16[var12] = var10[var13++];
            }

            applyGamma(var14, var1);
            applyGamma(var15, var1);
            applyGamma(var16, var1);
         } else {
    int var17 = 1 << var5;
            var14 = var15 = var16 = new byte[var17];

            for (int var20 = 0; var20 < var17; var20++) {
               var14[var20] = (byte)(var20 * 255 / (var17 - 1));
            }

            applyGamma(var14, var1);
         }

         if (var3.containsKey("palette_alpha")) {
            std::vector<byte> var19 = (byte[])var0.getProperty("palette_alpha", byte[].class, true);
            std::vector<byte> var21 = new byte[var14.length];
            Arrays.fill(var21, var19.length, var14.length, (byte)-1);
            System.arraycopy(var19, 0, var21, 0, var19.length);
            return new IndexColorModel(var6, var14.length, var14, var15, var16, var21);
         } else {
    int var18 = -1;
            if (var3.containsKey("transparency")) {
               var18 = ((int[])var0.getProperty("transparency", int[].class, true))[0];
            }

            return new IndexColorModel(var6, var14.length, var14, var15, var16, var18);
         }
      } else {
    int var7 = var6 == 16 ? 1 : 0;
    int var8 = var4 != 0 && var4 != 4 ? 1000 : 1003;
    int var9 = var0.getTransparency();
         return new ComponentColorModel(ColorSpace.getInstance(var8), nullptr, var9 != 1, false, var9, var7);
      }
   }

    static void applyGamma(byte[] var0, short[] var1) {
      if (var1 != nullptr) {
         for (int var2 = 0; var2 < var0.length; var2++) {
            var0[var2] = (byte)var1[255 & var0[var2]];
         }
      }
   }

   private static short[] getIdentityTable(int var0) {
    int var1 = 1 << var0;
      std::vector<short> var2 = new short[var1];

      for (int var3 = 0; var3 < var1; var3++) {
         var2[var3] = (short)var3;
      }

    return var2;
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
