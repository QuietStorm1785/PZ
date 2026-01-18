#pragma once
#include "java/awt/image/WritableRaster.h"
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

class Destination {
public:
public
  abstract void setPixels(int var1, int var2, int var3, int[] var4);

public
  abstract void setPixel(int var1, int var2, int[] var3);

public
  abstract void getPixel(int var1, int var2, int[] var3);

public
  abstract WritableRaster getRaster();

public
  abstract int getSourceWidth();

public
  abstract void done();
}
} // namespace png
} // namespace sixlegs
} // namespace com
