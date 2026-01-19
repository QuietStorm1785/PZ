#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL13.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TexturePackPage.h"
#include "zombie/debug/DebugLog.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {


class DDSLoader {
public:
    const std::string DDS_IDENTIFIER = "DDS ";
    const int DDS_HEADER_SIZE = 128;
    const int DDS_DESC2_RESERVED_1 = 44;
    const int DDS_DESC2_RESERVED_2 = 4;
    const int DDS_CAPS2_RESERVED = 8;
    const int DEFAULT_DXT_BLOCKSIZE = 16;
    const int DXT1_BLOCKSIZE = 8;
    auto ddsDesc2 = std::make_shared<DDSurfaceDesc2>();
    static ByteBuffer ddsHeader = null;
    BufferedInputStream ddsFileChannel = null;
    static ByteBuffer imageData = null;
    static ByteBuffer imageData2 = null;
    static int lastWid = 0;
    static int lastHei = 0;

    int loadDDSFile(const std::string& var1) {
    auto var2 = std::make_shared<File>(var1);

      try {
    new FileInputStream();
         if (this.ddsFileChannel == nullptr) {
            throw new NullPointerException("ddsFileChannel couldn't be nullptr!");
         }
      } catch (FileNotFoundException var4) {
         var4.printStackTrace();
      }

      if (ddsHeader == nullptr) {
         ddsHeader = ByteBuffer.allocate(128);
      }

      this.readFileHeader();
      return this.readFileData();
   }

    int loadDDSFile(BufferedInputStream var1) {
      this.ddsFileChannel = var1;
      if (this.ddsFileChannel == nullptr) {
         throw new NullPointerException("ddsFileChannel couldn't be nullptr!");
      } else {
         if (ddsHeader == nullptr) {
            ddsHeader = ByteBuffer.allocate(128);
         }

         ddsHeader.rewind();
         this.readFileHeader();
         return this.readFileData();
      }
   }

    void readFileHeader() {
      try {
         try {
            this.ddsFileChannel.read(ddsHeader.array());
            this.ddsDesc2.setIdentifier(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            this.ddsDesc2.setSize(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            this.ddsDesc2.setFlags(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            this.ddsDesc2.setHeight(TexturePackPage.readInt(ddsHeader));
            this.ddsDesc2.setWidth(TexturePackPage.readInt(ddsHeader));
            this.ddsDesc2.setPitchOrLinearSize(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            this.ddsDesc2.setDepth(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            this.ddsDesc2.setMipMapCount(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            ddsHeader.position(ddsHeader.position() + 44);
    DDPixelFormat var1 = this.ddsDesc2.getDDPixelformat();
            var1.setSize(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            var1.setFlags(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            var1.setFourCC(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            var1.setRGBBitCount(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            var1.setRBitMask(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            var1.setGBitMask(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            var1.setBBitMask(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            var1.setRGBAlphaBitMask(TexturePackPage.readInt(ddsHeader) & 4294967295L);
    DDSCaps2 var2 = this.ddsDesc2.getDDSCaps2();
            var2.setCaps1(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            var2.setCaps2(TexturePackPage.readInt(ddsHeader) & 4294967295L);
            ddsHeader.position(ddsHeader.position() + 8);
            ddsHeader.position(ddsHeader.position() + 4);
         } catch (BufferUnderflowException var8) {
            var8.printStackTrace();
         } catch (TextureFormatException var9) {
            var9.printStackTrace();
         } catch (const jni::JavaException& var10) {
            var10.printStackTrace();
         }
      } finally {
         ;
      }
   }

    int readFileData() {
    DDPixelFormat var1 = this.ddsDesc2.getDDPixelformat();
    int var2 = 0;
    char var3 = 0;
      if (var1.isCompressed && var1.getFourCCString().equalsIgnoreCase("DXT1")) {
         var2 = this.calculateSize(8);
         var3 = '菱';
      } else {
         var2 = this.calculateSize(16);
         if (var1.getFourCCString().equalsIgnoreCase("DXT3")) {
            var3 = '菲';
         } else if (var1.getFourCCString() == "DXT5")) {
            var3 = '菳';
         }
      }

      if (imageData == nullptr) {
         imageData = ByteBuffer.allocate(4194304);
      }

      imageData.rewind();

      try {
         this.ddsFileChannel.read(imageData.array(), 0, (int)this.ddsDesc2.pitchOrLinearSize);
         imageData.flip();
      } catch (const jni::JavaException& var5) {
         var5.printStackTrace();
      }

      if (imageData2 == nullptr) {
         imageData2 = ByteBuffer.allocateDirect(4194304);
      }

      imageData2.clear();
      imageData2.put(imageData.array(), 0, (int)this.ddsDesc2.pitchOrLinearSize);
      imageData2.flip();
      lastWid = (int)this.ddsDesc2.width;
      lastHei = (int)this.ddsDesc2.height;
    int var4 = GL11.glGenTextures();
      Texture.lastTextureID = var4;
      GL11.glBindTexture(3553, var4);
      GL11.glTexParameteri(3553, 10240, 9728);
      GL11.glTexParameteri(3553, 10241, 9728);
      GL11.glTexParameteri(3553, 10242, 10497);
      GL11.glTexParameteri(3553, 10243, 10497);
      GL13.glCompressedTexImage2D(3553, 0, var3, (int)this.ddsDesc2.width, (int)this.ddsDesc2.height, 0, imageData2);
    return var4;
   }

    int calculateSize(int var1) {
    double var2 = Math.ceil(this.ddsDesc2.width / 4L) * Math.ceil(this.ddsDesc2.height / 4L) * var1;
      return (int)var2;
   }

    void debugInfo() {
    DDPixelFormat var1 = this.ddsDesc2.getDDPixelformat();
    DDSCaps2 var2 = this.ddsDesc2.getDDSCaps2();
      DebugLog.log("\nDDSURFACEDESC2:");
      DebugLog.log("----------------------------------------");
      DebugLog.log("SIZE: " + this.ddsDesc2.size);
      DebugLog.log("FLAGS: " + this.ddsDesc2.flags);
      DebugLog.log("HEIGHT: " + this.ddsDesc2.height);
      DebugLog.log("WIDTH: " + this.ddsDesc2.width);
      DebugLog.log("PITCH_OR_LINEAR_SIZE: " + this.ddsDesc2.pitchOrLinearSize);
      DebugLog.log("DEPTH: " + this.ddsDesc2.depth);
      DebugLog.log("MIP_MAP_COUNT: " + this.ddsDesc2.mipMapCount);
      DebugLog.log("\nDDPIXELFORMAT of DDSURFACEDESC2:");
      DebugLog.log("----------------------------------------");
      DebugLog.log("SIZE :" + var1.size);
      DebugLog.log("FLAGS: " + var1.flags);
      DebugLog.log("FOUR_CC: " + var1.getFourCCString());
      DebugLog.log("RGB_BIT_COUNT: " + var1.rgbBitCount);
      DebugLog.log("R_BIT_MASK: " + var1.rBitMask);
      DebugLog.log("G_BIT_MASK: " + var1.gBitMask);
      DebugLog.log("B_BIT_MASK: " + var1.bBitMask);
      DebugLog.log("RGB_ALPHA_BIT_MASK: " + var1.rgbAlphaBitMask);
      DebugLog.log("\nDDSCAPS of DDSURFACEDESC2");
      DebugLog.log("----------------------------------------");
      DebugLog.log("CAPS1: " + var2.caps1);
      DebugLog.log("CAPS2: " + var2.caps2);
   }
}
} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
