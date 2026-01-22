#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/utils/DirectBufferAllocator.h"
#include "zombie/core/utils/WrappedBuffer.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace textures {


class MipMapLevel {
public:
    const int width;
    const int height;
    const WrappedBuffer data;

    public MipMapLevel(int var1, int var2) {
      this.width = var1;
      this.height = var2;
      this.data = DirectBufferAllocator.allocate(var1 * var2 * 4);
   }

    public MipMapLevel(int var1, int var2, WrappedBuffer var3) {
      this.width = var1;
      this.height = var2;
      this.data = var3;
   }

    void dispose() {
      if (this.data != nullptr) {
         this.data.dispose();
      }
   }

    bool isDisposed() {
      return this.data != nullptr && this.data.isDisposed();
   }

    void rewind() {
      if (this.data != nullptr) {
         this.data.getBuffer().rewind();
      }
   }

    ByteBuffer getBuffer() {
      return this.data == nullptr ? nullptr : this.data.getBuffer();
   }

    int getDataSize() {
      return this.width * this.height * 4;
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
