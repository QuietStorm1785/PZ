#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace utils {


class ObjectCube {
public:
    const int width;
    const int height;
    const int depth;
   private const Object[] value;

    public ObjectCube(int var1, int var2, int var3) {
      DebugLog.log("Created object cube of size " + var1 + "x" + var2 + "x" + var3 + " (" + var1 * var2 * var3 * 4 + " bytes)");
      this.width = var1;
      this.height = var2;
      this.depth = var3;
      this.value = new Object[var1 * var2 * var3];
   }

   public ObjectCube<T> clone() throws CloneNotSupportedException {
    ObjectCube var1 = std::make_shared<ObjectCube>(this.width, this.height, this.depth);
      System.arraycopy(this.value, 0, var1.value, 0, this.value.length);
    return var1;
   }

    void clear() {
      Arrays.fill(this.value, nullptr);
   }

    void fill(T var1) {
      Arrays.fill(this.value, var1);
   }

    int getIndex(int var1, int var2, int var3) {
      return var1 >= 0 && var2 >= 0 && var3 >= 0 && var1 < this.width && var2 < this.height && var3 < this.depth
         ? var1 + var2 * this.width + var3 * this.width * this.height
         : -1;
   }

    T getValue(int var1, int var2, int var3) {
    int var4 = this.getIndex(var1, var2, var3);
      return (T)(var4 == -1 ? nullptr : this.value[var4]);
   }

    void setValue(int var1, int var2, int var3, T var4) {
    int var5 = this.getIndex(var1, var2, var3);
      if (var5 != -1) {
         this.value[var5] = var4;
      }
   }

    int getWidth() {
      return this.width;
   }

    int getHeight() {
      return this.height;
   }

    int getDepth() {
      return this.depth;
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
