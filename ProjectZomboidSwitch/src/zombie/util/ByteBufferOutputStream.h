#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace util {


class ByteBufferOutputStream : public OutputStream {
public:
    ByteBuffer wrappedBuffer;
    const bool autoEnlarge;

    public ByteBufferOutputStream(ByteBuffer var1, bool var2) {
      this.wrappedBuffer = var1;
      this.autoEnlarge = var2;
   }

    ByteBuffer toByteBuffer() {
    ByteBuffer var1 = this.wrappedBuffer.duplicate();
      var1.flip();
      return var1.asReadOnlyBuffer();
   }

    ByteBuffer getWrappedBuffer() {
      return this.wrappedBuffer;
   }

    void clear() {
      this.wrappedBuffer.clear();
   }

    void flip() {
      this.wrappedBuffer.flip();
   }

    void growTo(int var1) {
    int var2 = this.wrappedBuffer.capacity();
    int var3 = var2 << 1;
      if (var3 - var1 < 0) {
         var3 = var1;
      }

      if (var3 < 0) {
         if (var1 < 0) {
            throw std::make_unique<OutOfMemoryError>();
         }

         var3 = int.MAX_VALUE;
      }

    ByteBuffer var4 = this.wrappedBuffer;
      if (this.wrappedBuffer.isDirect()) {
         this.wrappedBuffer = ByteBuffer.allocateDirect(var3);
      } else {
         this.wrappedBuffer = ByteBuffer.allocate(var3);
      }

      var4.flip();
      this.wrappedBuffer.put(var4);
   }

    void write(int var1) {
      try {
         this.wrappedBuffer.put((byte)var1);
      } catch (BufferOverflowException var4) {
         if (!this.autoEnlarge) {
    throw var4;
         }

    int var3 = this.wrappedBuffer.capacity() * 2;
         this.growTo(var3);
         this.write(var1);
      }
   }

    void write(byte[] var1) {
    int var2 = 0;

      try {
         var2 = this.wrappedBuffer.position();
         this.wrappedBuffer.put(var1);
      } catch (BufferOverflowException var5) {
         if (!this.autoEnlarge) {
    throw var5;
         }

    int var4 = Math.max(this.wrappedBuffer.capacity() * 2, var2 + var1.length);
         this.growTo(var4);
         this.write(var1);
      }
   }

    void write(byte[] var1, int var2, int var3) {
    int var4 = 0;

      try {
         var4 = this.wrappedBuffer.position();
         this.wrappedBuffer.put(var1, var2, var3);
      } catch (BufferOverflowException var7) {
         if (!this.autoEnlarge) {
    throw var7;
         }

    int var6 = Math.max(this.wrappedBuffer.capacity() * 2, var4 + var3);
         this.growTo(var6);
         this.write(var1, var2, var3);
      }
   }
}
} // namespace util
} // namespace zombie
