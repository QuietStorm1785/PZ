#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TIntLongHashMap.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class ChunkChecksum {
public:
    static const TIntLongHashMap checksumCache = std::make_shared<TIntLongHashMap>();
    static const std::stringstream stringBuilder = new std::stringstream(128);
    static const CRC32 crc32 = std::make_shared<CRC32>();
   private static const byte[] bytes = new byte[1024];

    static void noise(const std::string& var0) {
      if (Core.bDebug) {
      }
   }

    static long getChecksum(int var0, int var1) {
      MPStatistic.getInstance().ChunkChecksum.Start();
    long var2 = 0L;
      /* synchronized - TODO: add std::mutex */ (checksumCache) {
    int var5 = var0 + var1 * 30 * 1000;
         if (checksumCache.containsKey(var5)) {
            noise(var0 + "," + var1 + " found in cache crc=" + checksumCache.get(var5));
            var2 = checksumCache.get(var5);
         } else {
            stringBuilder.setLength(0);
            stringBuilder.append(ZomboidFileSystem.instance.getGameModeCacheDir());
            stringBuilder.append(File.separator);
            stringBuilder.append(Core.GameSaveWorld);
            stringBuilder.append(File.separator);
            stringBuilder.append("map_");
            stringBuilder.append(var0);
            stringBuilder.append("_");
            stringBuilder.append(var1);
            stringBuilder.append(".bin");
            var2 = createChecksum(stringBuilder);
            checksumCache.put(var5, var2);
            noise(var0 + "," + var1 + " read from disk crc=" + var2);
         }
      }

      MPStatistic.getInstance().ChunkChecksum.End();
    return var2;
   }

    static long getChecksumIfExists(int var0, int var1) {
    long var2 = 0L;
      MPStatistic.getInstance().ChunkChecksum.Start();
      /* synchronized - TODO: add std::mutex */ (checksumCache) {
    int var5 = var0 + var1 * 30 * 1000;
         if (checksumCache.containsKey(var5)) {
            var2 = checksumCache.get(var5);
         }
      }

      MPStatistic.getInstance().ChunkChecksum.End();
    return var2;
   }

    static void setChecksum(int var0, int var1, long var2) {
      MPStatistic.getInstance().ChunkChecksum.Start();
      /* synchronized - TODO: add std::mutex */ (checksumCache) {
    int var5 = var0 + var1 * 30 * 1000;
         checksumCache.put(var5, var2);
         noise(var0 + "," + var1 + " set crc=" + var2);
      }

      MPStatistic.getInstance().ChunkChecksum.End();
   }

    static long createChecksum(const std::string& var0) {
      MPStatistic.getInstance().ChunkChecksum.Start();
    File var1 = std::make_shared<File>(var0);
      if (!var1.exists()) {
         MPStatistic.getInstance().ChunkChecksum.End();
    return 0L;
      } else {
    long var6;
         try (FileInputStream var2 = std::make_shared<FileInputStream>(var0)) {
            crc32.reset();

    int var3;
            while ((var3 = var2.read(bytes)) != -1) {
               crc32.update(bytes, 0, var3);
            }

    long var4 = crc32.getValue();
            MPStatistic.getInstance().ChunkChecksum.End();
            var6 = var4;
         }

    return var6;
      }
   }

    static void Reset() {
      MPStatistic.getInstance().ChunkChecksum.Start();
      checksumCache.clear();
      MPStatistic.getInstance().ChunkChecksum.End();
   }
}
} // namespace network
} // namespace zombie
