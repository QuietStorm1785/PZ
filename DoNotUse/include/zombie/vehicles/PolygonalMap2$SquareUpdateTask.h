#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/PolygonalMap2/Chunk.h"
#include "zombie/vehicles/PolygonalMap2/ChunkDataZ.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    PolygonalMap2 map;
    int x;
    int y;
    int z;
    int bits;
    short cost;
   static const ArrayDeque<PolygonalMap2$SquareUpdateTask> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$SquareUpdateTask() {
   }

   PolygonalMap2$SquareUpdateTask init(PolygonalMap2 var1, IsoGridSquare var2) {
      this.map = var1;
      this.x = var2.x;
      this.y = var2.y;
      this.z = var2.z;
      this.bits = getBits(var2);
      this.cost = getCost(var2);
    return this;
   }

    void execute() {
    Chunk var1 = this.map.getChunkFromChunkPos(this.x / 10, this.y / 10);
      if (var1 != nullptr && var1.setData(this)) {
         ChunkDataZ.EPOCH++;
         this.map.rebuild = true;
      }
   }

    static int getBits(IsoGridSquare var0) {
    int var1 = 0;
      if (var0.Is(IsoFlagType.solidfloor)) {
         var1 |= 512;
      }

      if (var0.isSolid()) {
         var1 |= 1;
      }

      if (var0.isSolidTrans()) {
         var1 |= 1024;
      }

      if (var0.Is(IsoFlagType.collideW)) {
         var1 |= 2;
      }

      if (var0.Is(IsoFlagType.collideN)) {
         var1 |= 4;
      }

      if (var0.Has(IsoObjectType.stairsTW)) {
         var1 |= 8;
      }

      if (var0.Has(IsoObjectType.stairsMW)) {
         var1 |= 16;
      }

      if (var0.Has(IsoObjectType.stairsBW)) {
         var1 |= 32;
      }

      if (var0.Has(IsoObjectType.stairsTN)) {
         var1 |= 64;
      }

      if (var0.Has(IsoObjectType.stairsMN)) {
         var1 |= 128;
      }

      if (var0.Has(IsoObjectType.stairsBN)) {
         var1 |= 256;
      }

      if (var0.Is(IsoFlagType.windowW) || var0.Is(IsoFlagType.WindowW)) {
         var1 |= 2050;
         if (isWindowUnblocked(var0, false)) {
            var1 |= 1048576;
         }
      }

      if (var0.Is(IsoFlagType.windowN) || var0.Is(IsoFlagType.WindowN)) {
         var1 |= 4100;
         if (isWindowUnblocked(var0, true)) {
            var1 |= 2097152;
         }
      }

      if (var0.Is(IsoFlagType.canPathW)) {
         var1 |= 8192;
      }

      if (var0.Is(IsoFlagType.canPathN)) {
         var1 |= 16384;
      }

      for (int var2 = 0; var2 < var0.getSpecialObjects().size(); var2++) {
    IsoObject var3 = (IsoObject)var0.getSpecialObjects().get(var2);
    IsoDirections var4 = IsoDirections.Max;
         if (dynamic_cast<IsoDoor*>(var3) != nullptr) {
            var4 = ((IsoDoor)var3).getSpriteEdge(false);
            if (((IsoDoor)var3).IsOpen()) {
               var4 = IsoDirections.Max;
            }
         } else if (dynamic_cast<IsoThumpable*>(var3) != nullptr && ((IsoThumpable)var3).isDoor()) {
            var4 = ((IsoThumpable)var3).getSpriteEdge(false);
            if (((IsoThumpable)var3).IsOpen()) {
               var4 = IsoDirections.Max;
            }
         }

         if (var4 == IsoDirections.W) {
            var1 |= 8192;
            var1 |= 2;
         } else if (var4 == IsoDirections.N) {
            var1 |= 16384;
            var1 |= 4;
         } else if (var4 == IsoDirections.S) {
            var1 |= 524288;
         } else if (var4 == IsoDirections.E) {
            var1 |= 262144;
         }
      }

      if (var0.Is(IsoFlagType.DoorWallW)) {
         var1 |= 8192;
         var1 |= 2;
      }

      if (var0.Is(IsoFlagType.DoorWallN)) {
         var1 |= 16384;
         var1 |= 4;
      }

      if (hasSquareThumpable(var0)) {
         var1 |= 8192;
         var1 |= 16384;
         var1 |= 131072;
      }

      if (hasWallThumpableN(var0)) {
         var1 |= 81920;
      }

      if (hasWallThumpableW(var0)) {
         var1 |= 40960;
      }

    return var1;
   }

    static bool isWindowUnblocked(IsoGridSquare var0, bool var1) {
      for (int var2 = 0; var2 < var0.getSpecialObjects().size(); var2++) {
    IsoObject var3 = (IsoObject)var0.getSpecialObjects().get(var2);
         if (dynamic_cast<IsoThumpable*>(var3) != nullptr var4 && var4.isWindow() && var1 == var4.north) {
            if (var4.isBarricaded()) {
    return false;
            }

    return true;
         }

         if (dynamic_cast<IsoWindow*>(var3) != nullptr var6 && var1 == var6.north) {
            if (var6.isBarricaded()) {
    return false;
            }

            if (var6.isInvincible()) {
    return false;
            }

            if (var6.IsOpen()) {
    return true;
            }

            if (var6.isDestroyed() && var6.isGlassRemoved()) {
    return true;
            }

    return false;
         }
      }

    IsoObject var5 = var0.getWindowFrame(var1);
      return IsoWindowFrame.canClimbThrough(var5, nullptr);
   }

    static bool hasSquareThumpable(IsoGridSquare var0) {
      for (int var1 = 0; var1 < var0.getSpecialObjects().size(); var1++) {
    IsoThumpable var2 = (IsoThumpable)Type.tryCastTo((IsoObject)var0.getSpecialObjects().get(var1), IsoThumpable.class);
         if (var2 != nullptr && var2.isThumpable() && var2.isBlockAllTheSquare()) {
    return true;
         }
      }

      for (int var3 = 0; var3 < var0.getObjects().size(); var3++) {
    IsoObject var4 = (IsoObject)var0.getObjects().get(var3);
         if (var4.isMovedThumpable()) {
    return true;
         }
      }

    return false;
   }

    static bool hasWallThumpableN(IsoGridSquare var0) {
    IsoGridSquare var1 = var0.getAdjacentSquare(IsoDirections.N);
      if (var1 == nullptr) {
    return false;
      } else {
         for (int var2 = 0; var2 < var0.getSpecialObjects().size(); var2++) {
    IsoThumpable var3 = (IsoThumpable)Type.tryCastTo((IsoObject)var0.getSpecialObjects().get(var2), IsoThumpable.class);
            if (var3 != nullptr
               && !var3.canClimbThrough(nullptr)
               && !var3.canClimbOver(nullptr)
               && var3.isThumpable()
               && !var3.isBlockAllTheSquare()
               && !var3.isDoor()
               && var3.TestCollide(nullptr, var0, var1)) {
    return true;
            }
         }

    return false;
      }
   }

    static bool hasWallThumpableW(IsoGridSquare var0) {
    IsoGridSquare var1 = var0.getAdjacentSquare(IsoDirections.W);
      if (var1 == nullptr) {
    return false;
      } else {
         for (int var2 = 0; var2 < var0.getSpecialObjects().size(); var2++) {
    IsoThumpable var3 = (IsoThumpable)Type.tryCastTo((IsoObject)var0.getSpecialObjects().get(var2), IsoThumpable.class);
            if (var3 != nullptr
               && !var3.canClimbThrough(nullptr)
               && !var3.canClimbOver(nullptr)
               && var3.isThumpable()
               && !var3.isBlockAllTheSquare()
               && !var3.isDoor()
               && var3.TestCollide(nullptr, var0, var1)) {
    return true;
            }
         }

    return false;
      }
   }

    static short getCost(IsoGridSquare var0) {
    short var1 = 0;
      if (var0.HasTree() || var0.getProperties().Is("Bush")) {
         var1 = (short)(var1 + 5);
      }

    return var1;
   }

   static PolygonalMap2$SquareUpdateTask alloc() {
      /* synchronized - TODO: add std::mutex */ (pool) {
         return pool.empty() ? new PolygonalMap2$SquareUpdateTask() : pool.pop();
      }
   }

    void release() {
      /* synchronized - TODO: add std::mutex */ (pool) {
         if (!$assertionsDisabled && pool.contains(this)) {
            throw std::make_unique<AssertionError>();
         } else {
            pool.push(this);
         }
      }
   }
}
} // namespace vehicles
} // namespace zombie
