#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/jcraft/jogg/Buffer.h"
#include "com/jcraft/jogg/Packet.h"

namespace com {
namespace jcraft {
namespace jorbis {


class Comment {
:
   private static byte[] _vorbis = "vorbis".getBytes();
   private static byte[] _vendor = "Xiphophorus libVorbis I 20000508".getBytes();
    static const int OV_EIMPL = -130;
    int[] comment_lengths;
    int comments;
    byte[][] user_comments;
    byte[] vendor;

    static bool tagcompare(byte[] var0, byte[] var1, int var2) {
      for (int var3 = 0; var3 < var2; var3++) {
    uint8_t var4 = var0[var3];
    uint8_t var5 = var1[var3];
         if (90 >= var4 && var4 >= 65) {
            var4 = (byte)(var4 - 65 + 97);
         }

         if (90 >= var5 && var5 >= 65) {
            var5 = (byte)(var5 - 65 + 97);
         }

         if (var4 != var5) {
    return false;
         }
      }

    return true;
   }

    void add(std::string_view var1) {
      this.add(var1.getBytes());
   }

    void add_tag(std::string_view var1, std::string_view var2) {
      if (var2 == nullptr) {
         var2 = "";
      }

      this.add(var1 + "=" + var2);
   }

    std::string getComment(int var1) {
      return this.comments <= var1 ? nullptr : new String(this.user_comments[var1], 0, this.user_comments[var1].length - 1);
   }

    std::string getVendor() const {
      return new String(this.vendor, 0, this.vendor.length - 1);
   }

    int header_out(Packet var1) {
    Buffer var2 = new Buffer();
      var2.writeinit();
      if (this.pack(var2) != 0) {
         return -130;
      } else {
         var1.packet_base = new byte[var2.bytes()];
         var1.packet = 0;
         var1.bytes = var2.bytes();
         System.arraycopy(var2.buffer(), 0, var1.packet_base, 0, var1.bytes);
         var1.b_o_s = 0;
         var1.e_o_s = 0;
         var1.granulepos = 0L;
    return 0;
      }
   }

    void init() {
      this.user_comments = nullptr;
      this.comments = 0;
      this.vendor = nullptr;
   }

    std::string query(std::string_view var1) {
      return this.query(var1, 0);
   }

    std::string query(std::string_view var1, int var2) {
    int var3 = this.query(var1.getBytes(), var2);
      if (var3 == -1) {
    return nullptr;
      } else {
         byte[] var4 = this.user_comments[var3];

         for (int var5 = 0; var5 < this.comment_lengths[var3]; var5++) {
            if (var4[var5] == 61) {
               return new String(var4, var5 + 1, this.comment_lengths[var3] - (var5 + 1));
            }
         }

    return nullptr;
      }
   }

    std::string toString() {
    std::string var1 = "Vendor: " + new String(this.vendor, 0, this.vendor.length - 1);

      for (int var2 = 0; var2 < this.comments; var2++) {
         var1 = var1 + "\nComment: " + new String(this.user_comments[var2], 0, this.user_comments[var2].length - 1);
      }

      return var1 + "\n";
   }

    void clear() {
      for (int var1 = 0; var1 < this.comments; var1++) {
         this.user_comments[var1] = nullptr;
      }

      this.user_comments = nullptr;
      this.vendor = nullptr;
   }

    int pack(Buffer var1) {
      var1.write(3, 8);
      var1.write(_vorbis);
      var1.write(_vendor.length, 32);
      var1.write(_vendor);
      var1.write(this.comments, 32);
      if (this.comments != 0) {
         for (int var2 = 0; var2 < this.comments; var2++) {
            if (this.user_comments[var2] != nullptr) {
               var1.write(this.comment_lengths[var2], 32);
               var1.write(this.user_comments[var2]);
            } else {
               var1.write(0, 32);
            }
         }
      }

      var1.write(1, 1);
    return 0;
   }

    int unpack(Buffer var1) {
    int var2 = var1.read(32);
      if (var2 < 0) {
         this.clear();
         return -1;
      } else {
         this.vendor = new byte[var2 + 1];
         var1.read(this.vendor, var2);
         this.comments = var1.read(32);
         if (this.comments < 0) {
            this.clear();
            return -1;
         } else {
            this.user_comments = new byte[this.comments + 1][];
            this.comment_lengths = new int[this.comments + 1];

            for (int var3 = 0; var3 < this.comments; var3++) {
    int var4 = var1.read(32);
               if (var4 < 0) {
                  this.clear();
                  return -1;
               }

               this.comment_lengths[var3] = var4;
               this.user_comments[var3] = new byte[var4 + 1];
               var1.read(this.user_comments[var3], var4);
            }

            if (var1.read(1) != 1) {
               this.clear();
               return -1;
            } else {
    return 0;
            }
         }
      }
   }

    void add(byte[] var1) {
      byte[][] var2 = new byte[this.comments + 2][];
      if (this.user_comments != nullptr) {
         System.arraycopy(this.user_comments, 0, var2, 0, this.comments);
      }

      this.user_comments = var2;
      int[] var3 = new int[this.comments + 2];
      if (this.comment_lengths != nullptr) {
         System.arraycopy(this.comment_lengths, 0, var3, 0, this.comments);
      }

      this.comment_lengths = var3;
      byte[] var4 = new byte[var1.length + 1];
      System.arraycopy(var1, 0, var4, 0, var1.length);
      this.user_comments[this.comments] = var4;
      this.comment_lengths[this.comments] = var1.length;
      this.comments++;
      this.user_comments[this.comments] = nullptr;
   }

    int query(byte[] var1, int var2) {
    bool var3 = false;
    int var4 = 0;
    int var5 = var1.length + 1;
      byte[] var6 = new byte[var5];
      System.arraycopy(var1, 0, var6, 0, var1.length);
      var6[var1.length] = 61;

      for (int var7 = 0; var7 < this.comments; var7++) {
         if (tagcompare(this.user_comments[var7], var6, var5)) {
            if (var2 == var4) {
    return var7;
            }

            var4++;
         }
      }

      return -1;
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
