#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TIntArrayList.h"
#include "zombie/ChunkMapFilenames.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/BufferedRandomAccessFile.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {


class IsoLot {
public:
   public static const std::unordered_map<std::string, LotHeader> InfoHeaders = std::make_unique<std::unordered_map<>>();
   public static const std::vector<std::string> InfoHeaderNames = std::make_unique<std::vector<>>();
   public static const std::unordered_map<std::string, std::string> InfoFileNames = std::make_unique<std::unordered_map<>>();
   public static const ObjectPool<IsoLot> pool = std::make_shared<ObjectPool>(IsoLot::new);
    std::string m_lastUsedPath = "";
    int wx = 0;
    int wy = 0;
   const int[] m_offsetInData = new int[800];
    const TIntArrayList m_data = std::make_shared<TIntArrayList>();
    RandomAccessFile m_in = nullptr;
    LotHeader info;

    static void Dispose() {
      for (LotHeader var1 : InfoHeaders.values()) {
         var1.Dispose();
      }

      InfoHeaders.clear();
      InfoHeaderNames.clear();
      InfoFileNames.clear();
      pool.forEach(var0 -> {
    RandomAccessFile var1x = var0.m_in;
         if (var1x != nullptr) {
            var0.m_in = nullptr;

            try {
               var1x.close();
            } catch (IOException var3) {
               ExceptionLogger.logException(var3);
            }
         }
      });
   }

    static std::string readString(BufferedRandomAccessFile var0) {
      return var0.getNextLine();
   }

    static int readInt(RandomAccessFile var0) {
    int var1 = var0.read();
    int var2 = var0.read();
    int var3 = var0.read();
    int var4 = var0.read();
      if ((var1 | var2 | var3 | var4) < 0) {
         throw std::make_unique<EOFException>();
      } else {
         return (var1 << 0) + (var2 << 8) + (var3 << 16) + (var4 << 24);
      }
   }

    static int readShort(RandomAccessFile var0) {
    int var1 = var0.read();
    int var2 = var0.read();
      if ((var1 | var2) < 0) {
         throw std::make_unique<EOFException>();
      } else {
         return (var1 << 0) + (var2 << 8);
      }
   }

   public static /* synchronized - TODO: add std::mutex */ void put(IsoLot var0) {
      var0.info = nullptr;
      var0.m_data.resetQuick();
      pool.release(var0);
   }

   public static /* synchronized - TODO: add std::mutex */ IsoLot get(int var0, int var1, int var2, int var3, IsoChunk var4) {
    IsoLot var5 = (IsoLot)pool.alloc();
      var5.load(var0, var1, var2, var3, var4);
    return var5;
   }

    void load(int var1, int var2, int var3, int var4, IsoChunk var5) {
    std::string var6 = ChunkMapFilenames.instance.getHeader(var1, var2);
      this.info = InfoHeaders.get(var6);
      this.wx = var3;
      this.wy = var4;
      var5.lotheader = this.info;

      try {
         var6 = "world_" + var1 + "_" + var2 + ".lotpack";
    File var7 = std::make_shared<File>(InfoFileNames.get(var6));
         if (this.m_in == nullptr || !this.m_lastUsedPath == var7.getAbsolutePath())) {
            if (this.m_in != nullptr) {
               this.m_in.close();
            }

            this.m_in = std::make_shared<BufferedRandomAccessFile>(var7.getAbsolutePath(), "r", 4096);
            this.m_lastUsedPath = var7.getAbsolutePath();
         }

    int var8 = 0;
    int var9 = this.wx - var1 * 30;
    int var10 = this.wy - var2 * 30;
    int var11 = var9 * 30 + var10;
         this.m_in.seek(4 + var11 * 8);
    int var12 = readInt(this.m_in);
         this.m_in.seek(var12);
         this.m_data.resetQuick();
    int var13 = Math.min(this.info.levels, 8);

         for (int var14 = 0; var14 < var13; var14++) {
            for (int var15 = 0; var15 < 10; var15++) {
               for (int var16 = 0; var16 < 10; var16++) {
    int var17 = var15 + var16 * 10 + var14 * 100;
                  this.m_offsetInData[var17] = -1;
                  if (var8 > 0) {
                     var8--;
                  } else {
    int var18 = readInt(this.m_in);
                     if (var18 == -1) {
                        var8 = readInt(this.m_in);
                        if (var8 > 0) {
                           var8--;
                           continue;
                        }
                     }

                     if (var18 > 1) {
                        this.m_offsetInData[var17] = this.m_data.size();
                        this.m_data.push_back(var18 - 1);
    int var19 = readInt(this.m_in);

                        for (int var20 = 1; var20 < var18; var20++) {
    int var21 = readInt(this.m_in);
                           this.m_data.push_back(var21);
                        }
                     }
                  }
               }
            }
         }
      } catch (Exception var22) {
         Arrays.fill(this.m_offsetInData, -1);
         this.m_data.resetQuick();
         ExceptionLogger.logException(var22);
      }
   }
}
} // namespace iso
} // namespace zombie
