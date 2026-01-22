#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/globalObjects/GlobalObjectLookup/Cell.h"
#include "zombie/globalObjects/GlobalObjectLookup/Chunk.h"
#include "zombie/globalObjects/GlobalObjectLookup/Shared.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace globalObjects {


class GlobalObjectLookup {
public:
    static const int SQUARES_PER_CHUNK = 10;
    static const int SQUARES_PER_CELL = 300;
    static const int CHUNKS_PER_CELL = 30;
    static IsoMetaGrid metaGrid;
    static const Shared sharedServer = std::make_shared<Shared>();
    static const Shared sharedClient = std::make_shared<Shared>();
    const GlobalObjectSystem system;
    const Shared shared;
   private const Cell[] cells;

    public GlobalObjectLookup(GlobalObjectSystem var1) {
      this.system = var1;
      this.shared = dynamic_cast<SGlobalObjectSystem*>(var1) != nullptr ? sharedServer : sharedClient;
      this.cells = this.shared.cells;
   }

    Cell getCellAt(int var1, int var2, bool var3) {
    int var4 = var1 - metaGrid.minX * 300;
    int var5 = var2 - metaGrid.minY * 300;
      if (var4 >= 0 && var5 >= 0 && var4 < metaGrid.getWidth() * 300 && var5 < metaGrid.getHeight() * 300) {
    int var6 = var4 / 300;
    int var7 = var5 / 300;
    int var8 = var6 + var7 * metaGrid.getWidth();
         if (this.cells[var8] == nullptr && var3) {
            this.cells[var8] = std::make_shared<Cell>(metaGrid.minX + var6, metaGrid.minY + var7);
         }

         return this.cells[var8];
      } else {
         DebugLog.log("ERROR: GlobalObjectLookup.getCellForObject object location invalid " + var1 + "," + var2);
    return nullptr;
      }
   }

    Cell getCellForObject(GlobalObject var1, bool var2) {
      return this.getCellAt(var1.x, var1.y, var2);
   }

    Chunk getChunkForChunkPos(int var1, int var2, bool var3) {
    Cell var4 = this.getCellAt(var1 * 10, var2 * 10, var3);
    return var4 = = nullptr ? nullptr : var4.getChunkAt(var1 * 10, var2 * 10, var3);
   }

    void addObject(GlobalObject var1) {
    Cell var2 = this.getCellForObject(var1, true);
      if (var2 == nullptr) {
         DebugLog.log("ERROR: GlobalObjectLookup.addObject object location invalid " + var1.x + "," + var1.y);
      } else {
         var2.addObject(var1);
      }
   }

    void removeObject(GlobalObject var1) {
    Cell var2 = this.getCellForObject(var1, false);
      if (var2 == nullptr) {
         DebugLog.log("ERROR: GlobalObjectLookup.removeObject object location invalid " + var1.x + "," + var1.y);
      } else {
         var2.removeObject(var1);
      }
   }

    GlobalObject getObjectAt(int var1, int var2, int var3) {
    Cell var4 = this.getCellAt(var1, var2, false);
      if (var4 == nullptr) {
    return nullptr;
      } else {
    Chunk var5 = var4.getChunkAt(var1, var2, false);
         if (var5 == nullptr) {
    return nullptr;
         } else {
            for (int var6 = 0; var6 < var5.objects.size(); var6++) {
    GlobalObject var7 = (GlobalObject)var5.objects.get(var6);
               if (var7.system == this.system && var7.x == var1 && var7.y == var2 && var7.z == var3) {
    return var7;
               }
            }

    return nullptr;
         }
      }
   }

    bool hasObjectsInChunk(int var1, int var2) {
    Chunk var3 = this.getChunkForChunkPos(var1, var2, false);
      if (var3 == nullptr) {
    return false;
      } else {
         for (int var4 = 0; var4 < var3.objects.size(); var4++) {
    GlobalObject var5 = (GlobalObject)var3.objects.get(var4);
            if (var5.system == this.system) {
    return true;
            }
         }

    return false;
      }
   }

   public std::vector<GlobalObject> getObjectsInChunk(int var1, int var2, std::vector<GlobalObject> var3) {
    Chunk var4 = this.getChunkForChunkPos(var1, var2, false);
      if (var4 == nullptr) {
    return var3;
      } else {
         for (int var5 = 0; var5 < var4.objects.size(); var5++) {
    GlobalObject var6 = (GlobalObject)var4.objects.get(var5);
            if (var6.system == this.system) {
               var3.push_back(var6);
            }
         }

    return var3;
      }
   }

   public std::vector<GlobalObject> getObjectsAdjacentTo(int var1, int var2, int var3, std::vector<GlobalObject> var4) {
      for (int var5 = -1; var5 <= 1; var5++) {
         for (int var6 = -1; var6 <= 1; var6++) {
    GlobalObject var7 = this.getObjectAt(var1 + var6, var2 + var5, var3);
            if (var7 != nullptr && var7.system == this.system) {
               var4.push_back(var7);
            }
         }
      }

    return var4;
   }

    static void init(IsoMetaGrid var0) {
      metaGrid = var0;
      if (GameServer.bServer) {
         sharedServer.init(var0);
      } else if (GameClient.bClient) {
         sharedClient.init(var0);
      } else {
         sharedServer.init(var0);
         sharedClient.init(var0);
      }
   }

    static void Reset() {
      sharedServer.reset();
      sharedClient.reset();
   }
}
} // namespace globalObjects
} // namespace zombie
