#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/image/BufferedImage.h"

namespace com {
namespace sixlegs {
namespace png {


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

    public ProgressUpdater(PngImage var1, BufferedImage var2, PixelProcessor var3) {
      this.png = var1;
      this.image = var2;
      this.pp = var3;
      this.total = var1.getWidth() * var1.getHeight();
      this.step = Math.max(1, this.total * 5 / 100);
   }

    bool process(int[] var1, int var2, int var3, int var4, int var5, int var6) {
    bool var7 = this.pp.process(var1, var2, var3, var4, var5, var6);
      this.mod += var6;
      this.count += var6;
      if (this.mod > this.step) {
         this.mod = this.mod % this.step;
         var7 = var7 && this.png.handleProgress(this.image, 100.0F * this.count / this.total);
      }

    return var7;
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
