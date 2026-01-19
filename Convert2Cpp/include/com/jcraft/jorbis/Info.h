#pragma once
#include <string>
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


class Info {
public:
    static const int OV_EBADPACKET = -136;
    static const int OV_ENOTAUDIO = -135;
   private static byte[] _vorbis = "vorbis".getBytes();
    static const int VI_TIMEB = 1;
    static const int VI_FLOORB = 2;
    static const int VI_RESB = 3;
    static const int VI_MAPB = 1;
    static const int VI_WINDOWB = 1;
    int channels;
    int rate;
    int version;
    int bitrate_lower;
    int bitrate_nominal;
    int bitrate_upper;
   int[] blocksizes = new int[2];
   StaticCodeBook[] book_param = nullptr;
    int books;
    int envelopesa;
   Object[] floor_param = nullptr;
   int[] floor_type = nullptr;
    int floors;
   Object[] map_param = nullptr;
   int[] map_type = nullptr;
    int maps;
   InfoMode[] mode_param = nullptr;
    int modes;
    float preecho_clamp;
    float preecho_thresh;
   PsyInfo[] psy_param = new PsyInfo[64];
    int psys;
   Object[] residue_param = nullptr;
   int[] residue_type = nullptr;
    int residues;
   Object[] time_param = nullptr;
   int[] time_type = nullptr;
    int times;

    int blocksize(Packet var1) {
    Buffer var2 = new Buffer();
      var2.readinit(var1.packet_base, var1.packet, var1.bytes);
      if (var2.read(1) != 0) {
         return -135;
      } else {
    int var4 = 0;

         for (int var5 = this.modes; var5 > 1; var5 >>>= 1) {
            var4++;
         }

    int var3 = var2.read(var4);
    return var3 = = -1 ? -136 : this.blocksizes[this.mode_param[var3].blockflag];
      }
   }

    void clear() {
      for (int var1 = 0; var1 < this.modes; var1++) {
         this.mode_param[var1] = nullptr;
      }

      this.mode_param = nullptr;

      for (int var2 = 0; var2 < this.maps; var2++) {
         FuncMapping.mapping_P[this.map_type[var2]].free_info(this.map_param[var2]);
      }

      this.map_param = nullptr;

      for (int var3 = 0; var3 < this.times; var3++) {
         FuncTime.time_P[this.time_type[var3]].free_info(this.time_param[var3]);
      }

      this.time_param = nullptr;

      for (int var4 = 0; var4 < this.floors; var4++) {
         FuncFloor.floor_P[this.floor_type[var4]].free_info(this.floor_param[var4]);
      }

      this.floor_param = nullptr;

      for (int var5 = 0; var5 < this.residues; var5++) {
         FuncResidue.residue_P[this.residue_type[var5]].free_info(this.residue_param[var5]);
      }

      this.residue_param = nullptr;

      for (int var6 = 0; var6 < this.books; var6++) {
         if (this.book_param[var6] != nullptr) {
            this.book_param[var6].clear();
            this.book_param[var6] = nullptr;
         }
      }

      this.book_param = nullptr;

      for (int var7 = 0; var7 < this.psys; var7++) {
         this.psy_param[var7].free();
      }
   }

    void init() {
      this.rate = 0;
   }

    int synthesis_headerin(Comment var1, Packet var2) {
    Buffer var3 = new Buffer();
      if (var2 != nullptr) {
         var3.readinit(var2.packet_base, var2.packet, var2.bytes);
         byte[] var4 = new byte[6];
    int var5 = var3.read(8);
         var3.read(var4, 6);
         if (var4[0] != 118 || var4[1] != 111 || var4[2] != 114 || var4[3] != 98 || var4[4] != 105 || var4[5] != 115) {
            return -1;
         }

         switch (var5) {
            case 1:
               if (var2.b_o_s == 0) {
                  return -1;
               }

               if (this.rate != 0) {
                  return -1;
               }

               return this.unpack_info(var3);
            case 2:
            case 4:
            default:
               break;
            case 3:
               if (this.rate == 0) {
                  return -1;
               }

               return var1.unpack(var3);
            case 5:
               if (this.rate != 0 && var1.vendor != nullptr) {
                  return this.unpack_books(var3);
               }

               return -1;
         }
      }

      return -1;
   }

    std::string toString() {
      return "version:"
         + new Integer(this.version)
         + ", channels:"
         + new Integer(this.channels)
         + ", rate:"
         + new Integer(this.rate)
         + ", bitrate:"
         + new Integer(this.bitrate_upper)
         + ","
         + new Integer(this.bitrate_nominal)
         + ","
         + new Integer(this.bitrate_lower);
   }

    int pack_books(Buffer var1) {
      var1.write(5, 8);
      var1.write(_vorbis);
      var1.write(this.books - 1, 8);

      for (int var2 = 0; var2 < this.books; var2++) {
         if (this.book_param[var2].pack(var1) != 0) {
            return -1;
         }
      }

      var1.write(this.times - 1, 6);

      for (int var3 = 0; var3 < this.times; var3++) {
         var1.write(this.time_type[var3], 16);
         FuncTime.time_P[this.time_type[var3]].pack(this.time_param[var3], var1);
      }

      var1.write(this.floors - 1, 6);

      for (int var4 = 0; var4 < this.floors; var4++) {
         var1.write(this.floor_type[var4], 16);
         FuncFloor.floor_P[this.floor_type[var4]].pack(this.floor_param[var4], var1);
      }

      var1.write(this.residues - 1, 6);

      for (int var5 = 0; var5 < this.residues; var5++) {
         var1.write(this.residue_type[var5], 16);
         FuncResidue.residue_P[this.residue_type[var5]].pack(this.residue_param[var5], var1);
      }

      var1.write(this.maps - 1, 6);

      for (int var6 = 0; var6 < this.maps; var6++) {
         var1.write(this.map_type[var6], 16);
         FuncMapping.mapping_P[this.map_type[var6]].pack(this, this.map_param[var6], var1);
      }

      var1.write(this.modes - 1, 6);

      for (int var7 = 0; var7 < this.modes; var7++) {
         var1.write(this.mode_param[var7].blockflag, 1);
         var1.write(this.mode_param[var7].windowtype, 16);
         var1.write(this.mode_param[var7].transformtype, 16);
         var1.write(this.mode_param[var7].mapping, 8);
      }

      var1.write(1, 1);
    return 0;
   }

    int pack_info(Buffer var1) {
      var1.write(1, 8);
      var1.write(_vorbis);
      var1.write(0, 32);
      var1.write(this.channels, 8);
      var1.write(this.rate, 32);
      var1.write(this.bitrate_upper, 32);
      var1.write(this.bitrate_nominal, 32);
      var1.write(this.bitrate_lower, 32);
      var1.write(Util.ilog2(this.blocksizes[0]), 4);
      var1.write(Util.ilog2(this.blocksizes[1]), 4);
      var1.write(1, 1);
    return 0;
   }

    int unpack_books(Buffer var1) {
      this.books = var1.read(8) + 1;
      if (this.book_param == nullptr || this.book_param.length != this.books) {
         this.book_param = new StaticCodeBook[this.books];
      }

      for (int var2 = 0; var2 < this.books; var2++) {
         this.book_param[var2] = std::make_unique<StaticCodeBook>();
         if (this.book_param[var2].unpack(var1) != 0) {
            this.clear();
            return -1;
         }
      }

      this.times = var1.read(6) + 1;
      if (this.time_type == nullptr || this.time_type.length != this.times) {
         this.time_type = new int[this.times];
      }

      if (this.time_param == nullptr || this.time_param.length != this.times) {
         this.time_param = new Object[this.times];
      }

      for (int var3 = 0; var3 < this.times; var3++) {
         this.time_type[var3] = var1.read(16);
         if (this.time_type[var3] < 0 || this.time_type[var3] >= 1) {
            this.clear();
            return -1;
         }

         this.time_param[var3] = FuncTime.time_P[this.time_type[var3]].unpack(this, var1);
         if (this.time_param[var3] == nullptr) {
            this.clear();
            return -1;
         }
      }

      this.floors = var1.read(6) + 1;
      if (this.floor_type == nullptr || this.floor_type.length != this.floors) {
         this.floor_type = new int[this.floors];
      }

      if (this.floor_param == nullptr || this.floor_param.length != this.floors) {
         this.floor_param = new Object[this.floors];
      }

      for (int var4 = 0; var4 < this.floors; var4++) {
         this.floor_type[var4] = var1.read(16);
         if (this.floor_type[var4] < 0 || this.floor_type[var4] >= 2) {
            this.clear();
            return -1;
         }

         this.floor_param[var4] = FuncFloor.floor_P[this.floor_type[var4]].unpack(this, var1);
         if (this.floor_param[var4] == nullptr) {
            this.clear();
            return -1;
         }
      }

      this.residues = var1.read(6) + 1;
      if (this.residue_type == nullptr || this.residue_type.length != this.residues) {
         this.residue_type = new int[this.residues];
      }

      if (this.residue_param == nullptr || this.residue_param.length != this.residues) {
         this.residue_param = new Object[this.residues];
      }

      for (int var5 = 0; var5 < this.residues; var5++) {
         this.residue_type[var5] = var1.read(16);
         if (this.residue_type[var5] < 0 || this.residue_type[var5] >= 3) {
            this.clear();
            return -1;
         }

         this.residue_param[var5] = FuncResidue.residue_P[this.residue_type[var5]].unpack(this, var1);
         if (this.residue_param[var5] == nullptr) {
            this.clear();
            return -1;
         }
      }

      this.maps = var1.read(6) + 1;
      if (this.map_type == nullptr || this.map_type.length != this.maps) {
         this.map_type = new int[this.maps];
      }

      if (this.map_param == nullptr || this.map_param.length != this.maps) {
         this.map_param = new Object[this.maps];
      }

      for (int var6 = 0; var6 < this.maps; var6++) {
         this.map_type[var6] = var1.read(16);
         if (this.map_type[var6] < 0 || this.map_type[var6] >= 1) {
            this.clear();
            return -1;
         }

         this.map_param[var6] = FuncMapping.mapping_P[this.map_type[var6]].unpack(this, var1);
         if (this.map_param[var6] == nullptr) {
            this.clear();
            return -1;
         }
      }

      this.modes = var1.read(6) + 1;
      if (this.mode_param == nullptr || this.mode_param.length != this.modes) {
         this.mode_param = new InfoMode[this.modes];
      }

      for (int var7 = 0; var7 < this.modes; var7++) {
         this.mode_param[var7] = std::make_unique<InfoMode>();
         this.mode_param[var7].blockflag = var1.read(1);
         this.mode_param[var7].windowtype = var1.read(16);
         this.mode_param[var7].transformtype = var1.read(16);
         this.mode_param[var7].mapping = var1.read(8);
         if (this.mode_param[var7].windowtype >= 1 || this.mode_param[var7].transformtype >= 1 || this.mode_param[var7].mapping >= this.maps) {
            this.clear();
            return -1;
         }
      }

      if (var1.read(1) != 1) {
         this.clear();
         return -1;
      } else {
    return 0;
      }
   }

    int unpack_info(Buffer var1) {
      this.version = var1.read(32);
      if (this.version != 0) {
         return -1;
      } else {
         this.channels = var1.read(8);
         this.rate = var1.read(32);
         this.bitrate_upper = var1.read(32);
         this.bitrate_nominal = var1.read(32);
         this.bitrate_lower = var1.read(32);
         this.blocksizes[0] = 1 << var1.read(4);
         this.blocksizes[1] = 1 << var1.read(4);
         if (this.rate >= 1 && this.channels >= 1 && this.blocksizes[0] >= 8 && this.blocksizes[1] >= this.blocksizes[0] && var1.read(1) == 1) {
    return 0;
         } else {
            this.clear();
            return -1;
         }
      }
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
