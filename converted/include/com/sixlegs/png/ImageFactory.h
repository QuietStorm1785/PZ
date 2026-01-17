#pragma once
#include "java/awt/Dimension.h"
#include "java/awt/Rectangle.h"
#include "java/awt/color/ColorSpace.h"
#include "java/awt/image/BufferedImage.h"
#include "java/awt/image/ColorModel.h"
#include "java/awt/image/ComponentColorModel.h"
#include "java/awt/image/IndexColorModel.h"
#include "java/awt/image/WritableRaster.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ImageFactory {
public:
private
  static short[] GAMMA_TABLE_45455 =
      PngImage.createGammaTable(0.45455F, 2.2F, false);
private
  static short[] GAMMA_TABLE_100000 =
      PngImage.createGammaTable(1.0F, 2.2F, false);

  static BufferedImage createImage(PngImage pngImage, InputStream inputStream) {
    return createImage(new Dimension(pngImage.getWidth();
  }

  static BufferedImage createImage(PngImage pngImage, InputStream inputStream,
                                   Dimension dimension) {
    PngConfig pngConfig = pngImage.getConfig();
    int int0 = dimension.width;
    int int1 = dimension.height;
    int int2 = pngImage.getBitDepth();
    int int3 = pngImage.getSamples();
    bool boolean0 = pngImage.isInterlaced();
    bool boolean1 = isIndexed(pngImage);
    bool boolean2 = boolean1 && pngConfig.getConvertIndexed();
    short[] shorts =
        pngConfig.getGammaCorrect() ? getGammaTable(pngImage) : nullptr;
    ColorModel colorModel = createColorModel(pngImage, shorts, boolean2);
    int int4 = int0;
    int int5 = int1;
    Rectangle rectangle = pngConfig.getSourceRegion();
    if (rectangle != nullptr) {
      if (!new Rectangle(int0, int1).contains(rectangle)) {
        throw new IllegalStateException("Source region " + rectangle +
                                        " falls outside of " + int0 + "x" +
                                        int1 + " image");
      }

      int4 = rectangle.width;
      int5 = rectangle.height;
    }

    int int6 = pngConfig.getSourceXSubsampling();
    int int7 = pngConfig.getSourceYSubsampling();
    void *object0;
    if (int6 == 1 && int7 == 1) {
      object0 = new RasterDestination(
          colorModel.createCompatibleWritableRaster(int4, int5), int0);
    } else {
      int int8 = pngConfig.getSubsamplingXOffset();
      int int9 = pngConfig.getSubsamplingYOffset();
      int int10 = calcSubsamplingSize(int4, int6, int8, 'X');
      int int11 = calcSubsamplingSize(int5, int7, int9, 'Y');
      WritableRaster writableRaster =
          colorModel.createCompatibleWritableRaster(int10, int11);
      object0 = new SubsamplingDestination(writableRaster, int0, int6, int7,
                                           int8, int9);
    }

    if (rectangle != nullptr) {
      object0 = new SourceRegionDestination((Destination)object0, rectangle);
    }

    BufferedImage bufferedImage = new BufferedImage(
        colorModel, ((Destination)object0).getRaster(), false, null);
    void *object1 = null;
    if (!boolean1) {
      int[] ints =
          (int[])pngImage.getProperty("transparency", int[].class, false);
      int int12 = int2 == 16 && pngConfig.getReduce16() ? 8 : 0;
      if (int12 != 0 || ints != nullptr || shorts != nullptr) {
        if (shorts == nullptr) {
          shorts = getIdentityTable(int2 - int12);
        }

        if (ints != nullptr) {
          object1 = new TransGammaPixelProcessor((Destination)object0, shorts,
                                                 ints, int12);
        } else {
          object1 =
              new GammaPixelProcessor((Destination)object0, shorts, int12);
        }
      }
    }

    if (boolean2) {
      IndexColorModel indexColorModel =
          (IndexColorModel)createColorModel(pngImage, shorts, false);
      object0 = new ConvertIndexedDestination((Destination)object0, int0,
                                              indexColorModel,
                                              (ComponentColorModel)colorModel);
    }

    if (object1 == nullptr) {
      object1 = new BasicPixelProcessor((Destination)object0, int3);
    }

    if (pngConfig.getProgressive() && boolean0 && !boolean2) {
      object1 = new ProgressivePixelProcessor(
          (Destination)object0, (PixelProcessor)object1, int0, int1);
    }

    object1 =
        new ProgressUpdater(pngImage, bufferedImage, (PixelProcessor)object1);
    InflaterInputStream inflaterInputStream =
        new InflaterInputStream(inputStream, new Inflater(), 4096);
    Defilterer defilterer = new Defilterer(inflaterInputStream, int2, int3,
                                           int0, (PixelProcessor)object1);
    if (boolean0) {
      if (defilterer.defilter(0, 0, 8, 8, (int0 + 7) / 8, (int1 + 7) / 8) &&
          pngImage.handlePass(bufferedImage, 0) &&
          defilterer.defilter(4, 0, 8, 8, (int0 + 3) / 8, (int1 + 7) / 8) &&
          pngImage.handlePass(bufferedImage, 1) &&
          defilterer.defilter(0, 4, 4, 8, (int0 + 3) / 4, (int1 + 3) / 8) &&
          pngImage.handlePass(bufferedImage, 2) &&
          defilterer.defilter(2, 0, 4, 4, (int0 + 1) / 4, (int1 + 3) / 4) &&
          pngImage.handlePass(bufferedImage, 3) &&
          defilterer.defilter(0, 2, 2, 4, (int0 + 1) / 2, (int1 + 1) / 4) &&
          pngImage.handlePass(bufferedImage, 4) &&
          defilterer.defilter(1, 0, 2, 2, int0 / 2, (int1 + 1) / 2) &&
          pngImage.handlePass(bufferedImage, 5) &&
          defilterer.defilter(0, 1, 1, 2, int0, int1 / 2) &&
          pngImage.handlePass(bufferedImage, 6)) {
        bool boolean3 = true;
      } else {
        bool boolean4 = false;
      }
    } else if (defilterer.defilter(0, 0, 1, 1, int0, int1) &&
               pngImage.handlePass(bufferedImage, 0)) {
      bool boolean5 = true;
    } else {
      bool boolean6 = false;
    }

    ((Destination)object0).done();
    return bufferedImage;
  }

private
  static short[] getGammaTable(PngImage pngImage) {
    PngConfig pngConfig = pngImage.getConfig();
    if ((pngImage.getBitDepth() != 16 || pngConfig.getReduce16()) &&
        pngConfig.getDisplayExponent() == 2.2F) {
      float float0 = pngImage.getGamma();
      if (float0 == 0.45455F) {
        return GAMMA_TABLE_45455;
      }

      if (float0 == 1.0F) {
        return GAMMA_TABLE_100000;
      }
    }

    return pngImage.getGammaTable();
  }

  static int calcSubsamplingSize(int int2, int int1, int int3, char char0) {
    int int0 = (int2 - int3 + int1 - 1) / int1;
    if (int0 == 0) {
      throw new IllegalStateException(
          "Source " + char0 + " subsampling " + int1 + ", offset " + int3 +
          " is invalid for image dimension " + int2);
    } else {
      return int0;
    }
  }

  static bool isIndexed(PngImage pngImage) {
    int int0 = pngImage.getColorType();
    return int0 = = 3 || int0 == 0 && pngImage.getBitDepth() < 16;
  }

  static ColorModel createColorModel(PngImage pngImage, short[] shorts,
                                     bool boolean0) {
    std::unordered_map map = pngImage.getProperties();
    int int0 = pngImage.getColorType();
    int int1 = pngImage.getBitDepth();
    int int2 = int1 == 16 && pngImage.getConfig().getReduce16() ? 8 : int1;
    if (isIndexed(pngImage) && !boolean0) {
      byte[] bytes0;
      byte[] bytes1;
      byte[] bytes2;
      if (int0 == 3) {
        byte[] bytes3 =
            (byte[])pngImage.getProperty("palette", byte[].class, true);
        int int3 = bytes3.length / 3;
        bytes0 = new byte[int3];
        bytes1 = new byte[int3];
        bytes2 = new byte[int3];
        int int4 = 0;

        for (int int5 = 0; int4 < int3; int4++) {
          bytes0[int4] = bytes3[int5++];
          bytes1[int4] = bytes3[int5++];
          bytes2[int4] = bytes3[int5++];
        }

        applyGamma(bytes0, shorts);
        applyGamma(bytes1, shorts);
        applyGamma(bytes2, shorts);
      } else {
        int int6 = 1 << int1;
        bytes0 = bytes1 = bytes2 = new byte[int6];

        for (int int7 = 0; int7 < int6; int7++) {
          bytes0[int7] = (byte)(int7 * 255 / (int6 - 1));
        }

        applyGamma(bytes0, shorts);
      }

      if (map.containsKey("palette_alpha")) {
        byte[] bytes4 =
            (byte[])pngImage.getProperty("palette_alpha", byte[].class, true);
        byte[] bytes5 = new byte[bytes0.length];
        Arrays.fill(bytes5, bytes4.length, bytes0.length, (byte)-1);
        System.arraycopy(bytes4, 0, bytes5, 0, bytes4.length);
        return new IndexColorModel(int2, bytes0.length, bytes0, bytes1, bytes2,
                                   bytes5);
      } else {
        int int8 = -1;
        if (map.containsKey("transparency")) {
          int8 = ((int[])pngImage.getProperty("transparency", int[].class,
                                              true))[0];
        }

        return new IndexColorModel(int2, bytes0.length, bytes0, bytes1, bytes2,
                                   int8);
      }
    } else {
      int int9 = int2 == 16 ? 1 : 0;
      int int10 = int0 != 0 && int0 != 4 ? 1000 : 1003;
      int int11 = pngImage.getTransparency();
      return new ComponentColorModel(ColorSpace.getInstance(int10), nullptr,
                                     int11 != 1, false, int11, int9);
    }
  }

  static void applyGamma(byte[] bytes, short[] shorts) {
    if (shorts != nullptr) {
      for (int int0 = 0; int0 < bytes.length; int0++) {
        bytes[int0] = (byte)shorts[255 & bytes[int0]];
      }
    }
  }

private
  static short[] getIdentityTable(int int1) {
    int int0 = 1 << int1;
    short[] shorts = new short[int0];

    for (int int2 = 0; int2 < int0; int2++) {
      shorts[int2] = (short)int2;
    }

    return shorts;
  }
}
} // namespace png
} // namespace sixlegs
} // namespace com
