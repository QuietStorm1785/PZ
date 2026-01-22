#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {


class ChunkMapFilenames {
public:
   static std::shared_ptr<ChunkMapFilenames> instance;
   std::unordered_map<int64_t, std::filesystem::path> Map;
   std::unordered_map<int64_t, std::filesystem::path> HeaderMap;
    std::string prefix = "map_";
   std::filesystem::path dirFile;
    std::string cacheDir;

   void clear() {
      dirFile.clear();
      cacheDir.clear();
      Map.clear();
      HeaderMap.clear();
   }

   std::filesystem::path getFilename(int var1, int var2) {
      int64_t key = (static_cast<int64_t>(var1) << 32) | var2;
      auto it = Map.find(key);
      if (it != Map.end()) {
         return it->second;
      } else {
         if (cacheDir.empty()) {
            cacheDir = ZomboidFileSystem::instance->getGameModeCacheDir();
         }

    std::string var5 = this.cacheDir + File.separator + Core.GameSaveWorld + File.separator + this.prefix + var1 + "_" + var2 + ".bin";
    File var6 = std::make_shared<File>(var5);
         this.Map.put(var3, var6);
    return var6;
      }
   }

    File getDir(const std::string& var1) {
      if (this.cacheDir == nullptr) {
         this.cacheDir = ZomboidFileSystem.instance.getGameModeCacheDir();
      }

      if (this.dirFile == nullptr) {
         this.dirFile = std::make_shared<File>(this.cacheDir + File.separator + var1);
      }

      return this.dirFile;
   }

    std::string getHeader(int var1, int var2) {
    long var3 = (long)var1 << 32 | var2;
      if (this.HeaderMap.containsKey(var3)) {
         return this.HeaderMap.get(var3);
      } else {
    std::string var5 = var1 + "_" + var2 + ".lotheader";
         this.HeaderMap.put(var3, var5);
    return var5;
      }
   }
}
} // namespace zombie
