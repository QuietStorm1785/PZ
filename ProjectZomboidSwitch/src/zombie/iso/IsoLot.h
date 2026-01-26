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

// Forward declarations
class LotHeader;

class IsoLot {
public:
   static std::unordered_map<std::string, std::shared_ptr<LotHeader>> InfoHeaders;
   static std::vector<std::string> InfoHeaderNames;
   static std::unordered_map<std::string, std::string> InfoFileNames;
   static ObjectPool<IsoLot> pool;
   static std::mutex lot_mutex;

   std::string m_lastUsedPath;
   int wx, wy;
   std::vector<int> m_offsetInData;
   std::vector<int> m_data;
   std::shared_ptr<BufferedRandomAccessFile> m_in;
   std::shared_ptr<LotHeader> info;

   IsoLot() : wx(0), wy(0), m_offsetInData(800, -1) {}

   static void Dispose() {
      std::lock_guard<std::mutex> lock(lot_mutex);
      for (auto& kv : InfoHeaders) {
         if (kv.second) kv.second->Dispose();
      }
      InfoHeaders.clear();
      InfoHeaderNames.clear();
      InfoFileNames.clear();
      // Release all pooled IsoLot objects and close files
      pool.forEach([](IsoLot* lot) {
         if (lot->m_in) {
            lot->m_in->close();
            lot->m_in = nullptr;
         }
      });
   }

   static std::string readString(BufferedRandomAccessFile& var0) {
      return var0.getNextLine();
   }

   static int readInt(BufferedRandomAccessFile& var0) {
      int b1 = var0.read();
      int b2 = var0.read();
      int b3 = var0.read();
      int b4 = var0.read();
      if ((b1 | b2 | b3 | b4) < 0) throw std::runtime_error("EOF");
      return (b1 << 0) + (b2 << 8) + (b3 << 16) + (b4 << 24);
   }

   static int readShort(BufferedRandomAccessFile& var0) {
      int b1 = var0.read();
      int b2 = var0.read();
      if ((b1 | b2) < 0) throw std::runtime_error("EOF");
      return (b1 << 0) + (b2 << 8);
   }

   static void put(std::shared_ptr<IsoLot> lot) {
      std::lock_guard<std::mutex> lock(lot_mutex);
      if (lot) {
         lot->info = nullptr;
         lot->m_data.clear();
         pool.release(lot.get());
      }
   }

   static std::shared_ptr<IsoLot> get(int var0, int var1, int var2, int var3, std::shared_ptr<IsoChunk> var4) {
      std::lock_guard<std::mutex> lock(lot_mutex);
      auto lot = std::shared_ptr<IsoLot>(pool.alloc());
      lot->load(var0, var1, var2, var3, var4);
      return lot;
   }

   void load(int cellX, int cellY, int wx_, int wy_, std::shared_ptr<IsoChunk> chunk) {
      std::lock_guard<std::mutex> lock(lot_mutex);
      std::string headerKey = ChunkMapFilenames::instance.getHeader(cellX, cellY);
      info = InfoHeaders.count(headerKey) ? InfoHeaders[headerKey] : nullptr;
      wx = wx_;
      wy = wy_;
      if (chunk) chunk->lotheader = info;

      try {
         std::string lotFile = "world_" + std::to_string(cellX) + "_" + std::to_string(cellY) + ".lotpack";
         std::string lotPath = InfoFileNames.count(lotFile) ? InfoFileNames[lotFile] : lotFile;
         if (!m_in || m_lastUsedPath != lotPath) {
            if (m_in) m_in->close();
            m_in = std::make_shared<BufferedRandomAccessFile>(lotPath, "r", 4096);
            m_lastUsedPath = lotPath;
         }
         int var8 = 0;
         int var9 = wx - cellX * 30;
         int var10 = wy - cellY * 30;
         int var11 = var9 * 30 + var10;
         m_in->seek(4 + var11 * 8);
         int var12 = readInt(*m_in);
         m_in->seek(var12);
         m_data.clear();
         int maxLevels = info ? std::min(info->levels, 8) : 8;
         for (int l = 0; l < maxLevels; ++l) {
            for (int i = 0; i < 10; ++i) {
               for (int j = 0; j < 10; ++j) {
                  int idx = i + j * 10 + l * 100;
                  m_offsetInData[idx] = -1;
                  if (var8 > 0) {
                     var8--;
                  } else {
                     int var18 = readInt(*m_in);
                     if (var18 == -1) {
                        var8 = readInt(*m_in);
                        if (var8 > 0) {
                           var8--;
                           continue;
                        }
                     }
                     if (var18 > 1) {
                        m_offsetInData[idx] = (int)m_data.size();
                        m_data.push_back(var18 - 1);
                        int var19 = readInt(*m_in);
                        for (int k = 1; k < var18; ++k) {
                           int var21 = readInt(*m_in);
                           m_data.push_back(var21);
                        }
                     }
                  }
               }
            }
         }
      } catch (const std::exception& ex) {
         std::fill(m_offsetInData.begin(), m_offsetInData.end(), -1);
         m_data.clear();
         ExceptionLogger::logException(ex);
      }
   }
};

class LotHeader {
public:
    int cellX, cellY;
    int width = 0, height = 0, levels = 0, version = 0;
    std::unordered_map<int, std::shared_ptr<RoomDef>> Rooms;
    std::vector<std::shared_ptr<RoomDef>> RoomList;
    std::vector<std::shared_ptr<BuildingDef>> Buildings;
    std::unordered_map<int, std::shared_ptr<IsoRoom>> isoRooms;
    std::unordered_map<int, std::shared_ptr<IsoBuilding>> isoBuildings;
    bool bFixed2x = false;
    std::vector<std::string> tilesUsed;

    int getHeight() const { return height; }
    int getWidth() const { return width; }
    int getLevels() const { return levels; }
    std::shared_ptr<IsoRoom> getRoom(int id);
    int getRoomAt(int x, int y, int z) const;
    void Dispose();
};

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

   static void put(std::shared_ptr<IsoLot> lot) {
      std::lock_guard<std::mutex> lock(lot_mutex);
      if (lot) {
         lot->info = nullptr;
         lot->m_data.clear();
         pool.release(lot.get());
      }
   }

   static std::shared_ptr<IsoLot> get(int var0, int var1, int var2, int var3, std::shared_ptr<IsoChunk> var4) {
         std::lock_guard<std::mutex> lock(lot_mutex);
         auto lot = std::shared_ptr<IsoLot>(pool.alloc());
         lot->load(var0, var1, var2, var3, var4);
         return lot;
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
