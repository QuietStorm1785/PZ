#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {


class TexturePackDevice {
public:
    long pos;
    long mark;

   public TexturePackDevice$PositionInputStream(TexturePackDevice var1, InputStream var2) {
      super(var2);
      this.this$0 = var1;
      this.pos = 0L;
      this.mark = 0L;
   }

   public /* synchronized - TODO: add std::mutex */ long getPosition() {
      return this.pos;
   }

   public /* synchronized - TODO: add std::mutex */ int read() throws IOException {
    int var1 = super.read();
      if (var1 >= 0) {
         this.pos++;
      }

    return var1;
   }

   public /* synchronized - TODO: add std::mutex */ int read(byte[] var1, int var2, int var3) throws IOException {
    int var4 = super.read(var1, var2, var3);
      if (var4 > 0) {
         this.pos += var4;
      }

    return var4;
   }

   public /* synchronized - TODO: add std::mutex */ long skip(long var1) throws IOException {
    long var3 = super.skip(var1);
      if (var3 > 0L) {
         this.pos += var3;
      }

    return var3;
   }

   public /* synchronized - TODO: add std::mutex */ void mark(int var1) {
      super.mark(var1);
      this.mark = this.pos;
   }

   public /* synchronized - TODO: add std::mutex */ void reset() throws IOException {
      if (!this.markSupported()) {
         throw IOException("Mark not supported.");
      } else {
         super.reset();
         this.pos = this.mark;
      }
   }
}
} // namespace fileSystem
} // namespace zombie
