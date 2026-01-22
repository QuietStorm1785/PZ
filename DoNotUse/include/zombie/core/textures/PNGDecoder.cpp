#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/PNGDecoder/1.h"
#include "zombie/core/textures/PNGDecoder/Format.h"
#include "zombie/core/utils/BooleanGrid.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace textures {


class PNGDecoder {
public:
   private static const byte[] SIGNATURE = new byte[]{-119, 80, 78, 71, 13, 10, 26, 10};
    static const int IHDR = 1229472850;
    static const int PLTE = 1347179589;
    static const int tRNS = 1951551059;
    static const int IDAT = 1229209940;
    static const int IEND = 1229278788;
    static const uint8_t COLOR_GREYSCALE = 0;
    static const uint8_t COLOR_TRUECOLOR = 2;
    static const uint8_t COLOR_INDEXED = 3;
    static const uint8_t COLOR_GREYALPHA = 4;
    static const uint8_t COLOR_TRUEALPHA = 6;
    const InputStream input;
    const CRC32 crc;
   private const byte[] buffer;
    int chunkLength;
    int chunkType;
    int chunkRemaining;
    int width;
    int height;
    int bitdepth;
    int colorType;
    int bytesPerPixel;
   private byte[] palette;
   private byte[] paletteA;
   private byte[] transPixel;
    int maskM = 0;
    int maskID = 0;
    BooleanGrid mask;
    bool bDoMask = false;
    long readTotal = 0L;

    public PNGDecoder(InputStream var1, bool var2) {
      this.input = var1;
      this.crc = std::make_unique<CRC32>();
      this.buffer = new byte[4096];
      this.bDoMask = var2;
      this.readFully(this.buffer, 0, SIGNATURE.length);
      if (!checkSignature(this.buffer)) {
         throw IOException("Not a valid PNG file");
      } else {
         this.openChunk(1229472850);
         this.readIHDR();
         this.closeChunk();

         while (true) {
            this.openChunk();
            switch (this.chunkType) {
               case 1229209940:
                  if (this.colorType == 3 && this.palette == nullptr) {
                     throw IOException("Missing PLTE chunk");
                  }

                  if (var2) {
                     this.mask = std::make_shared<BooleanGrid>(this.width, this.height);
                  }

                  return;
               case 1347179589:
                  this.readPLTE();
                  break;
               case 1951551059:
                  this.readtRNS();
            }

            this.closeChunk();
         }
      }
   }

    int getHeight() {
      return this.height;
   }

    int getWidth() {
      return this.width;
   }

    bool hasAlphaChannel() {
      return this.colorType == 6 || this.colorType == 4;
   }

    bool hasAlpha() {
      return this.hasAlphaChannel() || this.paletteA != nullptr || this.transPixel != nullptr;
   }

    bool isRGB() {
      return this.colorType == 6 || this.colorType == 2 || this.colorType == 3;
   }

    void overwriteTRNS(uint8_t var1, uint8_t var2, uint8_t var3) {
      if (this.hasAlphaChannel()) {
         throw UnsupportedOperationException("image has an alpha channel");
      } else {
         byte[] var4 = this.palette;
         if (var4 == nullptr) {
            this.transPixel = new byte[]{0, var1, 0, var2, 0, var3};
         } else {
            this.paletteA = new byte[var4.length / 3];
    uint8_t var5 = 0;

            for (int var6 = 0; var5 < var4.length; var6++) {
               if (var4[var5] != var1 || var4[var5 + 1] != var2 || var4[var5 + 2] != var3) {
                  this.paletteA[var6] = -1;
               }

               var5 += 3;
            }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    Format decideTextureFormat(Format var1) {
      switch (this.colorType) {
         case 0:
            switch (1.$SwitchMap$zombie$core$textures$PNGDecoder$Format[var1.ordinal()]) {
               case 5:
               case 6:
    return var1;
               default:
                  return Format.LUMINANCE;
            }
         case 1:
         case 5:
         default:
            throw UnsupportedOperationException("Not yet implemented");
         case 2:
            switch (1.$SwitchMap$zombie$core$textures$PNGDecoder$Format[var1.ordinal()]) {
               case 1:
               case 2:
               case 3:
               case 4:
    return var1;
               default:
                  return Format.RGB;
            }
         case 3:
            switch (1.$SwitchMap$zombie$core$textures$PNGDecoder$Format[var1.ordinal()]) {
               case 1:
               case 2:
               case 3:
    return var1;
               default:
                  return Format.RGBA;
            }
         case 4:
            return Format.LUMINANCE_ALPHA;
         case 6:
            switch (1.$SwitchMap$zombie$core$textures$PNGDecoder$Format[var1.ordinal()]) {
               case 1:
               case 2:
               case 3:
               case 4:
    return var1;
               default:
                  return Format.RGBA;
            }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void decode(ByteBuffer var1, int var2, Format var3) {
    int var4 = var1.position();
    int var5 = (this.width * this.bitdepth + 7) / 8 * this.bytesPerPixel;
      byte[] var6 = new byte[var5 + 1];
      byte[] var7 = new byte[var5 + 1];
      byte[] var8 = this.bitdepth < 8 ? new byte[this.width + 1] : nullptr;
      this.maskM = 0;
    Inflater var9 = std::make_shared<Inflater>();

      try {
         for (int var10 = 0; var10 < this.height; var10++) {
            this.readChunkUnzip(var9, var6, 0, var6.length);
            this.unfilter(var6, var7);
            var1.position(var4 + var10 * var2);
            label81:
            switch (this.colorType) {
               case 0:
                  switch (1.$SwitchMap$zombie$core$textures$PNGDecoder$Format[var3.ordinal()]) {
                     case 2:
                        this.copyGREYtoRGBA(var1, var6);
    break label81;
                     case 3:
                     case 4:
                     default:
                        throw UnsupportedOperationException("Unsupported format for this image");
                     case 5:
                     case 6:
                        this.copy(var1, var6);
    break label81;
                  }
               case 1:
               case 5:
               default:
                  throw UnsupportedOperationException("Not yet implemented");
               case 2:
                  switch (1.$SwitchMap$zombie$core$textures$PNGDecoder$Format[var3.ordinal()]) {
                     case 1:
                        this.copyRGBtoABGR(var1, var6);
    break label81;
                     case 2:
                        this.copyRGBtoRGBA(var1, var6);
    break label81;
                     case 3:
                        this.copyRGBtoBGRA(var1, var6);
    break label81;
                     case 4:
                        this.copy(var1, var6);
    break label81;
                     default:
                        throw UnsupportedOperationException("Unsupported format for this image");
                  }
               case 3:
                  switch (this.bitdepth) {
                     case 1:
                        this.expand1(var6, var8);
                        break;
                     case 2:
                        this.expand2(var6, var8);
                        break;
                     case 3:
                     case 5:
                     case 6:
                     case 7:
                     default:
                        throw UnsupportedOperationException("Unsupported bitdepth for this image");
                     case 4:
                        this.expand4(var6, var8);
                        break;
                     case 8:
                        var8 = var6;
                  }

                  switch (1.$SwitchMap$zombie$core$textures$PNGDecoder$Format[var3.ordinal()]) {
                     case 1:
                        this.copyPALtoABGR(var1, var8);
    break label81;
                     case 2:
                        this.copyPALtoRGBA(var1, var8);
    break label81;
                     case 3:
                        this.copyPALtoBGRA(var1, var8);
    break label81;
                     default:
                        throw UnsupportedOperationException("Unsupported format for this image");
                  }
               case 4:
                  switch (1.$SwitchMap$zombie$core$textures$PNGDecoder$Format[var3.ordinal()]) {
                     case 2:
                        this.copyGREYALPHAtoRGBA(var1, var6);
    break label81;
                     case 7:
                        this.copy(var1, var6);
    break label81;
                     default:
                        throw UnsupportedOperationException("Unsupported format for this image");
                  }
               case 6:
                  switch (1.$SwitchMap$zombie$core$textures$PNGDecoder$Format[var3.ordinal()]) {
                     case 1:
                        this.copyRGBAtoABGR(var1, var6);
                        break;
                     case 2:
                        this.copy(var1, var6);
                        break;
                     case 3:
                        this.copyRGBAtoBGRA(var1, var6);
                        break;
                     case 4:
                        this.copyRGBAtoRGB(var1, var6);
                        break;
                     default:
                        throw UnsupportedOperationException("Unsupported format for this image");
                  }
            }

            byte[] var11 = var6;
            var6 = var7;
            var7 = var11;
         }
      } finally {
         var9.end();
      }
   }

    void decodeFlipped(ByteBuffer var1, int var2, Format var3) {
      if (var2 <= 0) {
         throw IllegalArgumentException("stride");
      } else {
    int var4 = var1.position();
    int var5 = (this.height - 1) * var2;
         var1.position(var4 + var5);
         this.decode(var1, -var2, var3);
         var1.position(var1.position() + var5);
      }
   }

    void copy(ByteBuffer var1, byte[] var2) {
      if (this.bDoMask) {
    uint8_t var3 = 1;

         for (int var4 = var2.length; var3 < var4; var3 += 4) {
            if (var2[var3 + 3] % 255 != 0) {
               this.mask.setValue(this.maskM % this.width, this.maskM / this.width, true);
            }

            this.maskM++;
         }
      }

      var1.put(var2, 1, var2.length - 1);
   }

    void copyRGBtoABGR(ByteBuffer var1, byte[] var2) {
      if (this.transPixel != nullptr) {
    uint8_t var3 = this.transPixel[1];
    uint8_t var4 = this.transPixel[3];
    uint8_t var5 = this.transPixel[5];
    uint8_t var6 = 1;

         for (int var7 = var2.length; var6 < var7; var6 += 3) {
    uint8_t var8 = var2[var6];
    uint8_t var9 = var2[var6 + 1];
    uint8_t var10 = var2[var6 + 2];
    uint8_t var11 = -1;
            if (var8 == var3 && var9 == var4 && var10 == var5) {
               var11 = 0;
            }

            var1.put(var11).put(var10).put(var9).put(var8);
         }
      } else {
    uint8_t var12 = 1;

         for (int var13 = var2.length; var12 < var13; var12 += 3) {
            var1.put((byte)-1).put(var2[var12 + 2]).put(var2[var12 + 1]).put(var2[var12]);
         }
      }
   }

    void copyRGBtoRGBA(ByteBuffer var1, byte[] var2) {
      if (this.transPixel != nullptr) {
    uint8_t var3 = this.transPixel[1];
    uint8_t var4 = this.transPixel[3];
    uint8_t var5 = this.transPixel[5];
    uint8_t var6 = 1;

         for (int var7 = var2.length; var6 < var7; var6 += 3) {
    uint8_t var8 = var2[var6];
    uint8_t var9 = var2[var6 + 1];
    uint8_t var10 = var2[var6 + 2];
    uint8_t var11 = -1;
            if (var8 == var3 && var9 == var4 && var10 == var5) {
               var11 = 0;
            }

            if (this.bDoMask && var11 == 0) {
               this.mask.setValue(this.maskID % this.width, this.maskID / this.width, true);
               this.maskID++;
            }

            var1.put(var8).put(var9).put(var10).put(var11);
         }
      } else {
    uint8_t var12 = 1;

         for (int var13 = var2.length; var12 < var13; var12 += 3) {
            var1.put(var2[var12]).put(var2[var12 + 1]).put(var2[var12 + 2]).put((byte)-1);
         }
      }
   }

    void copyRGBtoBGRA(ByteBuffer var1, byte[] var2) {
      if (this.transPixel != nullptr) {
    uint8_t var3 = this.transPixel[1];
    uint8_t var4 = this.transPixel[3];
    uint8_t var5 = this.transPixel[5];
    uint8_t var6 = 1;

         for (int var7 = var2.length; var6 < var7; var6 += 3) {
    uint8_t var8 = var2[var6];
    uint8_t var9 = var2[var6 + 1];
    uint8_t var10 = var2[var6 + 2];
    uint8_t var11 = -1;
            if (var8 == var3 && var9 == var4 && var10 == var5) {
               var11 = 0;
            }

            var1.put(var10).put(var9).put(var8).put(var11);
         }
      } else {
    uint8_t var12 = 1;

         for (int var13 = var2.length; var12 < var13; var12 += 3) {
            var1.put(var2[var12 + 2]).put(var2[var12 + 1]).put(var2[var12]).put((byte)-1);
         }
      }
   }

    void copyRGBAtoABGR(ByteBuffer var1, byte[] var2) {
    uint8_t var3 = 1;

      for (int var4 = var2.length; var3 < var4; var3 += 4) {
         var1.put(var2[var3 + 3]).put(var2[var3 + 2]).put(var2[var3 + 1]).put(var2[var3]);
      }
   }

    void copyRGBAtoBGRA(ByteBuffer var1, byte[] var2) {
    uint8_t var3 = 1;

      for (int var4 = var2.length; var3 < var4; var3 += 4) {
         var1.put(var2[var3 + 2]).put(var2[var3 + 1]).put(var2[var3]).put(var2[var3 + 3]);
      }
   }

    void copyRGBAtoRGB(ByteBuffer var1, byte[] var2) {
    uint8_t var3 = 1;

      for (int var4 = var2.length; var3 < var4; var3 += 4) {
         var1.put(var2[var3]).put(var2[var3 + 1]).put(var2[var3 + 2]);
      }
   }

    void copyPALtoABGR(ByteBuffer var1, byte[] var2) {
      if (this.paletteA != nullptr) {
    int var3 = 1;

         for (int var4 = var2.length; var3 < var4; var3++) {
    int var5 = var2[var3] & 255;
    uint8_t var6 = this.palette[var5 * 3 + 0];
    uint8_t var7 = this.palette[var5 * 3 + 1];
    uint8_t var8 = this.palette[var5 * 3 + 2];
    uint8_t var9 = this.paletteA[var5];
            var1.put(var9).put(var8).put(var7).put(var6);
         }
      } else {
    int var10 = 1;

         for (int var11 = var2.length; var10 < var11; var10++) {
    int var12 = var2[var10] & 255;
    uint8_t var13 = this.palette[var12 * 3 + 0];
    uint8_t var14 = this.palette[var12 * 3 + 1];
    uint8_t var15 = this.palette[var12 * 3 + 2];
    uint8_t var16 = -1;
            var1.put(var16).put(var15).put(var14).put(var13);
         }
      }
   }

    void copyPALtoRGBA(ByteBuffer var1, byte[] var2) {
      if (this.paletteA != nullptr) {
    int var3 = 1;

         for (int var4 = var2.length; var3 < var4; var3++) {
    int var5 = var2[var3] & 255;
    uint8_t var6 = this.palette[var5 * 3 + 0];
    uint8_t var7 = this.palette[var5 * 3 + 1];
    uint8_t var8 = this.palette[var5 * 3 + 2];
    uint8_t var9 = this.paletteA[var5];
            var1.put(var6).put(var7).put(var8).put(var9);
         }
      } else {
    int var10 = 1;

         for (int var11 = var2.length; var10 < var11; var10++) {
    int var12 = var2[var10] & 255;
    uint8_t var13 = this.palette[var12 * 3 + 0];
    uint8_t var14 = this.palette[var12 * 3 + 1];
    uint8_t var15 = this.palette[var12 * 3 + 2];
    uint8_t var16 = -1;
            var1.put(var13).put(var14).put(var15).put(var16);
         }
      }
   }

    void copyPALtoBGRA(ByteBuffer var1, byte[] var2) {
      if (this.paletteA != nullptr) {
    int var3 = 1;

         for (int var4 = var2.length; var3 < var4; var3++) {
    int var5 = var2[var3] & 255;
    uint8_t var6 = this.palette[var5 * 3 + 0];
    uint8_t var7 = this.palette[var5 * 3 + 1];
    uint8_t var8 = this.palette[var5 * 3 + 2];
    uint8_t var9 = this.paletteA[var5];
            var1.put(var8).put(var7).put(var6).put(var9);
         }
      } else {
    int var10 = 1;

         for (int var11 = var2.length; var10 < var11; var10++) {
    int var12 = var2[var10] & 255;
    uint8_t var13 = this.palette[var12 * 3 + 0];
    uint8_t var14 = this.palette[var12 * 3 + 1];
    uint8_t var15 = this.palette[var12 * 3 + 2];
    uint8_t var16 = -1;
            var1.put(var15).put(var14).put(var13).put(var16);
         }
      }
   }

    void copyGREYtoRGBA(ByteBuffer var1, byte[] var2) {
    int var3 = 1;

      for (int var4 = var2.length; var3 < var4; var3++) {
    uint8_t var5 = var2[var3];
    uint8_t var6 = -1;
         var1.put(var5).put(var5).put(var5).put(var6);
      }
   }

    void copyGREYALPHAtoRGBA(ByteBuffer var1, byte[] var2) {
    uint8_t var3 = 1;

      for (int var4 = var2.length; var3 < var4; var3 += 2) {
    uint8_t var5 = var2[var3];
    uint8_t var6 = var2[var3 + 1];
         var1.put(var5).put(var5).put(var5).put(var6);
      }
   }

    void expand4(byte[] var1, byte[] var2) {
    uint8_t var3 = 1;

      for (int var4 = var2.length; var3 < var4; var3 += 2) {
    int var5 = var1[1 + (var3 >> 1)] & 255;
         switch (var4 - var3) {
            default:
               var2[var3 + 1] = (byte)(var5 & 15);
            case 1:
               var2[var3] = (byte)(var5 >> 4);
         }
      }
   }

    void expand2(byte[] var1, byte[] var2) {
    uint8_t var3 = 1;

      for (int var4 = var2.length; var3 < var4; var3 += 4) {
    int var5 = var1[1 + (var3 >> 2)] & 255;
         switch (var4 - var3) {
            default:
               var2[var3 + 3] = (byte)(var5 & 3);
            case 3:
               var2[var3 + 2] = (byte)(var5 >> 2 & 3);
            case 2:
               var2[var3 + 1] = (byte)(var5 >> 4 & 3);
            case 1:
               var2[var3] = (byte)(var5 >> 6);
         }
      }
   }

    void expand1(byte[] var1, byte[] var2) {
    uint8_t var3 = 1;

      for (int var4 = var2.length; var3 < var4; var3 += 8) {
    int var5 = var1[1 + (var3 >> 3)] & 255;
         switch (var4 - var3) {
            default:
               var2[var3 + 7] = (byte)(var5 & 1);
            case 7:
               var2[var3 + 6] = (byte)(var5 >> 1 & 1);
            case 6:
               var2[var3 + 5] = (byte)(var5 >> 2 & 1);
            case 5:
               var2[var3 + 4] = (byte)(var5 >> 3 & 1);
            case 4:
               var2[var3 + 3] = (byte)(var5 >> 4 & 1);
            case 3:
               var2[var3 + 2] = (byte)(var5 >> 5 & 1);
            case 2:
               var2[var3 + 1] = (byte)(var5 >> 6 & 1);
            case 1:
               var2[var3] = (byte)(var5 >> 7);
         }
      }
   }

    void unfilter(byte[] var1, byte[] var2) {
      switch (var1[0]) {
         case 0:
            break;
         case 1:
            this.unfilterSub(var1);
            break;
         case 2:
            this.unfilterUp(var1, var2);
            break;
         case 3:
            this.unfilterAverage(var1, var2);
            break;
         case 4:
            this.unfilterPaeth(var1, var2);
            break;
         default:
            throw IOException("invalide filter type in scanline: " + var1[0]);
      }
   }

    void unfilterSub(byte[] var1) {
    int var2 = this.bytesPerPixel;
    int var3 = var2 + 1;

      for (int var4 = var1.length; var3 < var4; var3++) {
         var1[var3] += var1[var3 - var2];
      }
   }

    void unfilterUp(byte[] var1, byte[] var2) {
    int var3 = this.bytesPerPixel;
    int var4 = 1;

      for (int var5 = var1.length; var4 < var5; var4++) {
         var1[var4] += var2[var4];
      }
   }

    void unfilterAverage(byte[] var1, byte[] var2) {
    int var3 = this.bytesPerPixel;

    int var4;
      for (var4 = 1; var4 <= var3; var4++) {
         var1[var4] += (byte)((var2[var4] & 255) >>> 1);
      }

      for (int var5 = var1.length; var4 < var5; var4++) {
         var1[var4] += (byte)((var2[var4] & 255) + (var1[var4 - var3] & 255) >>> 1);
      }
   }

    void unfilterPaeth(byte[] var1, byte[] var2) {
    int var3 = this.bytesPerPixel;

    int var4;
      for (var4 = 1; var4 <= var3; var4++) {
         var1[var4] += var2[var4];
      }

      for (int var5 = var1.length; var4 < var5; var4++) {
    int var6 = var1[var4 - var3] & 255;
    int var7 = var2[var4] & 255;
    int var8 = var2[var4 - var3] & 255;
    int var9 = var6 + var7 - var8;
    int var10 = var9 - var6;
         if (var10 < 0) {
            var10 = -var10;
         }

    int var11 = var9 - var7;
         if (var11 < 0) {
            var11 = -var11;
         }

    int var12 = var9 - var8;
         if (var12 < 0) {
            var12 = -var12;
         }

         if (var10 <= var11 && var10 <= var12) {
            var8 = var6;
         } else if (var11 <= var12) {
            var8 = var7;
         }

         var1[var4] += (byte)var8;
      }
   }

    void readIHDR() {
      this.checkChunkLength(13);
      this.readChunk(this.buffer, 0, 13);
      this.width = this.readInt(this.buffer, 0);
      this.height = this.readInt(this.buffer, 4);
      this.bitdepth = this.buffer[8] & 255;
      this.colorType = this.buffer[9] & 255;
      label43:
      switch (this.colorType) {
         case 0:
            if (this.bitdepth != 8) {
               throw IOException("Unsupported bit depth: " + this.bitdepth);
            }

            this.bytesPerPixel = 1;
            break;
         case 1:
         case 5:
         default:
            throw IOException("unsupported color format: " + this.colorType);
         case 2:
            if (this.bitdepth != 8) {
               throw IOException("Unsupported bit depth: " + this.bitdepth);
            }

            this.bytesPerPixel = 3;
            break;
         case 3:
            switch (this.bitdepth) {
               case 1:
               case 2:
               case 4:
               case 8:
                  this.bytesPerPixel = 1;
    break label43;
               case 3:
               case 5:
               case 6:
               case 7:
               default:
                  throw IOException("Unsupported bit depth: " + this.bitdepth);
            }
         case 4:
            if (this.bitdepth != 8) {
               throw IOException("Unsupported bit depth: " + this.bitdepth);
            }

            this.bytesPerPixel = 2;
            break;
         case 6:
            if (this.bitdepth != 8) {
               throw IOException("Unsupported bit depth: " + this.bitdepth);
            }

            this.bytesPerPixel = 4;
      }

      if (this.buffer[10] != 0) {
         throw IOException("unsupported compression method");
      } else if (this.buffer[11] != 0) {
         throw IOException("unsupported filtering method");
      } else if (this.buffer[12] != 0) {
         throw IOException("unsupported interlace method");
      }
   }

    void readPLTE() {
    int var1 = this.chunkLength / 3;
      if (var1 >= 1 && var1 <= 256 && this.chunkLength % 3 == 0) {
         this.palette = new byte[var1 * 3];
         this.readChunk(this.palette, 0, this.palette.length);
      } else {
         throw IOException("PLTE chunk has wrong length");
      }
   }

    void readtRNS() {
      switch (this.colorType) {
         case 0:
            this.checkChunkLength(2);
            this.transPixel = new byte[2];
            this.readChunk(this.transPixel, 0, 2);
         case 1:
         default:
            break;
         case 2:
            this.checkChunkLength(6);
            this.transPixel = new byte[6];
            this.readChunk(this.transPixel, 0, 6);
            break;
         case 3:
            if (this.palette == nullptr) {
               throw IOException("tRNS chunk without PLTE chunk");
            }

            this.paletteA = new byte[this.palette.length / 3];
            Arrays.fill(this.paletteA, (byte)-1);
            this.readChunk(this.paletteA, 0, this.paletteA.length);
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

    void refillInflater(Inflater var1) {
      while (this.chunkRemaining == 0) {
         this.closeChunk();
         this.openChunk(1229209940);
      }

    int var2 = this.readChunk(this.buffer, 0, this.buffer.length);
      var1.setInput(this.buffer, 0, var2);
   }

    void readChunkUnzip(Inflater var1, byte[] var2, int var3, int var4) {
      assert var2 != this.buffer;

      try {
         do {
    int var5 = var1.inflate(var2, var3, var4);
            if (var5 <= 0) {
               if (var1.finished()) {
                  throw std::make_unique<EOFException>();
               }

               if (!var1.needsInput()) {
                  throw IOException("Can't inflate " + var4 + " bytes");
               }

               this.refillInflater(var1);
            } else {
               var3 += var5;
               var4 -= var5;
            }
         } while (var4 > 0);
      } catch (DataFormatException var6) {
         throw (IOException)std::make_shared<IOException>("inflate error").initCause(var6);
      }
   }

    void readFully(byte[] var1, int var2, int var3) {
      do {
    int var4 = this.input.read(var1, var2, var3);
         if (var4 < 0) {
            throw std::make_unique<EOFException>();
         }

         var2 += var4;
         var3 -= var4;
         this.readTotal += var4;
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

    static bool checkSignature(byte[] var0) {
      for (int var1 = 0; var1 < SIGNATURE.length; var1++) {
         if (var0[var1] != SIGNATURE[var1]) {
    return false;
         }
      }

    return true;
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
