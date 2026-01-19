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
    static ChunkMapFilenames instance = new ChunkMapFilenames();
   public final ConcurrentHashMap<Long, Object> Map = std::make_unique<ConcurrentHashMap<>>();
   public final ConcurrentHashMap<Long, Object> HeaderMap = std::make_unique<ConcurrentHashMap<>>();
    std::string prefix = "map_";
    File dirFile;
    std::string cacheDir;

    void clear() {
      this.dirFile = nullptr;
      this.cacheDir = nullptr;
      this.Map.clear();
      this.HeaderMap.clear();
   }

    File getFilename(int var1, int var2) {
    long var3 = (long)var1 << 32 | var2;
      if (this.Map.containsKey(var3)) {
         return (File)this.Map.get(var3);
      } else {
         if (this.cacheDir == nullptr) {
            this.cacheDir = ZomboidFileSystem.instance.getGameModeCacheDir();
         }

    std::string var5 = this.cacheDir + File.separator + Core.GameSaveWorld + File.separator + this.prefix + var1 + "_" + var2 + ".bin";
    File var6 = new File(var5);
         this.Map.put(var3, var6);
    return var6;
      }
   }

    File getDir(const std::string& var1) {
      if (this.cacheDir == nullptr) {
         this.cacheDir = ZomboidFileSystem.instance.getGameModeCacheDir();
      }

      if (this.dirFile == nullptr) {
         this.dirFile = new File(this.cacheDir + File.separator + var1);
      }

      return this.dirFile;
   }

    std::string getHeader(int var1, int var2) {
    long var3 = (long)var1 << 32 | var2;
      if (this.HeaderMap.containsKey(var3)) {
         return this.HeaderMap.get(var3).toString();
      } else {
    std::string var5 = var1 + "_" + var2 + ".lotheader";
         this.HeaderMap.put(var3, var5);
    return var5;
      }
   }
}
} // namespace zombie
