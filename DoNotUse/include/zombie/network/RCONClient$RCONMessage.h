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
namespace network {


class RCONClient {
public:
   private static const byte[] input = new byte[4096];
    static const ByteBuffer bbr = ByteBuffer.wrap(input);
   private static const byte[] output = new byte[4096];
    static const ByteBuffer bbw = ByteBuffer.wrap(output);
    static const int baseSize = 10;
    int size;
    int id;
    int type;
   byte[] body;

   RCONClient$RCONMessage() {
   }

   RCONClient$RCONMessage(int var1, int var2, std::string var3) throws UnsupportedEncodingException {
      this.id = var1;
      this.type = var2;
      this.body = var3.getBytes();
      this.size = 10 + var3.length();
   }

    void writeObject(OutputStream var1) {
      bbw.putInt(this.size);
      bbw.putInt(this.id);
      bbw.putInt(this.type);
      bbw.put(this.body);
      bbw.put((byte)0);
      bbw.put((byte)0);
      var1.write(output, 0, this.size + 4);
      bbw.clear();
   }

    void readObject(InputStream var1, int var2) {
      if (var2 == 0) {
         var1.read(input);
      } else {
         var1.read(input, 0, var2);
      }

      this.size = bbr.getInt();
      this.id = bbr.getInt();
      this.type = bbr.getInt();
      if (this.size > 10) {
         this.body = new byte[this.size - 10];
         bbr.get(this.body, 0, this.size - 10);
      }

      bbr.get();
      bbr.get();
      bbr.clear();
   }

   static {
      bbr.order(ByteOrder.LITTLE_ENDIAN);
      bbw.order(ByteOrder.LITTLE_ENDIAN);
   }
}
} // namespace network
} // namespace zombie
