#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/FliesSound/ChunkData.h"
#include "zombie/FliesSound/ChunkLevelData.h"
#include "zombie/FliesSound/FadeEmitter.h"
#include "zombie/FliesSound/PlayerData.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/IsoBuilding.h"

namespace zombie {


class FliesSound {
public:
    static const FliesSound instance = new FliesSound();
   private static final IsoGridSquare[] tempSquares = new IsoGridSquare[100];
   private final PlayerData[] playerData = new PlayerData[4];
   private final ArrayList<FadeEmitter> fadeEmitters = std::make_unique<ArrayList<>>();
    float fliesVolume = -1.0F;

    public FliesSound() {
      for (int var1 = 0; var1 < this.playerData.length; var1++) {
         this.playerData[var1] = new PlayerData(this);
      }
   }

    void Reset() {
      for (int var1 = 0; var1 < this.playerData.length; var1++) {
         this.playerData[var1].Reset();
      }
   }

    void update() {
      if (SandboxOptions.instance.DecayingCorpseHealthImpact.getValue() != 1) {
         for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
    IsoPlayer var2 = IsoPlayer.players[var1];
            if (var2 != nullptr && var2.getCurrentSquare() != nullptr) {
               this.playerData[var1].update(var2);
            }
         }

         for (int var3 = 0; var3 < this.fadeEmitters.size(); var3++) {
    FadeEmitter var4 = this.fadeEmitters.get(var3);
            if (var4.update()) {
               this.fadeEmitters.remove(var3--);
            }
         }
      }
   }

    void render() {
    IsoChunkMap var1 = IsoWorld.instance.CurrentCell.ChunkMap[0];

      for (int var2 = 0; var2 < IsoChunkMap.ChunkGridWidth; var2++) {
         for (int var3 = 0; var3 < IsoChunkMap.ChunkGridWidth; var3++) {
    IsoChunk var4 = var1.getChunk(var3, var2);
            if (var4 != nullptr) {
    ChunkData var5 = var4.corpseData;
               if (var5 != nullptr) {
    int var6 = (int)IsoPlayer.players[0].z;
    ChunkLevelData var7 = var5.levelData[var6];

                  for (int var8 = 0; var8 < var7.emitters.length; var8++) {
    FadeEmitter var9 = var7.emitters[var8];
                     if (var9 != nullptr && var9.emitter != nullptr) {
                        this.paintSquare(var9.sq.x, var9.sq.y, var9.sq.z, 0.0F, 1.0F, 0.0F, 1.0F);
                     }

                     if (var7.refCount[var8] > 0) {
                        this.paintSquare(var4.wx * 10 + 5, var4.wy * 10 + 5, 0, 0.0F, 0.0F, 1.0F, 1.0F);
                     }
                  }

    IsoBuilding var10 = IsoPlayer.players[0].getCurrentBuilding();
                  if (var10 != nullptr && var7.buildingCorpseCount != nullptr && var7.buildingCorpseCount.containsKey(var10)) {
                     this.paintSquare(var4.wx * 10 + 5, var4.wy * 10 + 5, var6, 1.0F, 0.0F, 0.0F, 1.0F);
                  }
               }
            }
         }
      }
   }

    void paintSquare(int var1, int var2, int var3, float var4, float var5, float var6, float var7) {
    int var8 = Core.TileScale;
    int var9 = (int)IsoUtils.XToScreenExact(var1, var2 + 1, var3, 0);
    int var10 = (int)IsoUtils.YToScreenExact(var1, var2 + 1, var3, 0);
      SpriteRenderer.instance
         .renderPoly(var9, var10, var9 + 32 * var8, var10 - 16 * var8, var9 + 64 * var8, var10, var9 + 32 * var8, var10 + 16 * var8, var4, var5, var6, var7);
   }

    void chunkLoaded(IsoChunk var1) {
      if (var1.corpseData == nullptr) {
         var1.corpseData = new ChunkData(this, var1.wx, var1.wy);
      }

      var1.corpseData.wx = var1.wx;
      var1.corpseData.wy = var1.wy;
      var1.corpseData.Reset();
   }

    void corpseAdded(int var1, int var2, int var3) {
      if (var3 >= 0 && var3 < 8) {
    ChunkData var4 = this.getChunkData(var1, var2);
         if (var4 != nullptr) {
            var4.corpseAdded(var1, var2, var3);

            for (int var5 = 0; var5 < this.playerData.length; var5++) {
               if (var4.levelData[var3].refCount[var5] > 0) {
                  this.playerData[var5].forceUpdate = true;
               }
            }
         }
      } else {
         DebugLog.General.error("invalid z-coordinate %d,%d,%d", new Object[]{var1, var2, var3});
      }
   }

    void corpseRemoved(int var1, int var2, int var3) {
      if (var3 >= 0 && var3 < 8) {
    ChunkData var4 = this.getChunkData(var1, var2);
         if (var4 != nullptr) {
            var4.corpseRemoved(var1, var2, var3);

            for (int var5 = 0; var5 < this.playerData.length; var5++) {
               if (var4.levelData[var3].refCount[var5] > 0) {
                  this.playerData[var5].forceUpdate = true;
               }
            }
         }
      } else {
         DebugLog.General.error("invalid z-coordinate %d,%d,%d", new Object[]{var1, var2, var3});
      }
   }

    int getCorpseCount(IsoGameCharacter var1) {
      return var1 != nullptr && var1.getCurrentSquare() != nullptr
         ? this.getCorpseCount((int)var1.getX() / 10, (int)var1.getY() / 10, (int)var1.getZ(), var1.getBuilding())
         : 0;
   }

    int getCorpseCount(int var1, int var2, int var3, IsoBuilding var4) {
    int var5 = 0;

      for (int var6 = -1; var6 <= 1; var6++) {
         for (int var7 = -1; var7 <= 1; var7++) {
    ChunkData var8 = this.getChunkData((var1 + var7) * 10, (var2 + var6) * 10);
            if (var8 != nullptr) {
    ChunkLevelData var9 = var8.levelData[var3];
               if (var4 == nullptr) {
                  var5 += var9.corpseCount;
               } else if (var9.buildingCorpseCount != nullptr) {
    int var10 = (Integer)var9.buildingCorpseCount.get(var4);
                  if (var10 != nullptr) {
                     var5 += var10;
                  }
               }
            }
         }
      }

    return var5;
   }

    ChunkData getChunkData(int var1, int var2) {
    IsoChunk var3 = IsoWorld.instance.CurrentCell.getChunkForGridSquare(var1, var2, 0);
      return var3 != nullptr ? var3.corpseData : nullptr;
   }
}
} // namespace zombie
