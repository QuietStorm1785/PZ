#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URISyntaxException.h"
#include "zombie/core/textures/Texture/PZFileformat.h"
#include "zombie/core/textures/TexturePackPage/SubTextureInfo.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace textures {


class TexturePackPage {
public:
   public static std::unordered_map<std::string, std::stack<std::string>> FoundTextures = std::make_unique<std::unordered_map<>>();
   public static const std::unordered_map<std::string, Texture> subTextureMap = std::make_unique<std::unordered_map<>>();
   public static const std::unordered_map<std::string, Texture> subTextureMap2 = std::make_unique<std::unordered_map<>>();
   public static const std::unordered_map<std::string, TexturePackPage> texturePackPageMap = std::make_unique<std::unordered_map<>>();
   public static const std::unordered_map<std::string, std::string> TexturePackPageNameMap = std::make_unique<std::unordered_map<>>();
   public const std::unordered_map<std::string, Texture> subTextures = std::make_unique<std::unordered_map<>>();
    Texture tex = nullptr;
    static ByteBuffer SliceBuffer = nullptr;
    static bool bHasCache = false;
    static int percent = 0;
    static int chl1 = 0;
    static int chl2 = 0;
    static int chl3 = 0;
    static int chl4 = 0;
    static std::stringstream v = new std::stringstream(50);
   public static std::vector<SubTextureInfo> TempSubTextureInfo = std::make_unique<std::vector<>>();
   public static std::vector<std::string> tempFilenameCheck = std::make_unique<std::vector<>>();
    static bool bIgnoreWorldItemTextures = true;

    static void LoadDir(const std::string& var0) {
   }

    static void searchFolders(File var0) {
   }

    static Texture getTexture(const std::string& var0) {
      if (var0.contains(".png")) {
         return Texture.getSharedTexture(var0);
      } else {
         return subTextureMap.containsKey(var0) ? subTextureMap.get(var0) : nullptr;
      }
   }

    static int readInt(InputStream var0) {
    int var1 = var0.read();
    int var2 = var0.read();
    int var3 = var0.read();
    int var4 = var0.read();
      chl1 = var1;
      chl2 = var2;
      chl3 = var3;
      chl4 = var4;
      if ((var1 | var2 | var3 | var4) < 0) {
         throw std::make_unique<EOFException>();
      } else {
         return (var1 << 0) + (var2 << 8) + (var3 << 16) + (var4 << 24);
      }
   }

    static int readInt(ByteBuffer var0) {
    uint8_t var1 = var0.get();
    uint8_t var2 = var0.get();
    uint8_t var3 = var0.get();
    uint8_t var4 = var0.get();
      chl1 = var1;
      chl2 = var2;
      chl3 = var3;
      chl4 = var4;
      return (var1 << 0) + (var2 << 8) + (var3 << 16) + (var4 << 24);
   }

    static int readIntByte(InputStream var0) {
    int var1 = chl2;
    int var2 = chl3;
    int var3 = chl4;
    int var4 = var0.read();
      chl1 = var1;
      chl2 = var2;
      chl3 = var3;
      chl4 = var4;
      if ((var1 | var2 | var3 | var4) < 0) {
         throw std::make_unique<EOFException>();
      } else {
         return (var1 << 0) + (var2 << 8) + (var3 << 16) + (var4 << 24);
      }
   }

    static std::string ReadString(InputStream var0) {
      v.setLength(0);
    int var1 = readInt(var0);

      for (int var2 = 0; var2 < var1; var2++) {
         v.append((char)var0.read());
      }

      return v;
   }

    void loadFromPackFileDDS(BufferedInputStream var1) {
    std::string var2 = ReadString(var1);
      tempFilenameCheck.push_back(var2);
    int var3 = readInt(var1);
    bool var4 = readInt(var1) != 0;
      TempSubTextureInfo.clear();

      for (int var5 = 0; var5 < var3; var5++) {
    std::string var6 = ReadString(var1);
    int var7 = readInt(var1);
    int var8 = readInt(var1);
    int var9 = readInt(var1);
    int var10 = readInt(var1);
    int var11 = readInt(var1);
    int var12 = readInt(var1);
    int var13 = readInt(var1);
    int var14 = readInt(var1);
         if (var6.contains("ZombieWalk") && var6.contains("BobZ_")) {
            TempSubTextureInfo.push_back(std::make_shared<SubTextureInfo>(var7, var8, var9, var10, var11, var12, var13, var14, var6));
         }
      }

      if (TempSubTextureInfo.empty()) {
    int var16 = 0;

         do {
            var16 = readIntByte(var1);
         } while (var16 != -559038737);
      } else {
    Texture var15 = std::make_shared<Texture>(var2, var1, var4, PZFileformat.DDS);

         for (int var18 = 0; var18 < TempSubTextureInfo.size(); var18++) {
    SubTextureInfo var21 = TempSubTextureInfo.get(var18);
    Texture var22 = var15.split(var21.x, var21.y, var21.w, var21.h);
            var22.copyMaskRegion(var15, var21.x, var21.y, var21.w, var21.h);
            var22.setName(var21.name);
            this.subTextures.put(var21.name, var22);
            subTextureMap.put(var21.name, var22);
            var22.offsetX = var21.ox;
            var22.offsetY = var21.oy;
            var22.widthOrig = var21.fx;
            var22.heightOrig = var21.fy;
         }

         var15.mask = nullptr;
         texturePackPageMap.put(var2, this);
    int var19 = 0;

         do {
            var19 = readIntByte(var1);
         } while (var19 != -559038737);
      }
   }

    void loadFromPackFile(BufferedInputStream var1) {
    std::string var2 = ReadString(var1);
      tempFilenameCheck.push_back(var2);
    int var3 = readInt(var1);
    bool var4 = readInt(var1) != 0;
      if (var4) {
    bool var5 = false;
      }

      TempSubTextureInfo.clear();

      for (int var15 = 0; var15 < var3; var15++) {
    std::string var6 = ReadString(var1);
    int var7 = readInt(var1);
    int var8 = readInt(var1);
    int var9 = readInt(var1);
    int var10 = readInt(var1);
    int var11 = readInt(var1);
    int var12 = readInt(var1);
    int var13 = readInt(var1);
    int var14 = readInt(var1);
         if (!bIgnoreWorldItemTextures || !var6.startsWith("WItem_")) {
            TempSubTextureInfo.push_back(std::make_shared<SubTextureInfo>(var7, var8, var9, var10, var11, var12, var13, var14, var6));
         }
      }

    Texture var16 = std::make_shared<Texture>(var2, var1, var4);

      for (int var17 = 0; var17 < TempSubTextureInfo.size(); var17++) {
    SubTextureInfo var20 = TempSubTextureInfo.get(var17);
    Texture var21 = var16.split(var20.x, var20.y, var20.w, var20.h);
         var21.copyMaskRegion(var16, var20.x, var20.y, var20.w, var20.h);
         var21.setName(var20.name);
         this.subTextures.put(var20.name, var21);
         subTextureMap.put(var20.name, var21);
         var21.offsetX = var20.ox;
         var21.offsetY = var20.oy;
         var21.widthOrig = var20.fx;
         var21.heightOrig = var20.fy;
      }

      var16.mask = nullptr;
      texturePackPageMap.put(var2, this);
    int var18 = 0;

      do {
         var18 = readIntByte(var1);
      } while (var18 != -559038737);
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
