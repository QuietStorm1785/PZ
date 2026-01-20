#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/textures/TexturePackPage.h"
#include "zombie/core/textures/TexturePackPage/SubTextureInfo.h"
#include "zombie/fileSystem/FileSystem/TexturePackTextures.h"
#include "zombie/fileSystem/TexturePackDevice/Page.h"
#include "zombie/fileSystem/TexturePackDevice/PositionInputStream.h"
#include "zombie/fileSystem/TexturePackDevice/SubTexture.h"
#include "zombie/fileSystem/TexturePackDevice/TexturePackInputStream.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {


class TexturePackDevice {
public:
    static const int VERSION1 = 1;
    static const int VERSION_LATEST = 1;
    std::string m_name;
    std::string m_filename;
    int m_version = -1;
   const std::vector<Page> m_pages = std::make_unique<std::vector<>>();
   const std::unordered_map<std::string, Page> m_pagemap = std::make_unique<std::unordered_map<>>();
   const std::unordered_map<std::string, SubTexture> m_submap = std::make_unique<std::unordered_map<>>();
    int m_textureFlags;

    static long skipInput(InputStream var0, long var1) {
    long var3 = 0L;

      while (var3 < var1) {
    long var5 = var0.skip(var1 - var3);
         if (var5 > 0L) {
            var3 += var5;
         }
      }

    return var3;
   }

    public TexturePackDevice(const std::string& var1, int var2) {
      this.m_name = var1;
      this.m_filename = ZomboidFileSystem.instance.getString("media/texturepacks/" + var1 + ".pack");
      this.m_textureFlags = var2;
   }

    IFile createFile(IFile var1) {
    return nullptr;
   }

    void destroyFile(IFile var1) {
   }

    InputStream createStream(const std::string& var1, InputStream var2) {
      this.initMetaData();
      return std::make_shared<TexturePackInputStream>(var1, this);
   }

    void destroyStream(InputStream var1) {
      if (dynamic_cast<TexturePackInputStream*>(var1) != nullptr) {
      }
   }

    std::string name() {
      return this.m_name;
   }

    void getSubTextureInfo(TexturePackTextures var1) {
      this.initMetaData();

      for (SubTexture var3 : this.m_submap.values()) {
         zombie.fileSystem.FileSystem.SubTexture var4 = new zombie.fileSystem.FileSystem.SubTexture(this.name(), var3.m_page.m_name, var3.m_info);
         var1.put(var3.m_info.name, var4);
      }
   }

    void initMetaData() {
      if (this.m_pages.empty()) {
         try (
    FileInputStream var1 = std::make_shared<FileInputStream>(this.m_filename);
    BufferedInputStream var2 = std::make_shared<BufferedInputStream>(var1);
         ) {
    PositionInputStream var3 = std::make_shared<PositionInputStream>(this, var2);

            try {
               var3.mark(4);
    int var4 = var3.read();
    int var5 = var3.read();
    int var6 = var3.read();
    int var7 = var3.read();
               if (var4 == 80 && var5 == 90 && var6 == 80 && var7 == 75) {
                  this.m_version = TexturePackPage.readInt(var3);
                  if (this.m_version < 1 || this.m_version > 1) {
                     throw IOException("invalid .pack file version " + this.m_version);
                  }
               } else {
                  var3.reset();
                  this.m_version = 0;
               }

    int var8 = TexturePackPage.readInt(var3);

               for (int var9 = 0; var9 < var8; var9++) {
    Page var10 = this.readPage(var3);
                  this.m_pages.push_back(var10);
                  this.m_pagemap.put(var10.m_name, var10);

                  for (SubTextureInfo var12 : var10.m_sub) {
                     this.m_submap.put(var12.name, std::make_shared<SubTexture>(var10, var12));
                  }
               }
            } catch (Throwable var16) {
               try {
                  var3.close();
               } catch (Throwable var15) {
                  var16.addSuppressed(var15);
               }

    throw var16;
            }

            var3.close();
         }
      }
   }

    Page readPage(PositionInputStream var1) {
    Page var2 = std::make_shared<Page>();
    std::string var3 = TexturePackPage.ReadString(var1);
    int var4 = TexturePackPage.readInt(var1);
    bool var5 = TexturePackPage.readInt(var1) != 0;
      var2.m_name = var3;
      var2.m_has_alpha = var5;

      for (int var6 = 0; var6 < var4; var6++) {
    std::string var7 = TexturePackPage.ReadString(var1);
    int var8 = TexturePackPage.readInt(var1);
    int var9 = TexturePackPage.readInt(var1);
    int var10 = TexturePackPage.readInt(var1);
    int var11 = TexturePackPage.readInt(var1);
    int var12 = TexturePackPage.readInt(var1);
    int var13 = TexturePackPage.readInt(var1);
    int var14 = TexturePackPage.readInt(var1);
    int var15 = TexturePackPage.readInt(var1);
         var2.m_sub.push_back(std::make_shared<SubTextureInfo>(var8, var9, var10, var11, var12, var13, var14, var15, var7));
      }

      var2.m_png_start = var1.getPosition();
      if (this.m_version == 0) {
    int var16 = 0;

         do {
            var16 = TexturePackPage.readIntByte(var1);
         } while (var16 != -559038737);
      } else {
    int var18 = TexturePackPage.readInt(var1);
         skipInput(var1, var18);
      }

    return var2;
   }

    bool isAlpha(const std::string& var1) {
    Page var2 = this.m_pagemap.get(var1);
      return var2.m_has_alpha;
   }

    int getTextureFlags() {
      return this.m_textureFlags;
   }
}
} // namespace fileSystem
} // namespace zombie
