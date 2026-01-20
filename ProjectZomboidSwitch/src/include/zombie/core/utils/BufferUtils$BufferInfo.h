#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace zombie {
namespace core {
namespace utils {


class BufferUtils {
public:
    const Class type;
    const int size;

   public BufferUtils$BufferInfo(Class var1, int var2, Buffer var3, ReferenceQueue<? super Buffer> var4) {
      super(var3, var4);
      this.type = var1;
      this.size = var2;
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
