#pragma once
#include "zombie/core/Core.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ChunkMapFilenames {
public:
  static ChunkMapFilenames instance = new ChunkMapFilenames();
public
  final ConcurrentHashMap<Long, Object> Map =
      std::make_unique<ConcurrentHashMap<>>();
public
  final ConcurrentHashMap<Long, Object> HeaderMap =
      std::make_unique<ConcurrentHashMap<>>();
  std::string prefix = "map_";
  File dirFile;
  std::string cacheDir;

  void clear() {
    this.dirFile = nullptr;
    this.cacheDir = nullptr;
    this.Map.clear();
    this.HeaderMap.clear();
  }

  File getFilename(int int1, int int0) {
    long long0 = (long)int1 << 32 | int0;
    if (this.Map.containsKey(long0)) {
      return (File)this.Map.get(long0);
    } else {
      if (this.cacheDir == nullptr) {
        this.cacheDir = ZomboidFileSystem.instance.getGameModeCacheDir();
      }

      std::string string = this.cacheDir + File.separator + Core.GameSaveWorld +
                           File.separator + this.prefix + int1 + "_" + int0 +
                           ".bin";
      File file = new File(string);
      this.Map.put(long0, file);
      return file;
    }
  }

  File getDir(const std::string &string) {
    if (this.cacheDir == nullptr) {
      this.cacheDir = ZomboidFileSystem.instance.getGameModeCacheDir();
    }

    if (this.dirFile == nullptr) {
      this.dirFile = new File(this.cacheDir + File.separator + string);
    }

    return this.dirFile;
  }

  std::string getHeader(int int1, int int0) {
    long long0 = (long)int1 << 32 | int0;
    if (this.HeaderMap.containsKey(long0)) {
      return this.HeaderMap.get(long0).toString();
    } else {
      std::string string = int1 + "_" + int0 + ".lotheader";
      this.HeaderMap.put(long0, string);
      return string;
    }
  }
}
} // namespace zombie
