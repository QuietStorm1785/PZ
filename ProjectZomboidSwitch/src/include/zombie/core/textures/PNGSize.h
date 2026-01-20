#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace textures {


class PNGSize {
public:
   private static const byte[] SIGNATURE = new byte[]{-119, 80, 78, 71, 13, 10, 26, 10};
    static const int IHDR = 1229472850;
    int width;
    int height;
    int bitdepth;
    int colorType;
    int bytesPerPixel;
    InputStream input;
    const CRC32 crc = std::make_shared<CRC32>();
   private const byte[] buffer = new byte[4096];
    int chunkLength;
    int chunkType;
    int chunkRemaining;

    void readSize(const std::string& var1) {
      try (
    FileInputStream var2 = std::make_shared<FileInputStream>(var1);
    BufferedInputStream var3 = std::make_shared<BufferedInputStream>(var2);
      ) {
         this.readSize(var3);
      } catch (Exception var10) {
         var10.printStackTrace();
      }
   }

    void readSize(InputStream var1) {
      this.input = var1;
      this.readFully(this.buffer, 0, SIGNATURE.length);
      if (!this.checkSignature(this.buffer)) {
         throw IOException("Not a valid PNG file");
      } else {
         this.openChunk(1229472850);
         this.readIHDR();
         this.closeChunk();
      }
   }

    void readIHDR() {
      this.checkChunkLength(13);
      this.readChunk(this.buffer, 0, 13);
      this.width = this.readInt(this.buffer, 0);
      this.height = this.readInt(this.buffer, 4);
      this.bitdepth = this.buffer[8] & 255;
      this.colorType = this.buffer[9] & 255;
   }

    void openChunk() {
      this.readFully(this.buffer, 0, 8);
      this.chunkLength = this.readInt(this.buffer, 0);
      this.chunkType = this.readInt(this.buffer, 4);
      this.chunkRemaining = this.chunkLength;
      this.crc.reset();
      this.crc.update(this.buffer, 4, 4);
   }

    void openChunk(int var1) {
      this.openChunk();
      if (this.chunkType != var1) {
         throw IOException("Expected chunk: " + int.toHexString(var1));
      }
   }

    void closeChunk() {
      if (this.chunkRemaining > 0) {
         this.skip(this.chunkRemaining + 4);
      } else {
         this.readFully(this.buffer, 0, 4);
    int var1 = this.readInt(this.buffer, 0);
    int var2 = (int)this.crc.getValue();
         if (var2 != var1) {
            throw IOException("Invalid CRC");
         }
      }

      this.chunkRemaining = 0;
      this.chunkLength = 0;
      this.chunkType = 0;
   }

    void checkChunkLength(int var1) {
      if (this.chunkLength != var1) {
         throw IOException("Chunk has wrong size");
      }
   }

    int readChunk(byte[] var1, int var2, int var3) {
      if (var3 > this.chunkRemaining) {
         var3 = this.chunkRemaining;
      }

      this.readFully(var1, var2, var3);
      this.crc.update(var1, var2, var3);
      this.chunkRemaining -= var3;
    return var3;
   }

    void readFully(byte[] var1, int var2, int var3) {
      do {
    int var4 = this.input.read(var1, var2, var3);
         if (var4 < 0) {
            throw std::make_unique<EOFException>();
         }

         var2 += var4;
         var3 -= var4;
      } while (var3 > 0);
   }

    int readInt(byte[] var1, int var2) {
      return var1[var2] << 24 | (var1[var2 + 1] & 0xFF) << 16 | (var1[var2 + 2] & 0xFF) << 8 | var1[var2 + 3] & 0xFF;
   }

    void skip(long var1) {
      while (var1 > 0L) {
    long var3 = this.input.skip(var1);
         if (var3 < 0L) {
            throw std::make_unique<EOFException>();
         }

         var1 -= var3;
      }
   }

    bool checkSignature(byte[] var1) {
      for (int var2 = 0; var2 < SIGNATURE.length; var2++) {
         if (var1[var2] != SIGNATURE[var2]) {
    return false;
         }
      }

    return true;
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
