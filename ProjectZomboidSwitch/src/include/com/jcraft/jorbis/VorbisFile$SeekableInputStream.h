#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace jcraft {
namespace jorbis {


class VorbisFile {
public:
    const std::string mode;
    RandomAccessFile raf;

   VorbisFile$SeekableInputStream(VorbisFile var1, std::string var2) throws IOException {
      this.this$0 = var1;
      this.mode = "r";
      this.raf = nullptr;
      this.raf = std::make_shared<RandomAccessFile>(var2, "r");
   }

    int available() {
      return this.raf.length() == this.raf.getFilePointer() ? 0 : 1;
   }

    void close() {
      this.raf.close();
   }

    long getLength() {
      return this.raf.length();
   }

   public /* synchronized - TODO: add std::mutex */ void mark(int var1) {
   }

    bool markSupported() {
    return false;
   }

    int read() {
      return this.raf.read();
   }

    int read(byte[] var1) {
      return this.raf.read(var1);
   }

    int read(byte[] var1, int var2, int var3) {
      return this.raf.read(var1, var2, var3);
   }

   public /* synchronized - TODO: add std::mutex */ void reset() throws IOException {
   }

    void seek(long var1) {
      this.raf.seek(var1);
   }

    long skip(long var1) {
      return this.raf.skipBytes((int)var1);
   }

    long tell() {
      return this.raf.getFilePointer();
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
