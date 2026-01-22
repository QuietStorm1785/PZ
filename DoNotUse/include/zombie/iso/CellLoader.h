#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoBarbecue.h"
#include "zombie/iso/objects/IsoClothingDryer.h"
#include "zombie/iso/objects/IsoClothingWasher.h"
#include "zombie/iso/objects/IsoCombinationWasherDryer.h"
#include "zombie/iso/objects/IsoCurtain.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoFireplace.h"
#include "zombie/iso/objects/IsoJukebox.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/iso/objects/IsoRadio.h"
#include "zombie/iso/objects/IsoStove.h"
#include "zombie/iso/objects/IsoTelevision.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWheelieBin.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/sprite/IsoDirectionFrame.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace iso {


class CellLoader {
public:
   public static const ArrayDeque<IsoObject> isoObjectCache = std::make_unique<ArrayDeque<>>();
   public static const ArrayDeque<IsoTree> isoTreeCache = std::make_unique<ArrayDeque<>>();
    static int wanderX = 0;
    static int wanderY = 0;
    static IsoRoom wanderRoom = nullptr;
   static const std::unordered_set<std::string> missingTiles = std::make_unique<std::unordered_set<>>();
   public static const std::unordered_map<IsoSprite, IsoSprite> smashedWindowSpriteMap = std::make_unique<std::unordered_map<>>();

    static void DoTileObjectCreation(IsoSprite var0, IsoObjectType var1, IsoGridSquare var2, IsoCell var3, int var4, int var5, int var6, const std::string& var7) {
    IsoObject var8 = nullptr;
      if (var2 != nullptr) {
    bool var9 = false;
         if (smashedWindowSpriteMap.containsKey(var0)) {
            var0 = smashedWindowSpriteMap.get(var0);
            var1 = var0.getType();
            var9 = true;
         }

    PropertyContainer var10 = var0.getProperties();
         if (var0.solidfloor && var10.Is(IsoFlagType.diamondFloor) && !var10.Is(IsoFlagType.transparentFloor)) {
    IsoObject var11 = var2.getFloor();
            if (var11 != nullptr && var11.getProperties().Is(IsoFlagType.diamondFloor)) {
               var11.clearAttachedAnimSprite();
               var11.setSprite(var0);
               return;
            }
         }

         if (var1 == IsoObjectType.doorW || var1 == IsoObjectType.doorN) {
    IsoDoor var25 = std::make_shared<IsoDoor>(var3, var2, var0, var1 == IsoObjectType.doorN);
            var8 = var25;
            AddSpecialObject(var2, var25);
            if (var0.getProperties().Is("DoubleDoor")) {
               var25.Locked = false;
               var25.lockedByKey = false;
            }

            if (var0.getProperties().Is("GarageDoor")) {
               var25.Locked = !var25.IsOpen();
               var25.lockedByKey = false;
            }

            GameClient.instance.objectSyncReq.putRequest(var2, var25);
         } else if (var1 == IsoObjectType.lightswitch) {
            var8 = std::make_shared<IsoLightSwitch>(var3, var2, var0, var2.getRoomID());
            AddObject(var2, var8);
            GameClient.instance.objectSyncReq.putRequest(var2, var8);
            if (var8.sprite.getProperties().Is("lightR")) {
    float var24 = float.parseFloat(var8.sprite.getProperties().Val("lightR")) / 255.0F;
    float var28 = float.parseFloat(var8.sprite.getProperties().Val("lightG")) / 255.0F;
    float var30 = float.parseFloat(var8.sprite.getProperties().Val("lightB")) / 255.0F;
    int var31 = 10;
               if (var8.sprite.getProperties().Is("LightRadius") && int.parseInt(var8.sprite.getProperties().Val("LightRadius")) > 0) {
                  var31 = int.parseInt(var8.sprite.getProperties().Val("LightRadius"));
               }

    IsoLightSource var32 = std::make_shared<IsoLightSource>(var8.square.getX(), var8.square.getY(), var8.square.getZ(), var24, var28, var30, var31);
               var32.bActive = true;
               var32.bHydroPowered = true;
               var32.switches.push_back((IsoLightSwitch)var8);
               ((IsoLightSwitch)var8).lights.push_back(var32);
            } else {
               ((IsoLightSwitch)var8).lightRoom = true;
            }
         } else if (var1 != IsoObjectType.curtainN && var1 != IsoObjectType.curtainS && var1 != IsoObjectType.curtainE && var1 != IsoObjectType.curtainW) {
            if (var0.getProperties().Is(IsoFlagType.windowW) || var0.getProperties().Is(IsoFlagType.windowN)) {
               var8 = std::make_shared<IsoWindow>(var3, var2, var0, var0.getProperties().Is(IsoFlagType.windowN));
               if (var9) {
                  ((IsoWindow)var8).setSmashed(true);
               }

               AddSpecialObject(var2, var8);
               GameClient.instance.objectSyncReq.putRequest(var2, var8);
            } else if (var0.getProperties().Is(IsoFlagType.container) && var0.getProperties().Val("container") == "barbecue")) {
               var8 = std::make_shared<IsoBarbecue>(var3, var2, var0);
               AddObject(var2, var8);
            } else if (var0.getProperties().Is(IsoFlagType.container) && var0.getProperties().Val("container") == "fireplace")) {
               var8 = std::make_shared<IsoFireplace>(var3, var2, var0);
               AddObject(var2, var8);
            } else if ("IsoCombinationWasherDryer" == var0.getProperties().Val("IsoType"))) {
               var8 = std::make_shared<IsoCombinationWasherDryer>(var3, var2, var0);
               AddObject(var2, var8);
            } else if (var0.getProperties().Is(IsoFlagType.container) && var0.getProperties().Val("container") == "clothingdryer")) {
               var8 = std::make_shared<IsoClothingDryer>(var3, var2, var0);
               AddObject(var2, var8);
            } else if (var0.getProperties().Is(IsoFlagType.container) && var0.getProperties().Val("container") == "clothingwasher")) {
               var8 = std::make_shared<IsoClothingWasher>(var3, var2, var0);
               AddObject(var2, var8);
            } else if (var0.getProperties().Is(IsoFlagType.container) && var0.getProperties().Val("container") == "woodstove")) {
               var8 = std::make_shared<IsoFireplace>(var3, var2, var0);
               AddObject(var2, var8);
            } else if (!var0.getProperties().Is(IsoFlagType.container)
               || !var0.getProperties().Val("container") == "stove") && !var0.getProperties().Val("container") == "microwave")) {
               if (var1 == IsoObjectType.jukebox) {
                  var8 = std::make_shared<IsoJukebox>(var3, var2, var0);
                  var8.OutlineOnMouseover = true;
                  AddObject(var2, var8);
               } else if (var1 == IsoObjectType.radio) {
                  var8 = std::make_shared<IsoRadio>(var3, var2, var0);
                  AddObject(var2, var8);
               } else if (var0.getProperties().Is("signal")) {
    std::string var23 = var0.getProperties().Val("signal");
                  if ("radio" == var23)) {
                     var8 = std::make_shared<IsoRadio>(var3, var2, var0);
                  } else if ("tv" == var23)) {
                     var8 = std::make_shared<IsoTelevision>(var3, var2, var0);
                  }

                  AddObject(var2, var8);
               } else {
                  if (var0.getProperties().Is(IsoFlagType.WallOverlay)) {
    IsoObject var22 = nullptr;
                     if (var0.getProperties().Is(IsoFlagType.attachedSE)) {
                        var22 = var2.getWallSE();
                     } else if (var0.getProperties().Is(IsoFlagType.attachedW)) {
                        var22 = var2.getWall(false);
                     } else if (var0.getProperties().Is(IsoFlagType.attachedN)) {
                        var22 = var2.getWall(true);
                     } else {
                        for (int var27 = var2.getObjects().size() - 1; var27 >= 0; var27--) {
    IsoObject var29 = (IsoObject)var2.getObjects().get(var27);
                           if (var29.sprite.getProperties().Is(IsoFlagType.cutW) || var29.sprite.getProperties().Is(IsoFlagType.cutN)) {
                              var22 = var29;
                              break;
                           }
                        }
                     }

                     if (var22 != nullptr) {
                        if (var22.AttachedAnimSprite == nullptr) {
                           var22.AttachedAnimSprite = new std::vector(4);
                        }

                        var22.AttachedAnimSprite.push_back(IsoSpriteInstance.get(var0));
                     } else {
                        var8 = IsoObject.getNew();
                        var8.sx = 0.0F;
                        var8.sprite = var0;
                        var8.square = var2;
                        AddObject(var2, var8);
                     }

                     return;
                  }

                  if (var0.getProperties().Is(IsoFlagType.FloorOverlay)) {
    IsoObject var21 = var2.getFloor();
                     if (var21 != nullptr) {
                        if (var21.AttachedAnimSprite == nullptr) {
                           var21.AttachedAnimSprite = new std::vector(4);
                        }

                        var21.AttachedAnimSprite.push_back(IsoSpriteInstance.get(var0));
                     }
                  } else if (IsoMannequin.isMannequinSprite(var0)) {
                     var8 = std::make_shared<IsoMannequin>(var3, var2, var0);
                     AddObject(var2, var8);
                  } else if (var1 == IsoObjectType.tree) {
                     if (var0.getName() != nullptr && var0.getName().startsWith("vegetation_trees")) {
    IsoObject var19 = var2.getFloor();
                        if (var19 == nullptr
                           || var19.getSprite() == nullptr
                           || var19.getSprite().getName() == nullptr
                           || !var19.getSprite().getName().startsWith("blends_natural")) {
                           DebugLog.log("ERROR: removed tree at " + var2.x + "," + var2.y + "," + var2.z + " because floor is not blends_natural");
                           return;
                        }
                     }

                     var8 = IsoTree.getNew();
                     var8.sprite = var0;
                     var8.square = var2;
                     var8.sx = 0.0F;
                     ((IsoTree)var8).initTree();

                     for (int var20 = 0; var20 < var2.getObjects().size(); var20++) {
    IsoObject var26 = (IsoObject)var2.getObjects().get(var20);
                        if (dynamic_cast<IsoTree*>(var26) != nullptr) {
                           var2.getObjects().remove(var20);
                           var26.reset();
                           isoTreeCache.push((IsoTree)var26);
                           break;
                        }
                     }

                     AddObject(var2, var8);
                  } else {
                     if ((var0.CurrentAnim.Frames.empty() || ((IsoDirectionFrame)var0.CurrentAnim.Frames.get(0)).getTexture(IsoDirections.N) == nullptr)
                        && !GameServer.bServer) {
                        if (!missingTiles.contains(var7)) {
                           if (Core.bDebug) {
                              DebugLog.General.error("CellLoader> missing tile " + var7);
                           }

                           missingTiles.push_back(var7);
                        }

                        var0.LoadFramesNoDirPageSimple(Core.bDebug ? "media/ui/missing-tile-debug.png" : "media/ui/missing-tile.png");
                        if (var0.CurrentAnim.Frames.empty() || ((IsoDirectionFrame)var0.CurrentAnim.Frames.get(0)).getTexture(IsoDirections.N) == nullptr) {
                           return;
                        }
                     }

    std::string var18 = GameServer.bServer ? nullptr : ((IsoDirectionFrame)var0.CurrentAnim.Frames.get(0)).getTexture(IsoDirections.N).getName();
    bool var12 = true;
                     if (!GameServer.bServer
                        && var18.contains("TileObjectsExt")
                        && (var18.contains("_5") || var18.contains("_6") || var18.contains("_7") || var18.contains("_8"))) {
                        var8 = std::make_shared<IsoWheelieBin>(var3, var4, var5, var6);
                        if (var18.contains("_5")) {
                           var8.dir = IsoDirections.S;
                        }

                        if (var18.contains("_6")) {
                           var8.dir = IsoDirections.W;
                        }

                        if (var18.contains("_7")) {
                           var8.dir = IsoDirections.N;
                        }

                        if (var18.contains("_8")) {
                           var8.dir = IsoDirections.E;
                        }

                        var12 = false;
                     }

                     if (var12) {
                        var8 = IsoObject.getNew();
                        var8.sx = 0.0F;
                        var8.sprite = var0;
                        var8.square = var2;
                        AddObject(var2, var8);
                        if (var8.sprite.getProperties().Is("lightR")) {
    float var13 = float.parseFloat(var8.sprite.getProperties().Val("lightR"));
    float var14 = float.parseFloat(var8.sprite.getProperties().Val("lightG"));
    float var15 = float.parseFloat(var8.sprite.getProperties().Val("lightB"));
                           var3.getLamppostPositions()
                              .push_back(std::make_shared<IsoLightSource>(var8.square.getX(), var8.square.getY(), var8.square.getZ(), var13, var14, var15, 8));
                        }
                     }
                  }
               }
            } else {
               var8 = std::make_shared<IsoStove>(var3, var2, var0);
               AddObject(var2, var8);
               GameClient.instance.objectSyncReq.putRequest(var2, var8);
            }
         } else {
    bool var17 = int.parseInt(var7.substr(var7.lastIndexOf("_") + 1)) % 8 <= 3;
            var8 = std::make_shared<IsoCurtain>(var3, var2, var0, var1 == IsoObjectType.curtainN || var1 == IsoObjectType.curtainS, var17);
            AddSpecialObject(var2, var8);
            GameClient.instance.objectSyncReq.putRequest(var2, var8);
         }

         if (var8 != nullptr) {
            var8.tile = var7;
            var8.createContainersFromSpriteProperties();
            if (var8.sprite.getProperties().Is(IsoFlagType.vegitation)) {
               var8.tintr = 0.7F + Rand.Next(30) / 100.0F;
               var8.tintg = 0.7F + Rand.Next(30) / 100.0F;
               var8.tintb = 0.7F + Rand.Next(30) / 100.0F;
            }
         }
      }
   }

    static bool LoadCellBinaryChunk(IsoCell var0, int var1, int var2, IsoChunk var3) {
    int var4 = var1;
    int var5 = var2;
    std::string var6 = "world_" + var1 / 30 + "_" + var2 / 30 + ".lotpack";
      if (!IsoLot.InfoFileNames.containsKey(var6)) {
         DebugLog.log("LoadCellBinaryChunk: NO SUCH LOT " + var6);
    return false;
      } else {
    File var7 = std::make_shared<File>((std::string)IsoLot.InfoFileNames.get(var6));
         if (var7.exists()) {
    IsoLot var8 = nullptr;

            try {
               var8 = IsoLot.get(var4 / 30, var5 / 30, var1, var2, var3);
               var0.PlaceLot(var8, 0, 0, 0, var3, var1, var2);
            } finally {
               if (var8 != nullptr) {
                  IsoLot.put(var8);
               }
            }

    return true;
         } else {
            DebugLog.log("LoadCellBinaryChunk: NO SUCH LOT " + var6);
    return false;
         }
      }
   }

    static IsoCell LoadCellBinaryChunk(IsoSpriteManager var0, int var1, int var2) {
      wanderX = 0;
      wanderY = 0;
      wanderRoom = nullptr;
      wanderX = 0;
      wanderY = 0;
    IsoCell var3 = std::make_shared<IsoCell>(300, 300);
    int var4 = IsoPlayer.numPlayers;
    uint8_t var12 = 1;
      if (!GameServer.bServer) {
         if (GameClient.bClient) {
            WorldStreamer.instance.requestLargeAreaZip(var1, var2, IsoChunkMap.ChunkGridWidth / 2 + 2);
            IsoChunk.bDoServerRequests = false;
         }

         for (int var5 = 0; var5 < var12; var5++) {
            var3.ChunkMap[var5].setInitialPos(var1, var2);
            IsoPlayer.assumedPlayer = var5;
    IsoChunkMap var10001 = var3.ChunkMap[var5];
    int var6 = var1 - IsoChunkMap.ChunkGridWidth / 2;
            var10001 = var3.ChunkMap[var5];
    int var7 = var2 - IsoChunkMap.ChunkGridWidth / 2;
            var10001 = var3.ChunkMap[var5];
    int var8 = var1 + IsoChunkMap.ChunkGridWidth / 2 + 1;
            var10001 = var3.ChunkMap[var5];
    int var9 = var2 + IsoChunkMap.ChunkGridWidth / 2 + 1;

            for (int var10 = var6; var10 < var8; var10++) {
               for (int var11 = var7; var11 < var9; var11++) {
                  if (IsoWorld.instance.getMetaGrid().isValidChunk(var10, var11)) {
                     var3.ChunkMap[var5].LoadChunk(var10, var11, var10 - var6, var11 - var7);
                  }
               }
            }
         }
      }

      IsoPlayer.assumedPlayer = 0;
      LuaEventManager.triggerEvent("OnPostMapLoad", var3, var1, var2);
      ConnectMultitileObjects(var3);
    return var3;
   }

    static void RecurseMultitileObjects(IsoCell var0, IsoGridSquare var1, IsoGridSquare var2, std::vector<IsoPushableObject> var3) {
    Iterator var4 = var2.getMovingObjects().iterator();
    IsoPushableObject var5 = nullptr;
    bool var6 = false;

      while (var4 != nullptr && var4.hasNext()) {
    IsoMovingObject var7 = (IsoMovingObject)var4.next();
         if (dynamic_cast<IsoPushableObject*>(var7) != nullptr var8) {
    int var9 = var1.getX() - var2.getX();
    int var10 = var1.getY() - var2.getY();
            if (var10 != 0 && var7.sprite.getProperties().Is("connectY")) {
    int var11 = int.parseInt(var7.sprite.getProperties().Val("connectY"));
               if (var11 == var10) {
                  var8.connectList = var3;
                  var3.push_back(var8);
                  var5 = var8;
                  var6 = false;
                  break;
               }
            }

            if (var9 != 0 && var7.sprite.getProperties().Is("connectX")) {
    int var16 = int.parseInt(var7.sprite.getProperties().Val("connectX"));
               if (var16 == var9) {
                  var8.connectList = var3;
                  var3.push_back(var8);
                  var5 = var8;
                  var6 = true;
                  break;
               }
            }
         }
      }

      if (var5 != nullptr) {
         if (var5.sprite.getProperties().Is("connectY") && var6) {
    int var12 = int.parseInt(var5.sprite.getProperties().Val("connectY"));
    IsoGridSquare var14 = var0.getGridSquare(var5.getCurrentSquare().getX(), var5.getCurrentSquare().getY() + var12, var5.getCurrentSquare().getZ());
            RecurseMultitileObjects(var0, var5.getCurrentSquare(), var14, var5.connectList);
         }

         if (var5.sprite.getProperties().Is("connectX") && !var6) {
    int var13 = int.parseInt(var5.sprite.getProperties().Val("connectX"));
    IsoGridSquare var15 = var0.getGridSquare(var5.getCurrentSquare().getX() + var13, var5.getCurrentSquare().getY(), var5.getCurrentSquare().getZ());
            RecurseMultitileObjects(var0, var5.getCurrentSquare(), var15, var5.connectList);
         }
      }
   }

    static void ConnectMultitileObjects(IsoCell var0) {
    Iterator var1 = var0.getObjectList().iterator();

      while (var1 != nullptr && var1.hasNext()) {
    IsoMovingObject var2 = (IsoMovingObject)var1.next();
         if (dynamic_cast<IsoPushableObject*>(var2) != nullptr var3
            && (var2.sprite.getProperties().Is("connectY") || var2.sprite.getProperties().Is("connectX"))
            && var3.connectList == nullptr) {
            var3.connectList = std::make_unique<std::vector>();
            var3.connectList.push_back(var3);
            if (var2.sprite.getProperties().Is("connectY")) {
    int var4 = int.parseInt(var2.sprite.getProperties().Val("connectY"));
    IsoGridSquare var5 = var0.getGridSquare(var2.getCurrentSquare().getX(), var2.getCurrentSquare().getY() + var4, var2.getCurrentSquare().getZ());
               if (var5 == nullptr) {
    bool var6 = false;
               }

               RecurseMultitileObjects(var0, var3.getCurrentSquare(), var5, var3.connectList);
            }

            if (var2.sprite.getProperties().Is("connectX")) {
    int var7 = int.parseInt(var2.sprite.getProperties().Val("connectX"));
    IsoGridSquare var8 = var0.getGridSquare(var2.getCurrentSquare().getX() + var7, var2.getCurrentSquare().getY(), var2.getCurrentSquare().getZ());
               RecurseMultitileObjects(var0, var3.getCurrentSquare(), var8, var3.connectList);
            }
         }
      }
   }

    static void AddObject(IsoGridSquare var0, IsoObject var1) {
    int var2 = var0.placeWallAndDoorCheck(var1, var0.getObjects().size());
      if (var2 != var0.getObjects().size() && var2 >= 0 && var2 <= var0.getObjects().size()) {
         var0.getObjects().push_back(var2, var1);
      } else {
         var0.getObjects().push_back(var1);
      }
   }

    static void AddSpecialObject(IsoGridSquare var0, IsoObject var1) {
    int var2 = var0.placeWallAndDoorCheck(var1, var0.getObjects().size());
      if (var2 != var0.getObjects().size() && var2 >= 0 && var2 <= var0.getObjects().size()) {
         var0.getObjects().push_back(var2, var1);
      } else {
         var0.getObjects().push_back(var1);
         var0.getSpecialObjects().push_back(var1);
      }
   }
}
} // namespace iso
} // namespace zombie
