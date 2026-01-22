#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/evildevil/engines/bubble/texture/DDSLoader.h"
#include "java/awt/image/BufferedImage.h"
#include "java/awt/image/Raster.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/textures/ImageData/L_generateMipMaps.h"
#include "zombie/core/textures/ImageData/L_performAlphaPadding.h"
#include "zombie/core/textures/PNGDecoder/Format.h"
#include "zombie/core/textures/Texture/PZFileformat.h"
#include "zombie/core/utils/BooleanGrid.h"
#include "zombie/core/utils/DirectBufferAllocator.h"
#include "zombie/core/utils/ImageUtils.h"
#include "zombie/core/utils/WrappedBuffer.h"
#include "zombie/core/znet/SteamFriends.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace textures {


class ImageData {
public:
    static const long serialVersionUID = -7893392091273534932L;
    MipMapLevel data;
   private MipMapLevel[] mipMaps;
    int height;
    int heightHW;
    bool solid = true;
    int width;
    int widthHW;
    int mipMapCount = -1;
    bool alphaPaddingDone = false;
    bool bPreserveTransparentColor = false;
    BooleanGrid mask;
    static const int BufferSize = 67108864;
    static const DDSLoader dds = std::make_shared<DDSLoader>();
    int id = -1;
    static const int MIP_LEVEL_IDX_OFFSET = 0;
   private static const ThreadLocal<L_generateMipMaps> TL_generateMipMaps = ThreadLocal.withInitial(L_generateMipMaps::new);
   private static const ThreadLocal<L_performAlphaPadding> TL_performAlphaPadding = ThreadLocal.withInitial(L_performAlphaPadding::new);

    public ImageData(TextureID var1, WrappedBuffer var2) {
      this.data = std::make_shared<MipMapLevel>(var1.widthHW, var1.heightHW, var2);
      this.width = var1.width;
      this.widthHW = var1.widthHW;
      this.height = var1.height;
      this.heightHW = var1.heightHW;
      this.solid = var1.solid;
   }

    public ImageData(const std::string& var1) {
      if (var1.contains(".txt")) {
         var1 = var1.replace(".txt", ".png");
      }

      var1 = Texture.processFilePath(var1);
      var1 = ZomboidFileSystem.instance.getString(var1);

      try (
    FileInputStream var2 = std::make_shared<FileInputStream>(var1);
    BufferedInputStream var3 = std::make_shared<BufferedInputStream>(var2);
      ) {
    PNGDecoder var4 = std::make_shared<PNGDecoder>(var3, false);
         this.width = var4.getWidth();
         this.height = var4.getHeight();
         this.widthHW = ImageUtils.getNextPowerOfTwoHW(this.width);
         this.heightHW = ImageUtils.getNextPowerOfTwoHW(this.height);
         this.data = std::make_shared<MipMapLevel>(this.widthHW, this.heightHW);
    ByteBuffer var5 = this.data.getBuffer();
         var5.rewind();
    int var6 = this.widthHW * 4;
         if (this.width != this.widthHW) {
            for (int var7 = this.width * 4; var7 < this.widthHW * 4; var7++) {
               for (int var8 = 0; var8 < this.heightHW; var8++) {
                  var5.put(var7 + var8 * var6, (byte)0);
               }
            }
         }

         if (this.height != this.heightHW) {
            for (int var16 = this.height; var16 < this.heightHW; var16++) {
               for (int var17 = 0; var17 < this.width * 4; var17++) {
                  var5.put(var17 + var16 * var6, (byte)0);
               }
            }
         }

         var4.decode(this.data.getBuffer(), var6, Format.RGBA);
      } catch (Exception var13) {
         this.dispose();
         this.width = this.height = -1;
      }
   }

    public ImageData(int var1, int var2) {
      this.width = var1;
      this.height = var2;
      this.widthHW = ImageUtils.getNextPowerOfTwoHW(var1);
      this.heightHW = ImageUtils.getNextPowerOfTwoHW(var2);
      this.data = std::make_shared<MipMapLevel>(this.widthHW, this.heightHW);
   }

    public ImageData(int var1, int var2, WrappedBuffer var3) {
      this.width = var1;
      this.height = var2;
      this.widthHW = ImageUtils.getNextPowerOfTwoHW(var1);
      this.heightHW = ImageUtils.getNextPowerOfTwoHW(var2);
      this.data = std::make_shared<MipMapLevel>(this.widthHW, this.heightHW, var3);
   }

   ImageData(std::string var1, std::string var2) {
    Pcx var3 = std::make_shared<Pcx>(var1, var2);
      this.width = var3.imageWidth;
      this.height = var3.imageHeight;
      this.widthHW = ImageUtils.getNextPowerOfTwoHW(this.width);
      this.heightHW = ImageUtils.getNextPowerOfTwoHW(this.height);
      this.data = std::make_shared<MipMapLevel>(this.widthHW, this.heightHW);
      this.setData(var3);
      this.makeTransp((byte)var3.palette[762], (byte)var3.palette[763], (byte)var3.palette[764], (byte)0);
   }

   ImageData(std::string var1, int[] var2) {
    Pcx var3 = std::make_shared<Pcx>(var1, var2);
      this.width = var3.imageWidth;
      this.height = var3.imageHeight;
      this.widthHW = ImageUtils.getNextPowerOfTwoHW(this.width);
      this.heightHW = ImageUtils.getNextPowerOfTwoHW(this.height);
      this.data = std::make_shared<MipMapLevel>(this.widthHW, this.heightHW);
      this.setData(var3);
      this.makeTransp((byte)var3.palette[762], (byte)var3.palette[763], (byte)var3.palette[764], (byte)0);
   }

    public ImageData(BufferedInputStream var1, bool var2, PZFileformat var3) {
      if (var3 == PZFileformat.DDS) {
         RenderThread.invokeOnRenderContext(() -> this.id = dds.loadDDSFile(var1));
         this.width = DDSLoader.lastWid;
         this.height = DDSLoader.lastHei;
         this.widthHW = ImageUtils.getNextPowerOfTwoHW(this.width);
         this.heightHW = ImageUtils.getNextPowerOfTwoHW(this.height);
      }
   }

    public ImageData(InputStream var1, bool var2) {
    void* var3 = nullptr;
    PNGDecoder var4 = std::make_shared<PNGDecoder>(var1, var2);
      this.width = var4.getWidth();
      this.height = var4.getHeight();
      this.widthHW = ImageUtils.getNextPowerOfTwoHW(this.width);
      this.heightHW = ImageUtils.getNextPowerOfTwoHW(this.height);
      this.data = std::make_shared<MipMapLevel>(this.widthHW, this.heightHW);
      this.data.rewind();
      var4.decode(this.data.getBuffer(), 4 * this.widthHW, Format.RGBA);
      if (var2) {
         this.mask = var4.mask;
      }
   }

    static ImageData createSteamAvatar(long var0) {
    WrappedBuffer var2 = DirectBufferAllocator.allocate(65536);
    int var3 = SteamFriends.CreateSteamAvatar(var0, var2.getBuffer());
      if (var3 <= 0) {
    return nullptr;
      } else {
    int var4 = var2.getBuffer().position() / (var3 * 4);
         var2.getBuffer().flip();
         return std::make_shared<ImageData>(var3, var4, var2);
      }
   }

    MipMapLevel getData() {
      if (this.data == nullptr) {
         this.data = std::make_shared<MipMapLevel>(this.widthHW, this.heightHW, DirectBufferAllocator.allocate(67108864));
      }

      this.data.rewind();
      return this.data;
   }

    void makeTransp(uint8_t var1, uint8_t var2, uint8_t var3) {
      this.makeTransp(var1, var2, var3, (byte)0);
   }

    void makeTransp(uint8_t var1, uint8_t var2, uint8_t var3, uint8_t var4) {
      this.solid = false;
    ByteBuffer var5 = this.data.getBuffer();
      var5.rewind();
    int var10 = this.widthHW * 4;

      for (int var11 = 0; var11 < this.heightHW; var11++) {
    int var9 = var5.position();

         for (int var12 = 0; var12 < this.widthHW; var12++) {
    uint8_t var6 = var5.get();
    uint8_t var7 = var5.get();
    uint8_t var8 = var5.get();
            if (var6 == var1 && var7 == var2 && var8 == var3) {
               var5.put(var4);
            } else {
               var5.get();
            }

            if (var12 == this.width) {
               var5.position(var9 + var10);
               break;
            }
         }

         if (var11 == this.height) {
            break;
         }
      }

      var5.rewind();
   }

    void setData(BufferedImage var1) {
      if (var1 != nullptr) {
         this.setData(var1.getData());
      }
   }

    void setData(Raster var1) {
      if (var1 == nullptr) {
    std::make_shared<Exception>();
      } else {
         this.width = var1.getWidth();
         this.height = var1.getHeight();
         if (this.width <= this.widthHW && this.height <= this.heightHW) {
            int[] var2 = var1.getPixels(0, 0, this.width, this.height, (int[])nullptr);
    ByteBuffer var3 = this.data.getBuffer();
            var3.rewind();
    int var4 = 0;
    int var5 = var3.position();
    int var6 = this.widthHW * 4;

            for (int var7 = 0; var7 < var2.length; var7++) {
               if (++var4 > this.width) {
                  var3.position(var5 + var6);
                  var5 = var3.position();
                  var4 = 1;
               }

               var3.put((byte)var2[var7]);
               var3.put((byte)var2[++var7]);
               var3.put((byte)var2[++var7]);
               var3.put((byte)var2[++var7]);
            }

            var3.rewind();
            this.solid = false;
         } else {
    std::make_shared<Exception>();
         }
      }
   }

    void readObject(ObjectInputStream var1) {
      var1.defaultReadObject();
      this.data = std::make_shared<MipMapLevel>(this.widthHW, this.heightHW);
    ByteBuffer var2 = this.data.getBuffer();

      for (int var3 = 0; var3 < this.widthHW * this.heightHW; var3++) {
         var2.put(var1.readByte()).put(var1.readByte()).put(var1.readByte()).put(var1.readByte());
      }

      var2.flip();
   }

    void setData(Pcx var1) {
      this.width = var1.imageWidth;
      this.height = var1.imageHeight;
      if (this.width <= this.widthHW && this.height <= this.heightHW) {
    ByteBuffer var2 = this.data.getBuffer();
         var2.rewind();
    int var3 = 0;
    int var4 = var2.position();
    int var5 = this.widthHW * 4;

         for (int var6 = 0; var6 < this.heightHW * this.widthHW * 3; var6++) {
            if (++var3 > this.width) {
               var4 = var2.position();
               var3 = 1;
            }

            var2.put(var1.imageData[var6]);
            var2.put(var1.imageData[++var6]);
            var2.put(var1.imageData[++var6]);
            var2.put((byte)-1);
         }

         var2.rewind();
         this.solid = false;
      } else {
    std::make_shared<Exception>();
      }
   }

    void writeObject(ObjectOutputStream var1) {
      var1.defaultWriteObject();
    ByteBuffer var2 = this.data.getBuffer();
      var2.rewind();

      for (int var3 = 0; var3 < this.widthHW * this.heightHW; var3++) {
         var1.writeByte(var2.get());
         var1.writeByte(var2.get());
         var1.writeByte(var2.get());
         var1.writeByte(var2.get());
      }
   }

    int getHeight() {
      return this.height;
   }

    int getHeightHW() {
      return this.heightHW;
   }

    bool isSolid() {
      return this.solid;
   }

    int getWidth() {
      return this.width;
   }

    int getWidthHW() {
      return this.widthHW;
   }

    int getMipMapCount() {
      if (this.data == nullptr) {
    return 0;
      } else {
         if (this.mipMapCount < 0) {
            this.mipMapCount = calculateNumMips(this.widthHW, this.heightHW);
         }

         return this.mipMapCount;
      }
   }

    MipMapLevel getMipMapData(int var1) {
      if (this.data != nullptr && !this.alphaPaddingDone) {
         this.performAlphaPadding();
      }

      if (var1 == 0) {
         return this.getData();
      } else {
         if (this.mipMaps == nullptr) {
            this.generateMipMaps();
         }

    int var2 = var1 - 1;
    MipMapLevel var3 = this.mipMaps[var2];
         var3.rewind();
    return var3;
      }
   }

    void initMipMaps() {
    int var1 = this.getMipMapCount();
    int var2 = PZMath.min(0, var1 - 1);
    int var3 = var1;

      for (int var4 = var2; var4 < var3; var4++) {
    MipMapLevel var5 = this.getMipMapData(var4);
      }
   }

    void dispose() {
      if (this.data != nullptr) {
         this.data.dispose();
         this.data = nullptr;
      }

      if (this.mipMaps != nullptr) {
         for (int var1 = 0; var1 < this.mipMaps.length; var1++) {
            this.mipMaps[var1].dispose();
            this.mipMaps[var1] = nullptr;
         }

         this.mipMaps = nullptr;
      }
   }

    void generateMipMaps() {
      this.mipMapCount = calculateNumMips(this.widthHW, this.heightHW);
    int var1 = this.mipMapCount - 1;
      this.mipMaps = new MipMapLevel[var1];
    MipMapLevel var2 = this.getData();
    int var3 = this.widthHW;
    int var4 = this.heightHW;
    MipMapLevel var5 = var2;
    int var8 = getNextMipDimension(var3);
    int var9 = getNextMipDimension(var4);

      for (int var10 = 0; var10 < var1; var10++) {
    MipMapLevel var11 = std::make_shared<MipMapLevel>(var8, var9);
         if (var10 < 2) {
            this.scaleMipLevelMaxAlpha(var5, var11, var10);
         } else {
            this.scaleMipLevelAverage(var5, var11, var10);
         }

         this.performAlphaPadding(var11);
         this.mipMaps[var10] = var11;
         var5 = var11;
         var8 = getNextMipDimension(var8);
         var9 = getNextMipDimension(var9);
      }
   }

    void scaleMipLevelMaxAlpha(MipMapLevel var1, MipMapLevel var2, int var3) {
    L_generateMipMaps var4 = TL_generateMipMaps.get();
    ByteBuffer var5 = var2.getBuffer();
      var5.rewind();
    int var6 = var1.width;
    int var7 = var1.height;
    ByteBuffer var8 = var1.getBuffer();
    int var9 = var2.width;
    int var10 = var2.height;

      for (int var11 = 0; var11 < var10; var11++) {
         for (int var12 = 0; var12 < var9; var12++) {
            int[] var13 = var4.pixelBytes;
            int[] var14 = var4.originalPixel;
            int[] var15 = var4.resultPixelBytes;
            getPixelClamped(var8, var6, var7, var12 * 2, var11 * 2, var14);
    uint8_t var16;
            if (!this.bPreserveTransparentColor && var14[3] <= 0) {
               PZArrayUtil.arraySet(var15, 0);
               var16 = 0;
            } else {
               PZArrayUtil.arrayCopy(var15, var14, 0, 4);
               var16 = 1;
            }

            var16 += this.sampleNeighborPixelDiscard(var8, var6, var7, var12 * 2 + 1, var11 * 2, var13, var15);
            var16 += this.sampleNeighborPixelDiscard(var8, var6, var7, var12 * 2, var11 * 2 + 1, var13, var15);
            var16 += this.sampleNeighborPixelDiscard(var8, var6, var7, var12 * 2 + 1, var11 * 2 + 1, var13, var15);
            if (var16 > 0) {
               var15[0] /= var16;
               var15[1] /= var16;
               var15[2] /= var16;
               var15[3] /= var16;
               if (DebugOptions.instance.IsoSprite.WorldMipmapColors.getValue()) {
                  setMipmapDebugColors(var3, var15);
               }
            }

            setPixel(var5, var9, var10, var12, var11, var15);
         }
      }
   }

    void scaleMipLevelAverage(MipMapLevel var1, MipMapLevel var2, int var3) {
    L_generateMipMaps var4 = TL_generateMipMaps.get();
    ByteBuffer var5 = var2.getBuffer();
      var5.rewind();
    int var6 = var1.width;
    int var7 = var1.height;
    ByteBuffer var8 = var1.getBuffer();
    int var9 = var2.width;
    int var10 = var2.height;

      for (int var11 = 0; var11 < var10; var11++) {
         for (int var12 = 0; var12 < var9; var12++) {
            int[] var13 = var4.resultPixelBytes;
    int var14 = 1;
            getPixelClamped(var8, var6, var7, var12 * 2, var11 * 2, var13);
            var14 += getPixelDiscard(var8, var6, var7, var12 * 2 + 1, var11 * 2, var13);
            var14 += getPixelDiscard(var8, var6, var7, var12 * 2, var11 * 2 + 1, var13);
            var14 += getPixelDiscard(var8, var6, var7, var12 * 2 + 1, var11 * 2 + 1, var13);
            var13[0] /= var14;
            var13[1] /= var14;
            var13[2] /= var14;
            var13[3] /= var14;
            if (var13[3] != 0 && DebugOptions.instance.IsoSprite.WorldMipmapColors.getValue()) {
               setMipmapDebugColors(var3, var13);
            }

            setPixel(var5, var9, var10, var12, var11, var13);
         }
      }
   }

    static int calculateNumMips(int var0, int var1) {
    int var2 = calculateNumMips(var0);
    int var3 = calculateNumMips(var1);
      return PZMath.max(var2, var3);
   }

    static int calculateNumMips(int var0) {
    int var1 = 0;

      for (int var2 = var0; var2 > 0; var1++) {
         var2 >>= 1;
      }

    return var1;
   }

    void performAlphaPadding() {
    MipMapLevel var1 = this.data;
      if (var1 != nullptr && var1.data != nullptr) {
         this.performAlphaPadding(var1);
         this.alphaPaddingDone = true;
      }
   }

    void performAlphaPadding(MipMapLevel var1) {
    L_performAlphaPadding var2 = TL_performAlphaPadding.get();
    ByteBuffer var3 = var1.getBuffer();
    int var4 = var1.width;
    int var5 = var1.height;

      for (int var6 = 0; var6 < var5; var6++) {
         for (int var7 = 0; var7 < var4; var7++) {
    int var8 = (var6 * var4 + var7) * 4;
    int var9 = var3.get(var8 + 3) & 255;
            if (var9 != 255 && var9 == 0) {
               int[] var10 = getPixelClamped(var3, var4, var5, var7, var6, var2.pixelRGBA);
               int[] var11 = var2.newPixelRGBA;
               PZArrayUtil.arraySet(var11, 0);
               var11[3] = var10[3];
    int var12 = 0;
               var12 += this.sampleNeighborPixelDiscard(var3, var4, var5, var7 - 1, var6, var2.pixelRGBA_neighbor, var11);
               var12 += this.sampleNeighborPixelDiscard(var3, var4, var5, var7, var6 - 1, var2.pixelRGBA_neighbor, var11);
               var12 += this.sampleNeighborPixelDiscard(var3, var4, var5, var7 - 1, var6 - 1, var2.pixelRGBA_neighbor, var11);
               var12 += this.sampleNeighborPixelDiscard(var3, var4, var5, var7 + 1, var6, var2.pixelRGBA_neighbor, var11);
               var12 += this.sampleNeighborPixelDiscard(var3, var4, var5, var7, var6 + 1, var2.pixelRGBA_neighbor, var11);
               var12 += this.sampleNeighborPixelDiscard(var3, var4, var5, var7 + 1, var6 + 1, var2.pixelRGBA_neighbor, var11);
               if (var12 > 0) {
                  var11[0] /= var12;
                  var11[1] /= var12;
                  var11[2] /= var12;
                  var11[3] = var10[3];
                  setPixel(var3, var4, var5, var7, var6, var11);
               }
            }
         }
      }
   }

    int sampleNeighborPixelDiscard(ByteBuffer var1, int var2, int var3, int var4, int var5, int[] var6, int[] var7) {
      if (var4 >= 0 && var4 < var2 && var5 >= 0 && var5 < var3) {
         getPixelClamped(var1, var2, var3, var4, var5, var6);
         if (var6[3] > 0) {
            var7[0] += var6[0];
            var7[1] += var6[1];
            var7[2] += var6[2];
            var7[3] += var6[3];
    return 1;
         } else {
    return 0;
         }
      } else {
    return 0;
      }
   }

    static int getPixelDiscard(ByteBuffer var0, int var1, int var2, int var3, int var4, int[] var5) {
      if (var3 >= 0 && var3 < var1 && var4 >= 0 && var4 < var2) {
    int var6 = (var3 + var4 * var1) * 4;
         var5[0] += var0.get(var6) & 255;
         var5[1] += var0.get(var6 + 1) & 255;
         var5[2] += var0.get(var6 + 2) & 255;
         var5[3] += var0.get(var6 + 3) & 255;
    return 1;
      } else {
    return 0;
      }
   }

   public static int[] getPixelClamped(ByteBuffer var0, int var1, int var2, int var3, int var4, int[] var5) {
      var3 = PZMath.clamp(var3, 0, var1 - 1);
      var4 = PZMath.clamp(var4, 0, var2 - 1);
    int var6 = (var3 + var4 * var1) * 4;
      var5[0] = var0.get(var6) & 255;
      var5[1] = var0.get(var6 + 1) & 255;
      var5[2] = var0.get(var6 + 2) & 255;
      var5[3] = var0.get(var6 + 3) & 255;
    return var5;
   }

    static void setPixel(ByteBuffer var0, int var1, int var2, int var3, int var4, int[] var5) {
    int var6 = (var3 + var4 * var1) * 4;
      var0.put(var6, (byte)(var5[0] & 0xFF));
      var0.put(var6 + 1, (byte)(var5[1] & 0xFF));
      var0.put(var6 + 2, (byte)(var5[2] & 0xFF));
      var0.put(var6 + 3, (byte)(var5[3] & 0xFF));
   }

    static int getNextMipDimension(int var0) {
      if (var0 > 1) {
         var0 >>= 1;
      }

    return var0;
   }

    static void setMipmapDebugColors(int var0, int[] var1) {
      switch (var0) {
         case 0:
            var1[0] = 255;
            var1[1] = 0;
            var1[2] = 0;
            break;
         case 1:
            var1[0] = 0;
            var1[1] = 255;
            var1[2] = 0;
            break;
         case 2:
            var1[0] = 0;
            var1[1] = 0;
            var1[2] = 255;
            break;
         case 3:
            var1[0] = 255;
            var1[1] = 255;
            var1[2] = 0;
            break;
         case 4:
            var1[0] = 255;
            var1[1] = 0;
            var1[2] = 255;
            break;
         case 5:
            var1[0] = 0;
            var1[1] = 0;
            var1[2] = 0;
            break;
         case 6:
            var1[0] = 255;
            var1[1] = 255;
            var1[2] = 255;
            break;
         case 7:
            var1[0] = 128;
            var1[1] = 128;
            var1[2] = 128;
      }
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
