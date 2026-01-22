#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/WorldReuserThread.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/ServerChunkLoader/GetSquare.h"
#include "zombie/network/ServerMap/ServerCell.h"
#include <algorithm>

namespace zombie {
namespace network {


class ServerChunkLoader {
public:
   private const LinkedBlockingQueue<ServerCell> toThread;
   private const LinkedBlockingQueue<ServerCell> fromThread;
    const GetSquare serverCellGetSquare;

   private ServerChunkLoader$RecalcAllThread(ServerChunkLoader var1) {
      this.this$0 = var1;
      this.toThread = std::make_unique<LinkedBlockingQueue<>>();
      this.fromThread = std::make_unique<LinkedBlockingQueue<>>();
      this.serverCellGetSquare = std::make_shared<GetSquare>(this.this$0);
   }

    void run() {
      while (true) {
         try {
            this.runInner();
         } catch (Exception var2) {
            var2.printStackTrace();
         }
      }
   }

    void runInner() {
      MPStatistic.getInstance().RecalcAllThread.End();
    ServerCell var1 = this.toThread.take();
      MPStatistic.getInstance().RecalcAllThread.Start();
      if (var1.bCancelLoading && !this.hasAnyBrandNewChunks(var1)) {
         for (int var18 = 0; var18 < 5; var18++) {
            for (int var3 = 0; var3 < 5; var3++) {
    IsoChunk var19 = var1.chunks[var3][var18];
               if (var19 != nullptr) {
                  var1.chunks[var3][var18] = nullptr;
                  WorldReuserThread.instance.addReuseChunk(var19);
               }
            }
         }

         if (this.this$0.MapLoading) {
            DebugLog.log(DebugType.MapLoading, "RecalcAllThread: cancelled " + var1.WX + "," + var1.WY);
         }

         var1.bLoadingWasCancelled = true;
      } else {
    long var2 = System.nanoTime();
         this.serverCellGetSquare.cell = var1;
    int var4 = var1.WX * 50;
    int var5 = var1.WY * 50;
    int var6 = var4 + 50;
    int var7 = var5 + 50;
    int var8 = 0;
    uint8_t var9 = 100;

         for (int var10 = 0; var10 < 5; var10++) {
            for (int var11 = 0; var11 < 5; var11++) {
    IsoChunk var12 = var1.chunks[var10][var11];
               if (var12 != nullptr) {
                  var12.bLoaded = false;

                  for (int var13 = 0; var13 < var9; var13++) {
                     for (int var14 = 0; var14 <= var12.maxLevel; var14++) {
    IsoGridSquare var15 = var12.squares[var14][var13];
                        if (var14 == 0) {
                           if (var15 == nullptr) {
    int var16 = var12.wx * 10 + var13 % 10;
    int var17 = var12.wy * 10 + var13 / 10;
                              var15 = IsoGridSquare.getNew(IsoWorld.instance.CurrentCell, nullptr, var16, var17, var14);
                              var12.setSquare(var16 % 10, var17 % 10, var14, var15);
                           }

                           if (var15.getFloor() == nullptr) {
                              DebugLog.log("ERROR: added floor at " + var15.x + "," + var15.y + "," + var15.z + " because there wasn't one");
    IsoObject var35 = IsoObject.getNew();
                              var35.sprite = IsoSprite.getSprite(IsoSpriteManager.instance, "carpentry_02_58", 0);
                              var35.square = var15;
                              var15.getObjects().push_back(0, var35);
                           }
                        }

                        if (var15 != nullptr) {
                           var15.RecalcProperties();
                        }
                     }
                  }

                  if (var12.maxLevel > var8) {
                     var8 = var12.maxLevel;
                  }
               }
            }
         }

         for (int var20 = 0; var20 < 5; var20++) {
            for (int var23 = 0; var23 < 5; var23++) {
    IsoChunk var25 = var1.chunks[var20][var23];
               if (var25 != nullptr) {
                  for (int var27 = 0; var27 < var9; var27++) {
                     for (int var29 = 0; var29 <= var25.maxLevel; var29++) {
    IsoGridSquare var32 = var25.squares[var29][var27];
                        if (var32 != nullptr) {
                           if (var29 > 0 && !var32.getObjects().empty()) {
                              this.serverCellGetSquare.EnsureSurroundNotNull(var32.x - var4, var32.y - var5, var29);
                           }

                           var32.RecalcAllWithNeighbours(true, this.serverCellGetSquare);
                        }
                     }
                  }
               }
            }
         }

         for (int var21 = 0; var21 < 5; var21++) {
            for (int var24 = 0; var24 < 5; var24++) {
    IsoChunk var26 = var1.chunks[var21][var24];
               if (var26 != nullptr) {
                  for (int var28 = 0; var28 < var9; var28++) {
                     for (int var30 = var26.maxLevel; var30 > 0; var30--) {
    IsoGridSquare var33 = var26.squares[var30][var28];
                        if (var33 != nullptr && var33.Is(IsoFlagType.solidfloor)) {
                           var30--;

                           for (; var30 >= 0; var30--) {
                              var33 = var26.squares[var30][var28];
                              if (var33 != nullptr) {
                                 var33.haveRoof = true;
                                 var33.getProperties().UnSet(IsoFlagType.exterior);
                              }
                           }
                           break;
                        }
                     }
                  }
               }
            }
         }

         if (GameServer.bDebug && this.this$0.debugSlowMapLoadingDelay > 0L) {
            Thread.sleep(this.this$0.debugSlowMapLoadingDelay);
         }

    float var22 = (float)(System.nanoTime() - var2) / 1000000.0F;
         if (this.this$0.MapLoading) {
            DebugLog.log(DebugType.MapLoading, "RecalcAll for cell " + var1.WX + "," + var1.WY + " ms=" + var22);
         }

         this.fromThread.push_back(var1);
      }
   }

    bool hasAnyBrandNewChunks(ServerCell var1) {
      for (int var2 = 0; var2 < 5; var2++) {
         for (int var3 = 0; var3 < 5; var3++) {
    IsoChunk var4 = var1.chunks[var3][var2];
            if (var4 != nullptr && !var4.getErosionData().init) {
    return true;
            }
         }
      }

    return false;
   }
}
} // namespace network
} // namespace zombie
