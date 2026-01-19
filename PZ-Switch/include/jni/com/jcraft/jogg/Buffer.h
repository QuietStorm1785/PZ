#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/areas/IsoArea.h"

namespace com {
namespace jcraft {
namespace jogg {


class Buffer {
:
    static std::string version = "0a2a0q";
    static const int BUFFER_INCREMENT = 256;
   private static int[] mask = new int[]{
      0,
      1,
      3,
      7,
      15,
      31,
      63,
      127,
      255,
      511,
      1023,
      2047,
      4095,
      8191,
      16383,
      32767,
      65535,
      131071,
      262143,
      524287,
      1048575,
      2097151,
      4194303,
      8388607,
      16777215,
      33554431,
      67108863,
      134217727,
      268435455,
      536870911,
      1073741823,
      Integer.MAX_VALUE,
      -1
   };
   byte[] buffer = nullptr;
    int endbit = 0;
    int endbyte = 0;
    int ptr = 0;
    int storage = 0;

    static int ilog(int var0) {
    int var1 = 0;

      while (var0 > 0) {
         var1++;
         var0 >>>= 1;
      }

    return var1;
   }

    static void report(const std::string& var0) {
      System.err.println(var0);
      System.exit(1);
   }

    void adv(int var1) {
      var1 += this.endbit;
      this.ptr += var1 / 8;
      this.endbyte += var1 / 8;
      this.endbit = var1 & 7;
   }

    void adv1() {
      this.endbit++;
      if (this.endbit > 7) {
         this.endbit = 0;
         this.ptr++;
         this.endbyte++;
      }
   }

    int bits() {
      return this.endbyte * 8 + this.endbit;
   }

    byte[] buffer() {
      return this.buffer;
   }

    int bytes() {
      return this.endbyte + (this.endbit + 7) / 8;
   }

    int look(int var1) {
    int var3 = mask[var1];
      var1 += this.endbit;
      if (this.endbyte + 4 >= this.storage && this.endbyte + (var1 - 1) / 8 >= this.storage) {
         return -1;
      } else {
    int var2 = (this.buffer[this.ptr] & 255) >>> this.endbit;
         if (var1 > 8) {
            var2 |= (this.buffer[this.ptr + 1] & 255) << 8 - this.endbit;
            if (var1 > 16) {
               var2 |= (this.buffer[this.ptr + 2] & 255) << 16 - this.endbit;
               if (var1 > 24) {
                  var2 |= (this.buffer[this.ptr + 3] & 255) << 24 - this.endbit;
                  if (var1 > 32 && this.endbit != 0) {
                     var2 |= (this.buffer[this.ptr + 4] & 255) << 32 - this.endbit;
                  }
               }
            }
         }

         return var3 & var2;
      }
   }

    int look1() {
      return this.endbyte >= this.storage ? -1 : this.buffer[this.ptr] >> this.endbit & 1;
   }

    int read(int var1) {
    int var3 = mask[var1];
      var1 += this.endbit;
      if (this.endbyte + 4 >= this.storage) {
    uint8_t var2 = -1;
         if (this.endbyte + (var1 - 1) / 8 >= this.storage) {
            this.ptr += var1 / 8;
            this.endbyte += var1 / 8;
            this.endbit = var1 & 7;
    return var2;
         }
      }

    int var5 = (this.buffer[this.ptr] & 255) >>> this.endbit;
      if (var1 > 8) {
         var5 |= (this.buffer[this.ptr + 1] & 255) << 8 - this.endbit;
         if (var1 > 16) {
            var5 |= (this.buffer[this.ptr + 2] & 255) << 16 - this.endbit;
            if (var1 > 24) {
               var5 |= (this.buffer[this.ptr + 3] & 255) << 24 - this.endbit;
               if (var1 > 32 && this.endbit != 0) {
                  var5 |= (this.buffer[this.ptr + 4] & 255) << 32 - this.endbit;
               }
            }
         }
      }

      var5 &= var3;
      this.ptr += var1 / 8;
      this.endbyte += var1 / 8;
      this.endbit = var1 & 7;
    return var5;
   }

    void read(byte[] var1, int var2) {
    int var3 = 0;

      while (var2-- != 0) {
         var1[var3++] = (byte)this.read(8);
      }
   }

    int read1() {
      if (this.endbyte >= this.storage) {
    uint8_t var2 = -1;
         this.endbit++;
         if (this.endbit > 7) {
            this.endbit = 0;
            this.ptr++;
            this.endbyte++;
         }

    return var2;
      } else {
    int var1 = this.buffer[this.ptr] >> this.endbit & 1;
         this.endbit++;
         if (this.endbit > 7) {
            this.endbit = 0;
            this.ptr++;
            this.endbyte++;
         }

    return var1;
      }
   }

    int readB(int var1) {
    int var3 = 32 - var1;
      var1 += this.endbit;
      if (this.endbyte + 4 >= this.storage) {
    uint8_t var2 = -1;
         if (this.endbyte * 8 + var1 > this.storage * 8) {
            this.ptr += var1 / 8;
            this.endbyte += var1 / 8;
            this.endbit = var1 & 7;
    return var2;
         }
      }

    int var5 = (this.buffer[this.ptr] & 255) << 24 + this.endbit;
      if (var1 > 8) {
         var5 |= (this.buffer[this.ptr + 1] & 255) << 16 + this.endbit;
         if (var1 > 16) {
            var5 |= (this.buffer[this.ptr + 2] & 255) << 8 + this.endbit;
            if (var1 > 24) {
               var5 |= (this.buffer[this.ptr + 3] & 255) << this.endbit;
               if (var1 > 32 && this.endbit != 0) {
                  var5 |= (this.buffer[this.ptr + 4] & 255) >> 8 - this.endbit;
               }
            }
         }
      }

      var5 = var5 >>> (var3 >> 1) >>> (var3 + 1 >> 1);
      this.ptr += var1 / 8;
      this.endbyte += var1 / 8;
      this.endbit = var1 & 7;
    return var5;
   }

    void readinit(byte[] var1, int var2) {
      this.readinit(var1, 0, var2);
   }

    void readinit(byte[] var1, int var2, int var3) {
      this.ptr = var2;
      this.buffer = var1;
      this.endbit = this.endbyte = 0;
      this.storage = var3;
   }

    void write(byte[] var1) {
      for (int var2 = 0; var2 < var1.length && var1[var2] != 0; var2++) {
         this.write(var1[var2], 8);
      }
   }

    void write(int var1, int var2) {
      if (this.endbyte + 4 >= this.storage) {
         byte[] var3 = new byte[this.storage + 256];
         System.arraycopy(this.buffer, 0, var3, 0, this.storage);
         this.buffer = var3;
         this.storage += 256;
      }

      var1 &= mask[var2];
      var2 += this.endbit;
      this.buffer[this.ptr] = (byte)(this.buffer[this.ptr] | (byte)(var1 << this.endbit));
      if (var2 >= 8) {
         this.buffer[this.ptr + 1] = (byte)(var1 >>> 8 - this.endbit);
         if (var2 >= 16) {
            this.buffer[this.ptr + 2] = (byte)(var1 >>> 16 - this.endbit);
            if (var2 >= 24) {
               this.buffer[this.ptr + 3] = (byte)(var1 >>> 24 - this.endbit);
               if (var2 >= 32) {
                  if (this.endbit > 0) {
                     this.buffer[this.ptr + 4] = (byte)(var1 >>> 32 - this.endbit);
                  } else {
                     this.buffer[this.ptr + 4] = 0;
                  }
               }
            }
         }
      }

      this.endbyte += var2 / 8;
      this.ptr += var2 / 8;
      this.endbit = var2 & 7;
   }

    void writeclear() {
      this.buffer = nullptr;
   }

    void writeinit() {
      this.buffer = new byte[256];
      this.ptr = 0;
      this.buffer[0] = 0;
      this.storage = 256;
   }

    void reset() {
      this.ptr = 0;
      this.buffer[0] = 0;
      this.endbit = this.endbyte = 0;
   }

   static {
      if (!version == IsoArea.version)) {
         System.exit(0);
      }
   }
}
} // namespace jogg
} // namespace jcraft
} // namespace com
