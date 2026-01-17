#pragma once
#include "java/awt/image/BufferedImage.h"
#include <cstdint>
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

class ProgressUpdater : public PixelProcessor {
public:
  static const int STEP_PERCENT = 5;
  const PngImage png;
  const BufferedImage image;
  const PixelProcessor pp;
  const int total;
  const int step;
  int count;
  int mod;

public
  ProgressUpdater(PngImage pngImage, BufferedImage bufferedImage,
                  PixelProcessor pixelProcessor) {
    this.png = pngImage;
    this.image = bufferedImage;
    this.pp = pixelProcessor;
    this.total = pngImage.getWidth() * pngImage.getHeight();
    this.step = Math.max(1, this.total * 5 / 100);
  }

  bool process(int[] ints, int int0, int int1, int int2, int int3, int int4) {
    bool boolean0 = this.pp.process(ints, int0, int1, int2, int3, int4);
    this.mod += int4;
    this.count += int4;
    if (this.mod > this.step) {
      this.mod = this.mod % this.step;
      boolean0 = boolean0 && this.png.handleProgress(
                                 this.image, 100.0F * this.count / this.total);
    }

    return boolean0;
  }
}
} // namespace png
} // namespace sixlegs
} // namespace com
