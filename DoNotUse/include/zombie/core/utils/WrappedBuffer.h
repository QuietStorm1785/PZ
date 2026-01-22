#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/system/MemoryUtil.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace utils {


class WrappedBuffer {
public:
    ByteBuffer buf;
    const int capacity;
    bool disposed;

    public WrappedBuffer(int var1) {
      this.buf = MemoryUtil.memAlloc(var1);
      MemoryUtil.memSet(this.buf, 0);
      this.capacity = this.buf.capacity();
   }

    ByteBuffer getBuffer() {
      if (this.disposed) {
         throw IllegalStateException("Can't get buffer after disposal");
      } else {
         return this.buf;
      }
   }

    int capacity() {
      return this.capacity;
   }

    void dispose() {
      if (this.disposed) {
         throw IllegalStateException("WrappedBuffer was already disposed");
      } else {
         this.disposed = true;
         MemoryUtil.memFree(this.buf);
         this.buf = nullptr;
      }
   }

    bool isDisposed() {
      return this.disposed;
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
