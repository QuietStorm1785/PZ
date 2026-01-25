#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoGameCharacter/TorchInfo.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/opengl/RenderSettings/PlayerRenderSettings.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoCurtain.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoGenerator.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleLight.h"
#include "zombie/vehicles/VehiclePart.h"
#include <algorithm>

namespace zombie {
namespace iso {


class LightingJNI {
public:
   // Stubs for static methods ported from Java
   static inline bool init = false;
   static void DoLightingUpdateNew(long /*time*/) {}
   static bool WaitingForMain() { return false; }
    static const int ROOM_SPAWN_DIST = 50;
    static bool init = false;
   public static const int[][] ForcedVis = new int[][]{
      {-1, 0, -1, -1, 0, -1, 1, -1, 1, 0, -2, -2, -1, -2, 0, -2, 1, -2, 2, -2},
      {-1, 1, -1, 0, -1, -1, 0, -1, 1, -1, -2, 0, -2, -1, -2, -2, -1, -2, 0, -2},
      {0, 1, -1, 1, -1, 0, -1, -1, 0, -1, -2, 2, -2, 1, -2, 0, -2, -1, -2, -2},
      {1, 1, 0, 1, -1, 1, -1, 0, -1, -1, 0, 2, -1, 2, -2, 2, -2, 1, -2, 0},
      {1, 0, 1, 1, 0, 1, -1, 1, -1, 0, 2, 2, 1, 2, 0, 2, -1, 2, -2, 2},
      {-1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 2, 0, 2, 1, 2, 2, 1, 2, 0, 2},
      {0, 1, 1, 1, 1, 0, 1, -1, 0, -1, 2, -2, 2, -1, 2, 0, 2, 1, 2, 2},
      {-1, -1, 0, -1, 1, -1, 1, 0, 1, 1, 0, -2, 1, -2, 2, -2, 2, -1, 2, 0}
   };
   private static const std::vector<TorchInfo> torches = std::make_unique<std::vector<>>();
   private static const std::vector<TorchInfo> activeTorches = std::make_unique<std::vector<>>();
   private static const std::vector<IsoLightSource> JNILights = std::make_unique<std::vector<>>();
   private static const int[] updateCounter = new int[4];
    static bool bWasElecShut = false;
    static bool bWasNight = false;
    static const Vector2 tempVector2 = std::make_shared<Vector2>();
    static const int MAX_PLAYERS = 256;
    static const int MAX_LIGHTS_PER_PLAYER = 4;
    static const int MAX_LIGHTS_PER_VEHICLE = 10;
   private static const std::vector<InventoryItem> tempItems = std::make_unique<std::vector<>>();

    static void init() {
      if (!init) {
    std::string var0 = "";
         if ("1" == System.getProperty("zomboid.debuglibs.lighting"))) {
            DebugLog.log("***** Loading debug version of Lighting");
            var0 = "d";
         }

         try {
            if (System.getProperty("os.name").contains("OS X")) {
               System.loadLibrary("Lighting");
            } else if (System.getProperty("os.name").startsWith("Win")) {
               if (System.getProperty("sun.arch.data.model") == "64")) {
                  System.loadLibrary("Lighting64" + var0);
               } else {
                  System.loadLibrary("Lighting32" + var0);
               }
            } else if (System.getProperty("sun.arch.data.model") == "64")) {
               System.loadLibrary("Lighting64");
            } else {
               System.loadLibrary("Lighting32");
            }

            for (int var1 = 0; var1 < 4; var1++) {
               updateCounter[var1] = -1;
            }

            configure(0.005F);
            init = true;
         } catch (UnsatisfiedLinkError var4) {
            var4.printStackTrace();

            try {
               Thread.sleep(3000L);
            } catch (InterruptedException var3) {
            }

            System.exit(1);
         }
      }
   }

    static int getTorchIndexById(int var0) {
      for (int var1 = 0; var1 < torches.size(); var1++) {
    TorchInfo var2 = torches.get(var1);
         if (var2.id == var0) {
    return var1;
         }
      }

      return -1;
   }

    static void checkTorch(IsoPlayer var0, InventoryItem var1, int var2) {
    int var3 = getTorchIndexById(var2);
    TorchInfo var4;
      if (var3 == -1) {
         var4 = TorchInfo.alloc();
         torches.push_back(var4);
      } else {
         var4 = torches.get(var3);
      }

      var4.set(var0, var1);
      if (var4.id == 0) {
         var4.id = var2;
      }

      updateTorch(var4.id, var4.x, var4.y, var4.z, var4.angleX, var4.angleY, var4.dist, var4.strength, var4.bCone, var4.dot, var4.focusing);
      activeTorches.push_back(var4);
   }

    static int checkPlayerTorches(IsoPlayer var0, int var1) {
    std::vector var2 = tempItems;
      var2.clear();
      var0.getActiveLightItems(var2);
    int var3 = Math.min(var2.size(), 4);

      for (int var4 = 0; var4 < var3; var4++) {
         checkTorch(var0, (InventoryItem)var2.get(var4), var1 * 4 + var4 + 1);
      }

    return var3;
   }

    static void clearPlayerTorches(int var0, int var1) {
      for (int var2 = var1; var2 < 4; var2++) {
    int var3 = var0 * 4 + var2 + 1;
    int var4 = getTorchIndexById(var3);
         if (var4 != -1) {
    TorchInfo var5 = torches.get(var4);
            removeTorch(var5.id);
            var5.id = 0;
            TorchInfo.release(var5);
            torches.remove(var4);
            break;
         }
      }
   }

    static void checkTorch(VehiclePart var0, int var1) {
    VehicleLight var2 = var0.getLight();
      if (var2 != nullptr && var2.getActive()) {
    TorchInfo var5 = nullptr;

         for (int var6 = 0; var6 < torches.size(); var6++) {
            var5 = torches.get(var6);
            if (var5.id == var1) {
               break;
            }

            var5 = nullptr;
         }

         if (var5 == nullptr) {
            var5 = TorchInfo.alloc();
            torches.push_back(var5);
         }

         var5.set(var0);
         if (var5.id == 0) {
            var5.id = var1;
         }

         updateTorch(var5.id, var5.x, var5.y, var5.z, var5.angleX, var5.angleY, var5.dist, var5.strength, var5.bCone, var5.dot, var5.focusing);
         activeTorches.push_back(var5);
      } else {
         for (int var3 = 0; var3 < torches.size(); var3++) {
    TorchInfo var4 = torches.get(var3);
            if (var4.id == var1) {
               removeTorch(var4.id);
               var4.id = 0;
               TorchInfo.release(var4);
               torches.remove(var3--);
            }
         }
      }
   }

    static void checkLights() {
      if (IsoWorld.instance.CurrentCell != nullptr) {
         if (GameClient.bClient) {
            IsoGenerator.updateSurroundingNow();
         }

    bool var0 = IsoWorld.instance.isHydroPowerOn();
    std::stack var1 = IsoWorld.instance.CurrentCell.getLamppostPositions();

         for (int var2 = 0; var2 < var1.size(); var2++) {
    IsoLightSource var3 = (IsoLightSource)var1.get(var2);
    IsoChunk var4 = IsoWorld.instance.CurrentCell.getChunkForGridSquare(var3.x, var3.y, var3.z);
            if (var4 != nullptr && var3.chunk != nullptr && var3.chunk != var4) {
               var3.life = 0;
            }

            if (var3.life != 0 && var3.isInBounds()) {
               if (var3.bHydroPowered) {
                  if (var3.switches.empty()) {
    assert false;

    bool var23 = var0;
                     if (!var0) {
    IsoGridSquare var29 = IsoWorld.instance.CurrentCell.getGridSquare(var3.x, var3.y, var3.z);
                        var23 = var29 != nullptr && var29.haveElectricity();
                     }

                     if (var3.bActive != var23) {
                        var3.bActive = var23;
                        GameTime.instance.lightSourceUpdate = 100.0F;
                     }
                  } else {
    IsoLightSwitch var6 = (IsoLightSwitch)var3.switches.get(0);
    bool var22 = var6.canSwitchLight();
                     if (var6.bStreetLight && GameTime.getInstance().getNight() < 0.5F) {
                        var22 = false;
                     }

                     if (var3.bActive && !var22) {
                        var3.bActive = false;
                        GameTime.instance.lightSourceUpdate = 100.0F;
                     } else if (!var3.bActive && var22 && var6.isActivated()) {
                        var3.bActive = true;
                        GameTime.instance.lightSourceUpdate = 100.0F;
                     }
                  }
               }

               if (var3.ID == 0) {
                  var3.ID = IsoLightSource.NextID++;
                  if (var3.life != -1) {
                     addTempLight(
                        var3.ID, var3.x, var3.y, var3.z, var3.radius, var3.r, var3.g, var3.b, (int)(var3.life * PerformanceSettings.getLockFPS() / 30.0F)
                     );
                     var1.remove(var2--);
                  } else {
                     var3.rJNI = var3.r;
                     var3.gJNI = var3.g;
                     var3.bJNI = var3.b;
                     var3.bActiveJNI = var3.bActive;
                     JNILights.push_back(var3);
                     addLight(
                        var3.ID,
                        var3.x,
                        var3.y,
                        var3.z,
                        var3.radius,
                        var3.r,
                        var3.g,
                        var3.b,
                        var3.localToBuilding == nullptr ? -1 : var3.localToBuilding.ID,
                        var3.bActive
                     );
                  }
               } else {
                  if (var3.r != var3.rJNI || var3.g != var3.gJNI || var3.b != var3.bJNI) {
                     var3.rJNI = var3.r;
                     var3.gJNI = var3.g;
                     var3.bJNI = var3.b;
                     setLightColor(var3.ID, var3.r, var3.g, var3.b);
                  }

                  if (var3.bActiveJNI != var3.bActive) {
                     var3.bActiveJNI = var3.bActive;
                     setLightActive(var3.ID, var3.bActive);
                  }
               }
            } else {
               var1.remove(var2);
               if (var3.ID != 0) {
    int var5 = var3.ID;
                  var3.ID = 0;
                  JNILights.remove(var3);
                  removeLight(var5);
                  GameTime.instance.lightSourceUpdate = 100.0F;
               }

               var2--;
            }
         }

         for (int var8 = 0; var8 < JNILights.size(); var8++) {
    IsoLightSource var10 = JNILights.get(var8);
            if (!var1.contains(var10)) {
    int var16 = var10.ID;
               var10.ID = 0;
               JNILights.remove(var8--);
               removeLight(var16);
            }
         }

    std::vector var9 = IsoWorld.instance.CurrentCell.roomLights;

         for (int var11 = 0; var11 < var9.size(); var11++) {
    IsoRoomLight var17 = (IsoRoomLight)var9.get(var11);
            if (!var17.isInBounds()) {
               var9.remove(var11--);
               if (var17.ID != 0) {
    int var25 = var17.ID;
                  var17.ID = 0;
                  removeRoomLight(var25);
                  GameTime.instance.lightSourceUpdate = 100.0F;
               }
            } else {
               var17.bActive = var17.room.def.bLightsActive;
               if (!var0) {
    bool var24 = false;

                  for (int var30 = 0; !var24 && var30 < var17.room.lightSwitches.size(); var30++) {
    IsoLightSwitch var7 = (IsoLightSwitch)var17.room.lightSwitches.get(var30);
                     if (var7.square != nullptr && var7.square.haveElectricity()) {
                        var24 = true;
                     }
                  }

                  if (!var24 && var17.bActive) {
                     var17.bActive = false;
                     if (var17.bActiveJNI) {
                        IsoGridSquare.RecalcLightTime = -1;
                        GameTime.instance.lightSourceUpdate = 100.0F;
                     }
                  } else if (var24 && var17.bActive && !var17.bActiveJNI) {
                     IsoGridSquare.RecalcLightTime = -1;
                     GameTime.instance.lightSourceUpdate = 100.0F;
                  }
               }

               if (var17.ID == 0) {
                  var17.ID = 100000 + IsoRoomLight.NextID++;
                  addRoomLight(var17.ID, var17.room.building.ID, var17.room.def.ID, var17.x, var17.y, var17.z, var17.width, var17.height, var17.bActive);
                  var17.bActiveJNI = var17.bActive;
                  GameTime.instance.lightSourceUpdate = 100.0F;
               } else if (var17.bActiveJNI != var17.bActive) {
                  setRoomLightActive(var17.ID, var17.bActive);
                  var17.bActiveJNI = var17.bActive;
                  GameTime.instance.lightSourceUpdate = 100.0F;
               }
            }
         }

         activeTorches.clear();
         if (GameClient.bClient) {
    std::vector var12 = GameClient.instance.getPlayers();

            for (int var18 = 0; var18 < var12.size(); var18++) {
    IsoPlayer var26 = (IsoPlayer)var12.get(var18);
               checkPlayerTorches(var26, var26.OnlineID + 1);
            }
         } else {
            for (int var13 = 0; var13 < IsoPlayer.numPlayers; var13++) {
    IsoPlayer var19 = IsoPlayer.players[var13];
               if (var19 != nullptr && !var19.isDead() && var19.getVehicle() == nullptr) {
    int var27 = checkPlayerTorches(var19, var13);
                  clearPlayerTorches(var13, var27);
               } else {
                  clearPlayerTorches(var13, 0);
               }
            }
         }

         for (int var14 = 0; var14 < IsoWorld.instance.CurrentCell.getVehicles().size(); var14++) {
    BaseVehicle var20 = (BaseVehicle)IsoWorld.instance.CurrentCell.getVehicles().get(var14);
            if (var20.VehicleID != -1) {
               for (int var28 = 0; var28 < var20.getLightCount(); var28++) {
    VehiclePart var31 = var20.getLightByIndex(var28);
                  checkTorch(var31, 1024 + var20.VehicleID * 10 + var28);
               }
            }
         }

         for (int var15 = 0; var15 < torches.size(); var15++) {
    TorchInfo var21 = torches.get(var15);
            if (!activeTorches.contains(var21)) {
               removeTorch(var21.id);
               var21.id = 0;
               TorchInfo.release(var21);
               torches.remove(var15--);
            }
         }
      }
   }

    static float calculateVisionCone(IsoGameCharacter var0) {
    float var3;
      if (var0.getVehicle() == nullptr) {
         var3 = -0.2F;
         var3 -= var0.getStats().fatigue - 0.6F;
         if (var3 > -0.2F) {
            var3 = -0.2F;
         }

         if (var0.getStats().fatigue >= 1.0F) {
            var3 -= 0.2F;
         }

         if (var0.getMoodles().getMoodleLevel(MoodleType.Panic) == 4) {
            var3 -= 0.2F;
         }

         if (var0.isInARoom()) {
            var3 -= 0.2F * (1.0F - ClimateManager.getInstance().getDayLightStrength());
         } else {
            var3 -= 0.7F * (1.0F - ClimateManager.getInstance().getDayLightStrength());
         }

         if (var3 < -0.9F) {
            var3 = -0.9F;
         }

         if (var0.Traits.EagleEyed.isSet()) {
            var3 += 0.2F * ClimateManager.getInstance().getDayLightStrength();
         }

         if (var0.Traits.NightVision.isSet()) {
            var3 += 0.2F * (1.0F - ClimateManager.getInstance().getDayLightStrength());
         }

         if (var3 > 0.0F) {
            var3 = 0.0F;
         }
      } else {
         if (var0.getVehicle().getHeadlightsOn() && var0.getVehicle().getHeadlightCanEmmitLight()) {
            var3 = 0.8F - 3.0F * (1.0F - ClimateManager.getInstance().getDayLightStrength());
            if (var3 < -0.8F) {
               var3 = -0.8F;
            }
         } else {
            var3 = 0.8F - 3.0F * (1.0F - ClimateManager.getInstance().getDayLightStrength());
            if (var3 < -0.95F) {
               var3 = -0.95F;
            }
         }

         if (var0.Traits.NightVision.isSet()) {
            var3 += 0.2F * (1.0F - ClimateManager.getInstance().getDayLightStrength());
         }

         if (var3 > 1.0F) {
            var3 = 1.0F;
         }
      }

    return var3;
   }

    static void updatePlayer(int var0) {
    IsoPlayer var1 = IsoPlayer.players[var0];
      if (var1 != nullptr) {
    float var2 = var1.getStats().fatigue - 0.6F;
         if (var2 < 0.0F) {
            var2 = 0.0F;
         }

         var2 *= 2.5F;
         if (var1.Traits.HardOfHearing.isSet() && var2 < 0.7F) {
            var2 = 0.7F;
         }

    float var3 = 2.0F;
         if (var1.Traits.KeenHearing.isSet()) {
            var3 += 3.0F;
         }

    float var4 = calculateVisionCone(var1);
    Vector2 var5 = var1.getLookVector(tempVector2);
    BaseVehicle var6 = var1.getVehicle();
         if (var6 != nullptr && !var1.isAiming() && !var1.isLookingWhileInVehicle() && var6.isDriver(var1) && var6.getCurrentSpeedKmHour() < -1.0F) {
            var5.rotate((float) Math.PI);
         }

         playerSet(
            var1.x,
            var1.y,
            var1.z,
            var5.x,
            var5.y,
            false,
            var1.ReanimatedCorpse != nullptr,
            var1.isGhostMode(),
            var1.Traits.ShortSighted.isSet(),
            var2,
            var3,
            var4
         );
      }
   }

    static void updateChunk(IsoChunk var0) {
      chunkBeginUpdate(var0.wx, var0.wy);

      for (int var1 = 0; var1 < IsoCell.MaxHeight; var1++) {
         for (int var2 = 0; var2 < 10; var2++) {
            for (int var3 = 0; var3 < 10; var3++) {
    IsoGridSquare var4 = var0.getGridSquare(var3, var2, var1);
               if (var4 == nullptr) {
                  squareSetNull(var3, var2, var1);
               } else {
                  squareBeginUpdate(var3, var2, var1);
    int var5 = var4.visionMatrix;
                  boolean var6 = var4.Has(IsoObjectType.stairsTN)
                     || var4.Has(IsoObjectType.stairsMN)
                     || var4.Has(IsoObjectType.stairsTW)
                     || var4.Has(IsoObjectType.stairsMW);
                  squareSet(
                     var4.w != nullptr,
                     var4.n != nullptr,
                     var4.e != nullptr,
                     var4.s != nullptr,
                     var6,
                     var5,
                     var4.getRoom() != nullptr ? var4.getBuilding().ID : -1,
                     var4.getRoomID()
                  );

                  for (int var7 = 0; var7 < var4.getSpecialObjects().size(); var7++) {
    IsoObject var8 = (IsoObject)var4.getSpecialObjects().get(var7);
                     if (dynamic_cast<IsoCurtain*>(var8) != nullptr var9) {
    uint8_t var10 = 0;
                        if (var9.getType() == IsoObjectType.curtainW) {
                           var10 |= 4;
                        } else if (var9.getType() == IsoObjectType.curtainN) {
                           var10 |= 8;
                        } else if (var9.getType() == IsoObjectType.curtainE) {
                           var10 |= 16;
                        } else if (var9.getType() == IsoObjectType.curtainS) {
                           var10 |= 32;
                        }

                        squareAddCurtain(var10, var9.open);
                     } else if (dynamic_cast<IsoDoor*>(var8) != nullptr var15) {
    bool var18 = var15.sprite != nullptr && var15.sprite.getProperties().Is("doorTrans");
                        if (var15.open) {
                           var18 = true;
                        } else {
                           var18 = var18 && (var15.HasCurtains() == nullptr || var15.isCurtainOpen());
                        }

    IsoBarricade var11 = var15.getBarricadeOnSameSquare();
    IsoBarricade var12 = var15.getBarricadeOnOppositeSquare();
                        if (var11 != nullptr && var11.isBlockVision()) {
                           var18 = false;
                        }

                        if (var12 != nullptr && var12.isBlockVision()) {
                           var18 = false;
                        }

                        if (var15.IsOpen() && IsoDoor.getGarageDoorIndex(var15) != -1) {
                           var18 = true;
                        }

                        squareAddDoor(var15.north, var15.open, var18);
                     } else if (dynamic_cast<IsoThumpable*>(var8) != nullptr var16) {
    bool var20 = var16.getSprite().getProperties().Is("doorTrans");
                        if (var16.isDoor && var16.open) {
                           var20 = true;
                        }

                        squareAddThumpable(var16.north, var16.open, var16.isDoor, var20);
    IsoThumpable var22 = (IsoThumpable)var8;
    bool var24 = false;
    IsoBarricade var13 = var22.getBarricadeOnSameSquare();
    IsoBarricade var14 = var22.getBarricadeOnOppositeSquare();
                        if (var13 != nullptr) {
                           var24 |= var13.isBlockVision();
                        }

                        if (var14 != nullptr) {
                           var24 |= var14.isBlockVision();
                        }

                        squareAddWindow(var22.north, var22.open, var24);
                     } else if (dynamic_cast<IsoWindow*>(var8) != nullptr var17) {
    bool var21 = false;
    IsoBarricade var23 = var17.getBarricadeOnSameSquare();
    IsoBarricade var25 = var17.getBarricadeOnOppositeSquare();
                        if (var23 != nullptr) {
                           var21 |= var23.isBlockVision();
                        }

                        if (var25 != nullptr) {
                           var21 |= var25.isBlockVision();
                        }

                        squareAddWindow(var17.north, var17.open, var21);
                     }
                  }

                  squareEndUpdate();
               }
            }
         }
      }

      chunkEndUpdate();
   }

    static void update() {
      if (IsoWorld.instance != nullptr && IsoWorld.instance.CurrentCell != nullptr) {
         checkLights();
    GameTime var0 = GameTime.getInstance();
    RenderSettings var1 = RenderSettings.getInstance();
    bool var2 = IsoWorld.instance.isHydroPowerOn();
    bool var3 = GameTime.getInstance().getNight() < 0.5F;
         if (var2 != bWasElecShut || var3 != bWasNight) {
            bWasElecShut = var2;
            bWasNight = var3;
            IsoGridSquare.RecalcLightTime = -1;
            var0.lightSourceUpdate = 100.0F;
         }

         for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
    IsoChunkMap var5 = IsoWorld.instance.CurrentCell.ChunkMap[var4];
            if (var5 != nullptr && !var5.ignore) {
    PlayerRenderSettings var6 = var1.getPlayerSettings(var4);
               stateBeginUpdate(var4, var5.getWorldXMin(), var5.getWorldYMin(), IsoChunkMap.ChunkGridWidth, IsoChunkMap.ChunkGridWidth);
               updatePlayer(var4);
               stateEndFrame(
                  var6.getRmod(),
                  var6.getGmod(),
                  var6.getBmod(),
                  var6.getAmbient(),
                  var6.getNight(),
                  var6.getViewDistance(),
                  var0.getViewDistMax(),
                  LosUtil.cachecleared[var4],
                  var0.lightSourceUpdate
               );
               if (LosUtil.cachecleared[var4]) {
                  LosUtil.cachecleared[var4] = false;
                  IsoWorld.instance.CurrentCell.invalidatePeekedRoom(var4);
               }

               for (int var7 = 0; var7 < IsoChunkMap.ChunkGridWidth; var7++) {
                  for (int var8 = 0; var8 < IsoChunkMap.ChunkGridWidth; var8++) {
    IsoChunk var9 = var5.getChunk(var8, var7);
                     if (var9 != nullptr && var9.lightCheck[var4]) {
                        updateChunk(var9);
                        var9.lightCheck[var4] = false;
                     }

                     if (var9 != nullptr) {
                        var9.bLightingNeverDone[var4] = !chunkLightingDone(var9.wx, var9.wy);
                     }
                  }
               }

               stateEndUpdate();
               updateCounter[var4] = stateUpdateCounter(var4);
               if (var0.lightSourceUpdate > 0.0F && IsoPlayer.players[var4] != nullptr) {
                  IsoPlayer.players[var4].dirtyRecalcGridStackTime = 20.0F;
               }
            }
         }

         DeadBodyAtlas.instance.lightingUpdate(updateCounter[0], var0.lightSourceUpdate > 0.0F);
         var0.lightSourceUpdate = 0.0F;
      }
   }

    static void getTorches(std::vector<TorchInfo> var0) {
      var0.addAll(torches);
   }

    static void stop() {
      torches.clear();
      JNILights.clear();
      destroy();

      for (int var0 = 0; var0 < updateCounter.length; var0++) {
         updateCounter[var0] = -1;
      }

      bWasElecShut = false;
      bWasNight = false;
      IsoLightSource.NextID = 1;
      IsoRoomLight.NextID = 1;
   }

   public static native void configure(float var0);

   public static native void scrollLeft(int var0);

   public static native void scrollRight(int var0);

   public static native void scrollUp(int var0);

   public static native void scrollDown(int var0);

   public static native void stateBeginUpdate(int var0, int var1, int var2, int var3, int var4);

   public static native void stateEndFrame(float var0, float var1, float var2, float var3, float var4, float var5, float var6, boolean var7, float var8);

   public static native void stateEndUpdate();

   public static native int stateUpdateCounter(int var0);

   public static native void teleport(int var0, int var1, int var2);

   public static native void DoLightingUpdateNew(long var0);

   public static native boolean WaitingForMain();

   public static native void playerSet(
      float var0, float var1, float var2, float var3, float var4, boolean var5, boolean var6, boolean var7, boolean var8, float var9, float var10, float var11
   );

   public static native boolean chunkLightingDone(int var0, int var1);

   public static native void chunkBeginUpdate(int var0, int var1);

   public static native void chunkEndUpdate();

   public static native void squareSetNull(int var0, int var1, int var2);

   public static native void squareBeginUpdate(int var0, int var1, int var2);

   public static native void squareSet(boolean var0, boolean var1, boolean var2, boolean var3, boolean var4, int var5, int var6, int var7);

   public static native void squareAddCurtain(int var0, boolean var1);

   public static native void squareAddDoor(boolean var0, boolean var1, boolean var2);

   public static native void squareAddThumpable(boolean var0, boolean var1, boolean var2, boolean var3);

   public static native void squareAddWindow(boolean var0, boolean var1, boolean var2);

   public static native void squareEndUpdate();

   public static native int getVertLight(int var0, int var1, int var2, int var3, int var4);

   public static native float getLightInfo(int var0, int var1, int var2, int var3, int var4);

   public static native float getDarkMulti(int var0, int var1, int var2, int var3);

   public static native float getTargetDarkMulti(int var0, int var1, int var2, int var3);

   public static native boolean getSeen(int var0, int var1, int var2, int var3);

   public static native boolean getCanSee(int var0, int var1, int var2, int var3);

   public static native boolean getCouldSee(int var0, int var1, int var2, int var3);

   public static native boolean getSquareLighting(int var0, int var1, int var2, int var3, int[] var4);

   public static native void addLight(int var0, int var1, int var2, int var3, int var4, float var5, float var6, float var7, int var8, boolean var9);

   public static native void addTempLight(int var0, int var1, int var2, int var3, int var4, float var5, float var6, float var7, int var8);

   public static native void removeLight(int var0);

   public static native void setLightActive(int var0, boolean var1);

   public static native void setLightColor(int var0, float var1, float var2, float var3);

   public static native void addRoomLight(int var0, int var1, int var2, int var3, int var4, int var5, int var6, int var7, boolean var8);

   public static native void removeRoomLight(int var0);

   public static native void setRoomLightActive(int var0, boolean var1);

   public static native void updateTorch(
      int var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7, boolean var8, float var9, int var10
   );

   public static native void removeTorch(int var0);

   public static native void destroy();
}
} // namespace iso
} // namespace zombie
