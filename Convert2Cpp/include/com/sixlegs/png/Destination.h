#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/image/WritableRaster.h"

namespace com {
namespace sixlegs {
namespace png {


class Destination {
public:
   public abstract void setPixels(int var1, int var2, int var3, int[] var4);

   public abstract void setPixel(int var1, int var2, int[] var3);

   public abstract void getPixel(int var1, int var2, int[] var3);

   public abstract WritableRaster getRaster();

   public abstract int getSourceWidth();

   public abstract void done();
}
} // namespace png
} // namespace sixlegs
} // namespace com
