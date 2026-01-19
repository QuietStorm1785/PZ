#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace jcraft {
namespace jogg {

class Page {
public:
   private static std::vector<int> crc_lookup = std::make_shared<std::array<int, 256>>();
    int body;
   public byte[] body_base;
    int body_len;
    int header;
   public byte[] header_base;
    int header_len;

    static int crc_entry(int var0) {
    int var1 = var0 << 24;

      for (int var2 = 0; var2 < 8; var2++) {
         if ((var1 & -2147483648) != 0) {
            var1 = var1 << 1 ^ 79764919;
         } else {
            var1 <<= 1;
         }
      }

      return var1 & -1;
   }

    int bos() {
      return this.header_base[this.header + 5] & 2;
   }

    Page copy() {
      return this.copy(std::make_unique<Page>());
   }

    Page copy(Page var1) {
      std::vector<byte> var2 = new byte[this.header_len];
      System.arraycopy(this.header_base, this.header, var2, 0, this.header_len);
      var1.header_len = this.header_len;
      var1.header_base = var2;
      var1.header = 0;
      var2 = new byte[this.body_len];
      System.arraycopy(this.body_base, this.body, var2, 0, this.body_len);
      var1.body_len = this.body_len;
      var1.body_base = var2;
      var1.body = 0;
    return var1;
   }

    int eos() {
      return this.header_base[this.header + 5] & 4;
   }

    long granulepos() {
    long var1 = this.header_base[this.header + 13] & 255;
      var1 = var1 << 8 | this.header_base[this.header + 12] & 255;
      var1 = var1 << 8 | this.header_base[this.header + 11] & 255;
      var1 = var1 << 8 | this.header_base[this.header + 10] & 255;
      var1 = var1 << 8 | this.header_base[this.header + 9] & 255;
      var1 = var1 << 8 | this.header_base[this.header + 8] & 255;
      var1 = var1 << 8 | this.header_base[this.header + 7] & 255;
      return var1 << 8 | this.header_base[this.header + 6] & 255;
   }

    int serialno() {
      return this.header_base[this.header + 14] & 0xFF
         | (this.header_base[this.header + 15] & 0xFF) << 8
         | (this.header_base[this.header + 16] & 0xFF) << 16
         | (this.header_base[this.header + 17] & 0xFF) << 24;
   }

    void checksum() {
    int var1 = 0;

      for (int var2 = 0; var2 < this.header_len; var2++) {
         var1 = var1 << 8 ^ crc_lookup[var1 >>> 24 & 0xFF ^ this.header_base[this.header + var2] & 255];
      }

      for (int var3 = 0; var3 < this.body_len; var3++) {
         var1 = var1 << 8 ^ crc_lookup[var1 >>> 24 & 0xFF ^ this.body_base[this.body + var3] & 255];
      }

      this.header_base[this.header + 22] = (byte)var1;
      this.header_base[this.header + 23] = (byte)(var1 >>> 8);
      this.header_base[this.header + 24] = (byte)(var1 >>> 16);
      this.header_base[this.header + 25] = (byte)(var1 >>> 24);
   }

    int continued() {
      return this.header_base[this.header + 5] & 1;
   }

    int pageno() {
      return this.header_base[this.header + 18] & 0xFF
         | (this.header_base[this.header + 19] & 0xFF) << 8
         | (this.header_base[this.header + 20] & 0xFF) << 16
         | (this.header_base[this.header + 21] & 0xFF) << 24;
   }

    int version() {
      return this.header_base[this.header + 4] & 0xFF;
   }

   static {
      for (int var0 = 0; var0 < crc_lookup.length; var0++) {
         crc_lookup[var0] = crc_entry(var0);
      }
   }
}
} // namespace jogg
} // namespace jcraft
} // namespace com
