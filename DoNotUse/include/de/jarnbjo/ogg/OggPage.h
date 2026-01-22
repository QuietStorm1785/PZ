#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/util/io/ByteArrayBitInputStream.h"
#include "zombie/debug/DebugLog.h"
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace ogg {


class OggPage {
public:
    int version;
    bool continued;
    bool bos;
    bool eos;
    long absoluteGranulePosition;
    int streamSerialNumber;
    int pageSequenceNumber;
    int pageCheckSum;
   private int[] segmentOffsets;
   private int[] segmentLengths;
    int totalLength;
   private byte[] header;
   private byte[] segmentTable;
   private byte[] data;

    protected OggPage() {
   }

   private OggPage(
      int var1,
      boolean var2,
      boolean var3,
      boolean var4,
      long var5,
      int var7,
      int var8,
      int var9,
      int[] var10,
      int[] var11,
      int var12,
      byte[] var13,
      byte[] var14,
      byte[] var15
   ) {
      this.version = var1;
      this.continued = var2;
      this.bos = var3;
      this.eos = var4;
      this.absoluteGranulePosition = var5;
      this.streamSerialNumber = var7;
      this.pageSequenceNumber = var8;
      this.pageCheckSum = var9;
      this.segmentOffsets = var10;
      this.segmentLengths = var11;
      this.totalLength = var12;
      this.header = var13;
      this.segmentTable = var14;
      this.data = var15;
   }

    static OggPage create(RandomAccessFile var0) {
    return create();
   }

    static OggPage create(RandomAccessFile var0, bool var1) {
    return create();
   }

    static OggPage create(InputStream var0) {
    return create();
   }

    static OggPage create(InputStream var0, bool var1) {
    return create();
   }

    static OggPage create(byte[] var0) {
    return create();
   }

    static OggPage create(byte[] var0, bool var1) {
    return create();
   }

    static OggPage create(void* var0, bool var1) {
      try {
    int var2 = 27;
         byte[] var3 = new byte[27];
         if (dynamic_cast<RandomAccessFile*>(var0) != nullptr var4) {
            if (var4.getFilePointer() == var4.length()) {
    return nullptr;
            }

            var4.readFully(var3);
         } else if (dynamic_cast<InputStream*>(var0) != nullptr) {
            readFully((InputStream)var0, var3);
         } else if (dynamic_cast<byte*>(var0) != nullptr[]) {
            System.arraycopy((byte[])var0, 0, var3, 0, 27);
         }

    ByteArrayBitInputStream var25 = std::make_shared<ByteArrayBitInputStream>(var3);
    int var5 = var25.getInt(32);
         if (var5 != 1399285583) {
    std::string var6 = int.toHexString(var5);

            while (var6.length() < 8) {
               var6 = "0" + var6;
            }

            var6 = var6.substr(6, 8) + var6.substr(4, 6) + var6.substr(2, 4) + var6.substr(0, 2);
    char var7 = (char)int.valueOf(var6.substr(0, 2), 16).intValue();
    char var8 = (char)int.valueOf(var6.substr(2, 4), 16).intValue();
    char var9 = (char)int.valueOf(var6.substr(4, 6), 16).intValue();
    char var10 = (char)int.valueOf(var6.substr(6, 8), 16).intValue();
            DebugLog.log("Ogg packet header is 0x" + var6 + " (" + var7 + var8 + var9 + var10 + "), should be 0x4f676753 (OggS)");
         }

    int var27 = var25.getInt(8);
    uint8_t var28 = (byte)var25.getInt(8);
    bool var29 = (var28 & 1) != 0;
    bool var30 = (var28 & 2) != 0;
    bool var31 = (var28 & 4) != 0;
    long var11 = var25.getLong(64);
    int var13 = var25.getInt(32);
    int var14 = var25.getInt(32);
    int var15 = var25.getInt(32);
    int var16 = var25.getInt(8);
         int[] var17 = new int[var16];
         int[] var18 = new int[var16];
    int var19 = 0;
         byte[] var20 = new byte[var16];
         byte[] var21 = new byte[1];

         for (int var22 = 0; var22 < var16; var22++) {
    int var23 = 0;
            if (dynamic_cast<RandomAccessFile*>(var0) != nullptr) {
               var23 = ((RandomAccessFile)var0).readByte() & 255;
            } else if (dynamic_cast<InputStream*>(var0) != nullptr) {
               var23 = ((InputStream)var0).read();
            } else if (dynamic_cast<byte*>(var0) != nullptr[]) {
    uint8_t var33 = ((byte[])var0)[var2++];
               var23 = var33 & 255;
            }

            var20[var22] = (byte)var23;
            var18[var22] = var23;
            var17[var22] = var19;
            var19 += var23;
         }

         byte[] var32 = nullptr;
         if (!var1) {
            var32 = new byte[var19];
            if (dynamic_cast<RandomAccessFile*>(var0) != nullptr) {
               ((RandomAccessFile)var0).readFully(var32);
            } else if (dynamic_cast<InputStream*>(var0) != nullptr) {
               readFully((InputStream)var0, var32);
            } else if (dynamic_cast<byte*>(var0) != nullptr[]) {
               System.arraycopy(var0, var2, var32, 0, var19);
            }
         }

         return std::make_shared<OggPage>(var27, var29, var30, var31, var11, var13, var14, var15, var17, var18, var19, var3, var20, var32);
      } catch (EOFException var24) {
         throw std::make_unique<EndOfOggStreamException>();
      }
   }

    static void readFully(InputStream var0, byte[] var1) {
    int var2 = 0;

      while (var2 < var1.length) {
    int var3 = var0.read(var1, var2, var1.length - var2);
         if (var3 == -1) {
            throw std::make_unique<EndOfOggStreamException>();
         }

         var2 += var3;
      }
   }

    long getAbsoluteGranulePosition() {
      return this.absoluteGranulePosition;
   }

    int getStreamSerialNumber() {
      return this.streamSerialNumber;
   }

    int getPageSequenceNumber() {
      return this.pageSequenceNumber;
   }

    int getPageCheckSum() {
      return this.pageCheckSum;
   }

    int getTotalLength() {
      return this.data != nullptr ? 27 + this.segmentTable.length + this.data.length : this.totalLength;
   }

   public byte[] getData() {
      return this.data;
   }

   public byte[] getHeader() {
      return this.header;
   }

   public byte[] getSegmentTable() {
      return this.segmentTable;
   }

   public int[] getSegmentOffsets() {
      return this.segmentOffsets;
   }

   public int[] getSegmentLengths() {
      return this.segmentLengths;
   }

    bool isContinued() {
      return this.continued;
   }

    bool isFresh() {
      return !this.continued;
   }

    bool isBos() {
      return this.bos;
   }

    bool isEos() {
      return this.eos;
   }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
