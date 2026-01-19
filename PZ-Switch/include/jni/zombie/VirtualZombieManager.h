#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/ZombiesZoneDefinition.h"
#include "zombie/characters/action/ActionGroup.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaChunk.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/popman/NetworkZombieSimulator.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include <algorithm>

namespace zombie {


class VirtualZombieManager {
:
   private ArrayDeque<IsoZombie> ReusableZombies = std::make_unique<ArrayDeque<>>();
   private HashSet<IsoZombie> ReusableZombieSet = std::make_unique<HashSet<>>();
   private ArrayList<IsoZombie> ReusedThisFrame = std::make_unique<ArrayList<>>();
   private ArrayList<IsoZombie> RecentlyRemoved = std::make_unique<ArrayList<>>();
    static VirtualZombieManager instance = new VirtualZombieManager();
    int MaxRealZombies = 1;
   private ArrayList<IsoZombie> m_tempZombies = std::make_unique<ArrayList<>>();
    ArrayList<IsoGridSquare> choices = std::make_unique<ArrayList<>>();
   private ArrayList<IsoGridSquare> bestchoices = std::make_unique<ArrayList<>>();
    HandWeapon w = nullptr;
    int BLOCKED_N = 1;
    int BLOCKED_S = 2;
    int BLOCKED_W = 4;
    int BLOCKED_E = 8;
    int NO_SQUARE_N = 16;
    int NO_SQUARE_S = 32;
    int NO_SQUARE_W = 64;
    int NO_SQUARE_E = 128;

    bool removeZombieFromWorld(IsoZombie var1) {
    bool var2 = var1.getCurrentSquare() != nullptr;
      var1.getEmitter().unregister();
      var1.removeFromWorld();
      var1.removeFromSquare();
    return var2;
   }

    void reuseZombie(IsoZombie var1) {
      if (var1 != nullptr) {
         assert !IsoWorld.instance.CurrentCell.getObjectList().contains(var1);

         assert !IsoWorld.instance.CurrentCell.getZombieList().contains(var1);

         assert var1.getCurrentSquare() == nullptr || !var1.getCurrentSquare().getMovingObjects().contains(var1);

         if (!this.isReused(var1)) {
            NetworkZombieSimulator.getInstance().remove(var1);
            var1.resetForReuse();
            this.addToReusable(var1);
         }
      }
   }

    void addToReusable(IsoZombie var1) {
      if (var1 != nullptr && !this.ReusableZombieSet.contains(var1)) {
         this.ReusableZombies.addLast(var1);
         this.ReusableZombieSet.add(var1);
      }
   }

    bool isReused(IsoZombie var1) {
      return this.ReusableZombieSet.contains(var1);
   }

    void init() {
      if (!GameClient.bClient) {
    void* var1 = nullptr;
         if (!IsoWorld.getZombiesDisabled()) {
            for (int var2 = 0; var2 < this.MaxRealZombies; var2++) {
               var1 = new IsoZombie(IsoWorld.instance.CurrentCell);
               var1.getEmitter().unregister();
               this.addToReusable((IsoZombie)var1);
            }
         }
      }
   }

    void Reset() {
      for (IsoZombie var2 : this.ReusedThisFrame) {
         if (var2.vocalEvent != 0L) {
            var2.getEmitter().stopSoundLocal(var2.vocalEvent);
            var2.vocalEvent = 0L;
         }
      }

      this.bestchoices.clear();
      this.choices.clear();
      this.RecentlyRemoved.clear();
      this.ReusableZombies.clear();
      this.ReusableZombieSet.clear();
      this.ReusedThisFrame.clear();
   }

    void update() {
    long var1 = System.currentTimeMillis();

      for (int var3 = this.RecentlyRemoved.size() - 1; var3 >= 0; var3--) {
    IsoZombie var4 = this.RecentlyRemoved.get(var3);
         var4.updateEmitter();
         if (var1 - var4.removedFromWorldMS > 5000L) {
            if (var4.vocalEvent != 0L) {
               var4.getEmitter().stopSoundLocal(var4.vocalEvent);
               var4.vocalEvent = 0L;
            }

            var4.getEmitter().stopAll();
            this.RecentlyRemoved.remove(var3);
            this.ReusedThisFrame.add(var4);
         }
      }

      if (!GameClient.bClient && !GameServer.bServer) {
         for (int var6 = 0; var6 < IsoWorld.instance.CurrentCell.getZombieList().size(); var6++) {
    IsoZombie var9 = (IsoZombie)IsoWorld.instance.CurrentCell.getZombieList().get(var6);
            if (!var9.KeepItReal && var9.getCurrentSquare() == nullptr) {
               var9.removeFromWorld();
               var9.removeFromSquare();

               assert this.ReusedThisFrame.contains(var9);

               assert !IsoWorld.instance.CurrentCell.getZombieList().contains(var9);

               var6--;
            }
         }

         for (int var7 = 0; var7 < this.ReusedThisFrame.size(); var7++) {
    IsoZombie var10 = this.ReusedThisFrame.get(var7);
            this.reuseZombie(var10);
         }

         this.ReusedThisFrame.clear();
      } else {
         for (int var5 = 0; var5 < this.ReusedThisFrame.size(); var5++) {
    IsoZombie var8 = this.ReusedThisFrame.get(var5);
            this.reuseZombie(var8);
         }

         this.ReusedThisFrame.clear();
      }
   }

    IsoZombie createRealZombieAlways(int var1, bool var2) {
      return this.createRealZombieAlways(var1, var2, 0);
   }

    IsoZombie createRealZombieAlways(int var1, int var2, bool var3) {
    int var4 = PersistentOutfits.instance.getOutfit(var1);
      return this.createRealZombieAlways(var2, var3, var4);
   }

    IsoZombie createRealZombieAlways(int var1, bool var2, int var3) {
    IsoZombie var4 = nullptr;
      if (!SystemDisabler.doZombieCreation) {
    return nullptr;
      } else if (this.choices != nullptr && !this.choices.isEmpty()) {
    IsoGridSquare var5 = this.choices.get(Rand.Next(this.choices.size()));
         if (var5 == nullptr) {
    return nullptr;
         } else {
            if (this.w == nullptr) {
               this.w = (HandWeapon)InventoryItemFactory.CreateItem("Base.Axe");
            }

            if ((GameServer.bServer || GameClient.bClient) && var3 == 0) {
               var3 = ZombiesZoneDefinition.pickPersistentOutfit(var5);
            }

            if (this.ReusableZombies.isEmpty()) {
               var4 = new IsoZombie(IsoWorld.instance.CurrentCell);
               var4.bDressInRandomOutfit = var3 == 0;
               var4.setPersistentOutfitID(var3);
               IsoWorld.instance.CurrentCell.getObjectList().add(var4);
            } else {
               var4 = this.ReusableZombies.removeFirst();
               this.ReusableZombieSet.remove(var4);
               var4.getHumanVisual().clear();
               var4.clearAttachedItems();
               var4.clearItemsToSpawnAtDeath();
               var4.bDressInRandomOutfit = var3 == 0;
               var4.setPersistentOutfitID(var3);
               var4.setSitAgainstWall(false);
               var4.setOnDeathDone(false);
               var4.setOnKillDone(false);
               var4.setDoDeathSound(true);
               var4.setHitTime(0);
               var4.setFallOnFront(false);
               var4.setFakeDead(false);
               var4.setReanimatedPlayer(false);
               var4.setStateMachineLocked(false);
    Vector2 var6 = var4.dir.ToVector();
               var6.x = var6.x + (Rand.Next(200) / 100.0F - 0.5F);
               var6.y = var6.y + (Rand.Next(200) / 100.0F - 0.5F);
               var6.normalize();
               var4.setForwardDirection(var6);
               IsoWorld.instance.CurrentCell.getObjectList().add(var4);
               var4.walkVariant = "ZombieWalk";
               var4.DoZombieStats();
               if (var4.isOnFire()) {
                  IsoFireManager.RemoveBurningCharacter(var4);
                  var4.setOnFire(false);
               }

               if (var4.AttachedAnimSprite != nullptr) {
                  var4.AttachedAnimSprite.clear();
               }

               var4.thumpFlag = 0;
               var4.thumpSent = false;
               var4.soundSourceTarget = nullptr;
               var4.soundAttract = 0.0F;
               var4.soundAttractTimeout = 0.0F;
               var4.bodyToEat = nullptr;
               var4.eatBodyTarget = nullptr;
               var4.atlasTex = nullptr;
               var4.clearVariables();
               var4.setStaggerBack(false);
               var4.setKnockedDown(false);
               var4.setKnifeDeath(false);
               var4.setJawStabAttach(false);
               var4.setCrawler(false);
               var4.initializeStates();
               var4.actionContext.setGroup(ActionGroup.getActionGroup("zombie"));
               var4.advancedAnimator.OnAnimDataChanged(false);
               var4.setDefaultState();
               var4.getAnimationPlayer().resetBoneModelTransforms();
            }

            var4.dir = IsoDirections.fromIndex(var1);
            var4.setForwardDirection(var4.dir.ToVector());
            var4.getInventory().setExplored(false);
            if (var2) {
               var4.bDressInRandomOutfit = true;
            }

            var4.target = nullptr;
            var4.TimeSinceSeenFlesh = 100000.0F;
            if (!var4.isFakeDead()) {
               if (SandboxOptions.instance.Lore.Toughness.getValue() == 1) {
                  var4.setHealth(3.5F + Rand.Next(0.0F, 0.3F));
               }

               if (SandboxOptions.instance.Lore.Toughness.getValue() == 2) {
                  var4.setHealth(1.5F + Rand.Next(0.0F, 0.3F));
               }

               if (SandboxOptions.instance.Lore.Toughness.getValue() == 3) {
                  var4.setHealth(0.5F + Rand.Next(0.0F, 0.3F));
               }

               if (SandboxOptions.instance.Lore.Toughness.getValue() == 4) {
                  var4.setHealth(Rand.Next(0.5F, 3.5F) + Rand.Next(0.0F, 0.3F));
               }
            } else {
               var4.setHealth(0.5F + Rand.Next(0.0F, 0.3F));
            }

    float var12 = Rand.Next(0, 1000);
    float var7 = Rand.Next(0, 1000);
            var12 /= 1000.0F;
            var7 /= 1000.0F;
            var12 += var5.getX();
            var7 += var5.getY();
            var4.setCurrent(var5);
            var4.setMovingSquareNow();
            var4.setX(var12);
            var4.setY(var7);
            var4.setZ(var5.getZ());
            if ((GameClient.bClient || GameServer.bServer) && var4.networkAI != nullptr) {
               var4.networkAI.reset();
            }

            var4.upKillCount = true;
            if (var2) {
               var4.setDir(IsoDirections.fromIndex(Rand.Next(8)));
               var4.setForwardDirection(var4.dir.ToVector());
               var4.setFakeDead(false);
               var4.setHealth(0.0F);
               var4.upKillCount = false;
               var4.DoZombieInventory();
    new IsoDeadBody();
    return var4;
            } else {
               synchronized (IsoWorld.instance.CurrentCell.getZombieList()) {
                  var4.getEmitter().register();
                  IsoWorld.instance.CurrentCell.getZombieList().add(var4);
                  if (GameClient.bClient) {
                     var4.bRemote = true;
                  }

                  if (GameServer.bServer) {
                     var4.OnlineID = ServerMap.instance.getUniqueZombieId();
                     if (var4.OnlineID == -1) {
                        IsoWorld.instance.CurrentCell.getZombieList().remove(var4);
                        IsoWorld.instance.CurrentCell.getObjectList().remove(var4);
                        this.ReusedThisFrame.add(var4);
    return nullptr;
                     }

                     ServerMap.instance.ZombieMap.put(var4.OnlineID, var4);
                  }

    return var4;
               }
            }
         }
      } else {
    return nullptr;
      }
   }

    IsoGridSquare pickEatingZombieSquare(float var1, float var2, float var3, float var4, int var5) {
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      if (var6 == nullptr || !this.canSpawnAt(var6.x, var6.y, var6.z) || var6.HasStairs()) {
    return nullptr;
      } else {
         return PolygonalMap2.instance.lineClearCollide(var1, var2, var3, var4, var5, nullptr, false, true) ? nullptr : var6;
      }
   }

    void createEatingZombies(IsoDeadBody var1, int var2) {
      if (!IsoWorld.getZombiesDisabled()) {
         for (int var3 = 0; var3 < var2; var3++) {
    float var4 = var1.x;
    float var5 = var1.y;
            switch (var3) {
               case 0:
                  var4 -= 0.5F;
                  break;
               case 1:
                  var4 += 0.5F;
                  break;
               case 2:
                  var5 -= 0.5F;
                  break;
               case 3:
                  var5 += 0.5F;
            }

    IsoGridSquare var6 = this.pickEatingZombieSquare(var1.x, var1.y, var4, var5, (int)var1.z);
            if (var6 != nullptr) {
               this.choices.clear();
               this.choices.add(var6);
    IsoZombie var7 = this.createRealZombieAlways(1, false);
               if (var7 != nullptr) {
                  ZombieSpawnRecorder.instance.record(var7, "createEatingZombies");
                  var7.bDressInRandomOutfit = true;
                  var7.setX(var4);
                  var7.setY(var5);
                  var7.setZ(var1.z);
                  var7.faceLocationF(var1.x, var1.y);
                  var7.setEatBodyTarget(var1, true);
               }
            }
         }
      }
   }

    IsoZombie createRealZombie(int var1, bool var2) {
      return GameClient.bClient ? nullptr : this.createRealZombieAlways(var1, var2);
   }

    void AddBloodToMap(int var1, IsoChunk var2) {
      for (int var3 = 0; var3 < var1; var3++) {
    void* var4 = nullptr;
    int var5 = 0;

         do {
    int var6 = Rand.Next(10);
    int var7 = Rand.Next(10);
            var4 = var2.getGridSquare(var6, var7, 0);
            var5++;
         } while (var5 < 100 && (var4 == nullptr || !var4.isFree(false)));

         if (var4 != nullptr) {
    uint8_t var11 = 5;
            if (Rand.Next(10) == 0) {
               var11 = 10;
            }

            if (Rand.Next(40) == 0) {
               var11 = 20;
            }

            for (int var12 = 0; var12 < var11; var12++) {
    float var8 = Rand.Next(3000) / 1000.0F;
    float var9 = Rand.Next(3000) / 1000.0F;
               var2.addBloodSplat(var4.getX() + --var8, var4.getY() + --var9, var4.getZ(), Rand.Next(12) + 8);
            }
         }
      }
   }

    ArrayList<IsoZombie> addZombiesToMap(int var1, RoomDef var2) {
      return this.addZombiesToMap(var1, var2, true);
   }

    ArrayList<IsoZombie> addZombiesToMap(int var1, RoomDef var2, boolean var3) {
    std::vector var4 = new ArrayList();
      if ("Tutorial" == Core.GameMode)) {
    return var4;
      } else if (IsoWorld.getZombiesDisabled()) {
    return var4;
      } else {
         this.choices.clear();
         this.bestchoices.clear();
    void* var5 = nullptr;

         for (int var6 = 0; var6 < var2.rects.size(); var6++) {
    int var7 = var2.level;
    RoomRect var8 = (RoomRect)var2.rects.get(var6);

            for (int var9 = var8.x; var9 < var8.getX2(); var9++) {
               for (int var10 = var8.y; var10 < var8.getY2(); var10++) {
                  var5 = IsoWorld.instance.CurrentCell.getGridSquare(var9, var10, var7);
                  if (var5 != nullptr && this.canSpawnAt(var9, var10, var7)) {
                     this.choices.add((IsoGridSquare)var5);
    bool var11 = false;

                     for (int var12 = 0; var12 < IsoPlayer.numPlayers; var12++) {
                        if (IsoPlayer.players[var12] != nullptr && var5.isSeen(var12)) {
                           var11 = true;
                        }
                     }

                     if (!var11) {
                        this.bestchoices.add((IsoGridSquare)var5);
                     }
                  }
               }
            }
         }

         var1 = Math.min(var1, this.choices.size());
         if (!this.bestchoices.isEmpty()) {
            this.choices.addAll(this.bestchoices);
            this.choices.addAll(this.bestchoices);
         }

         for (int var15 = 0; var15 < var1; var15++) {
            if (!this.choices.isEmpty()) {
               var2.building.bAlarmed = false;
    int var16 = Rand.Next(8);
    uint8_t var17 = 4;
    IsoZombie var18 = this.createRealZombie(var16, var3 ? Rand.Next(var17) == 0 : false);
               if (var18 != nullptr && var18.getSquare() != nullptr) {
                  if (!GameServer.bServer) {
                     var18.bDressInRandomOutfit = true;
                  }

                  var18.setX((int)var18.getX() + Rand.Next(2, 8) / 10.0F);
                  var18.setY((int)var18.getY() + Rand.Next(2, 8) / 10.0F);
                  this.choices.remove(var18.getSquare());
                  this.choices.remove(var18.getSquare());
                  this.choices.remove(var18.getSquare());
                  var4.add(var18);
               }
            } else {
               System.out.println("No choices for zombie.");
            }
         }

         this.bestchoices.clear();
         this.choices.clear();
    return var4;
      }
   }

    void tryAddIndoorZombies(RoomDef var1, bool var2) {
   }

    void addIndoorZombies(int var1, RoomDef var2, bool var3) {
      this.choices.clear();
      this.bestchoices.clear();
    void* var4 = nullptr;

      for (int var5 = 0; var5 < var2.rects.size(); var5++) {
    int var6 = var2.level;
    RoomRect var7 = (RoomRect)var2.rects.get(var5);

         for (int var8 = var7.x; var8 < var7.getX2(); var8++) {
            for (int var9 = var7.y; var9 < var7.getY2(); var9++) {
               var4 = IsoWorld.instance.CurrentCell.getGridSquare(var8, var9, var6);
               if (var4 != nullptr && this.canSpawnAt(var8, var9, var6)) {
                  this.choices.add((IsoGridSquare)var4);
               }
            }
         }
      }

      var1 = Math.min(var1, this.choices.size());
      if (!this.bestchoices.isEmpty()) {
         this.choices.addAll(this.bestchoices);
         this.choices.addAll(this.bestchoices);
      }

      for (int var12 = 0; var12 < var1; var12++) {
         if (!this.choices.isEmpty()) {
            var2.building.bAlarmed = false;
    int var13 = Rand.Next(8);
    uint8_t var14 = 4;
    IsoZombie var15 = this.createRealZombie(var13, var3 ? Rand.Next(var14) == 0 : false);
            if (var15 != nullptr && var15.getSquare() != nullptr) {
               ZombieSpawnRecorder.instance.record(var15, "addIndoorZombies");
               var15.bIndoorZombie = true;
               var15.setX((int)var15.getX() + Rand.Next(2, 8) / 10.0F);
               var15.setY((int)var15.getY() + Rand.Next(2, 8) / 10.0F);
               this.choices.remove(var15.getSquare());
               this.choices.remove(var15.getSquare());
               this.choices.remove(var15.getSquare());
            }
         } else {
            System.out.println("No choices for zombie.");
         }
      }

      this.bestchoices.clear();
      this.choices.clear();
   }

    void addIndoorZombiesToChunk(IsoChunk var1, IsoRoom var2, int var3, ArrayList<IsoZombie> var4) {
      if (var3 > 0) {
    float var5 = var2.getRoomDef().getAreaOverlapping(var1);
    int var6 = (int)Math.ceil(var3 * var5);
         if (var6 > 0) {
            this.choices.clear();
    int var7 = var2.def.level;

            for (int var8 = 0; var8 < var2.rects.size(); var8++) {
    RoomRect var9 = (RoomRect)var2.rects.get(var8);
    int var10 = Math.max(var1.wx * 10, var9.x);
    int var11 = Math.max(var1.wy * 10, var9.y);
    int var12 = Math.min((var1.wx + 1) * 10, var9.x + var9.w);
    int var13 = Math.min((var1.wy + 1) * 10, var9.y + var9.h);

               for (int var14 = var10; var14 < var12; var14++) {
                  for (int var15 = var11; var15 < var13; var15++) {
    IsoGridSquare var16 = var1.getGridSquare(var14 - var1.wx * 10, var15 - var1.wy * 10, var7);
                     if (var16 != nullptr && this.canSpawnAt(var14, var15, var7)) {
                        this.choices.add(var16);
                     }
                  }
               }
            }

            if (!this.choices.isEmpty()) {
               var2.def.building.bAlarmed = false;
               var6 = Math.min(var6, this.choices.size());

               for (int var18 = 0; var18 < var6; var18++) {
    IsoZombie var19 = this.createRealZombie(Rand.Next(8), false);
                  if (var19 != nullptr && var19.getSquare() != nullptr) {
                     if (!GameServer.bServer) {
                        var19.bDressInRandomOutfit = true;
                     }

                     var19.setX((int)var19.getX() + Rand.Next(2, 8) / 10.0F);
                     var19.setY((int)var19.getY() + Rand.Next(2, 8) / 10.0F);
                     this.choices.remove(var19.getSquare());
                     var4.add(var19);
                  }
               }

               this.choices.clear();
            }
         }
      }
   }

    void addIndoorZombiesToChunk(IsoChunk var1, IsoRoom var2) {
      if (var2.def.spawnCount == -1) {
         var2.def.spawnCount = this.getZombieCountForRoom(var2);
      }

      this.m_tempZombies.clear();
      this.addIndoorZombiesToChunk(var1, var2, var2.def.spawnCount, this.m_tempZombies);
      ZombieSpawnRecorder.instance.record(this.m_tempZombies, "addIndoorZombiesToChunk");
   }

    void addDeadZombiesToMap(int var1, RoomDef var2) {
    bool var3 = false;
      this.choices.clear();
      this.bestchoices.clear();
    void* var4 = nullptr;

      for (int var5 = 0; var5 < var2.rects.size(); var5++) {
    int var6 = var2.level;
    RoomRect var7 = (RoomRect)var2.rects.get(var5);

         for (int var8 = var7.x; var8 < var7.getX2(); var8++) {
            for (int var9 = var7.y; var9 < var7.getY2(); var9++) {
               var4 = IsoWorld.instance.CurrentCell.getGridSquare(var8, var9, var6);
               if (var4 != nullptr && var4.isFree(false)) {
                  this.choices.add((IsoGridSquare)var4);
                  if (!GameServer.bServer) {
    bool var10 = false;

                     for (int var11 = 0; var11 < IsoPlayer.numPlayers; var11++) {
                        if (IsoPlayer.players[var11] != nullptr && var4.isSeen(var11)) {
                           var10 = true;
                        }
                     }

                     if (!var10) {
                        this.bestchoices.add((IsoGridSquare)var4);
                     }
                  }
               }
            }
         }
      }

      var1 = Math.min(var1, this.choices.size());
      if (!this.bestchoices.isEmpty()) {
         this.choices.addAll(this.bestchoices);
         this.choices.addAll(this.bestchoices);
      }

      for (int var14 = 0; var14 < var1; var14++) {
         if (!this.choices.isEmpty()) {
    int var15 = Rand.Next(8);
            this.createRealZombie(var15, true);
         }
      }

      this.bestchoices.clear();
      this.choices.clear();
   }

    void RemoveZombie(IsoZombie var1) {
      if (var1.isReanimatedPlayer()) {
         if (var1.vocalEvent != 0L) {
            var1.getEmitter().stopSoundLocal(var1.vocalEvent);
            var1.vocalEvent = 0L;
         }

         ReanimatedPlayers.instance.removeReanimatedPlayerFromWorld(var1);
      } else {
         if (var1.isDead()) {
            if (!this.RecentlyRemoved.contains(var1)) {
               var1.removedFromWorldMS = System.currentTimeMillis();
               this.RecentlyRemoved.add(var1);
            }
         } else if (!this.ReusedThisFrame.contains(var1)) {
            this.ReusedThisFrame.add(var1);
         }
      }
   }

    void createHordeFromTo(float var1, float var2, float var3, float var4, int var5) {
      ZombiePopulationManager.instance.createHordeFromTo((int)var1, (int)var2, (int)var3, (int)var4, var5);
   }

    IsoZombie createRealZombie(float var1, float var2, float var3) {
      this.choices.clear();
      this.choices.add(IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3));
      if (!this.choices.isEmpty()) {
    int var4 = Rand.Next(8);
         return this.createRealZombie(var4, true);
      } else {
    return nullptr;
      }
   }

    IsoZombie createRealZombieNow(float var1, float var2, float var3) {
      this.choices.clear();
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      if (var4 == nullptr) {
    return nullptr;
      } else {
         this.choices.add(var4);
         if (!this.choices.isEmpty()) {
    int var5 = Rand.Next(8);
            return this.createRealZombie(var5, false);
         } else {
    return nullptr;
         }
      }
   }

    int getZombieCountForRoom(IsoRoom var1) {
      if (IsoWorld.getZombiesDisabled()) {
    return 0;
      } else if (GameClient.bClient) {
    return 0;
      } else if (Core.bLastStand) {
    return 0;
      } else {
    int var2 = 7;
         if (SandboxOptions.instance.Zombies.getValue() == 1) {
            var2 = 3;
         } else if (SandboxOptions.instance.Zombies.getValue() == 2) {
            var2 = 4;
         } else if (SandboxOptions.instance.Zombies.getValue() == 3) {
            var2 = 6;
         } else if (SandboxOptions.instance.Zombies.getValue() == 5) {
            var2 = 15;
         }

    float var3 = 0.0F;
    IsoMetaChunk var4 = IsoWorld.instance.getMetaChunk(var1.def.x / 10, var1.def.y / 10);
         if (var4 != nullptr) {
            var3 = var4.getLootZombieIntensity();
            if (var3 > 4.0F) {
               var2 = (int)(var2 - (var3 / 2.0F - 2.0F));
            }
         }

         if (var1.def.getArea() > 100) {
            var2 -= 2;
         }

         var2 = Math.max(2, var2);
         if (var1.getBuilding() != nullptr) {
    int var5 = var1.def.getArea();
            if (var1.getBuilding().getRoomsNumber() > 100 && var5 >= 20) {
    int var6 = var1.getBuilding().getRoomsNumber() - 95;
               if (var6 > 20) {
                  var6 = 20;
               }

               if (SandboxOptions.instance.Zombies.getValue() == 1) {
                  var6 += 10;
               } else if (SandboxOptions.instance.Zombies.getValue() == 2) {
                  var6 += 7;
               } else if (SandboxOptions.instance.Zombies.getValue() == 3) {
                  var6 += 5;
               } else if (SandboxOptions.instance.Zombies.getValue() == 4) {
                  var6 -= 10;
               }

               if (var5 < 30) {
                  var6 -= 6;
               }

               if (var5 < 50) {
                  var6 -= 10;
               }

               if (var5 < 70) {
                  var6 -= 13;
               }

               return Rand.Next(var6, var6 + 10);
            }
         }

         if (Rand.Next(var2) == 0) {
    int var8 = 1;
            var8 = (int)(var8 + (var3 / 2.0F - 2.0F));
            if (var1.def.getArea() < 30) {
               var8 -= 4;
            }

            if (var1.def.getArea() > 85) {
               var8 += 2;
            }

            if (var1.getBuilding().getRoomsNumber() < 7) {
               var8 -= 2;
            }

            if (SandboxOptions.instance.Zombies.getValue() == 1) {
               var8 += 3;
            } else if (SandboxOptions.instance.Zombies.getValue() == 2) {
               var8 += 2;
            } else if (SandboxOptions.instance.Zombies.getValue() == 3) {
               var8++;
            } else if (SandboxOptions.instance.Zombies.getValue() == 5) {
               var8 -= 2;
            }

            var8 = Math.max(0, var8);
            var8 = Math.min(7, var8);
            return Rand.Next(var8, var8 + 2);
         } else {
    return 0;
         }
      }
   }

    void roomSpotted(IsoRoom var1) {
      if (!GameClient.bClient) {
         var1.def.forEachChunk((var0, var1x) -> var1x.addSpawnedRoom(var0.ID));
         if (var1.def.spawnCount == -1) {
            var1.def.spawnCount = this.getZombieCountForRoom(var1);
         }

         if (var1.def.spawnCount > 0) {
            if (var1.getBuilding().getDef().isFullyStreamedIn()) {
    std::vector var2 = this.addZombiesToMap(var1.def.spawnCount, var1.def, false);
               ZombieSpawnRecorder.instance.record(var2, "roomSpotted");
            } else {
               this.m_tempZombies.clear();
               var1.def.forEachChunk((var2x, var3) -> this.addIndoorZombiesToChunk(var3, var1, var1.def.spawnCount, this.m_tempZombies));
               ZombieSpawnRecorder.instance.record(this.m_tempZombies, "roomSpotted");
            }
         }
      }
   }

    int getBlockedBits(IsoGridSquare var1) {
    int var2 = 0;
      if (var1 == nullptr) {
    return var2;
      } else {
         if (var1.nav[IsoDirections.N.index()] == nullptr) {
            var2 |= this.NO_SQUARE_N;
         } else if (IsoGridSquare.getMatrixBit(var1.pathMatrix, 1, 0, 1)) {
            var2 |= this.BLOCKED_N;
         }

         if (var1.nav[IsoDirections.S.index()] == nullptr) {
            var2 |= this.NO_SQUARE_S;
         } else if (IsoGridSquare.getMatrixBit(var1.pathMatrix, 1, 2, 1)) {
            var2 |= this.BLOCKED_S;
         }

         if (var1.nav[IsoDirections.W.index()] == nullptr) {
            var2 |= this.NO_SQUARE_W;
         } else if (IsoGridSquare.getMatrixBit(var1.pathMatrix, 0, 1, 1)) {
            var2 |= this.BLOCKED_W;
         }

         if (var1.nav[IsoDirections.E.index()] == nullptr) {
            var2 |= this.NO_SQUARE_E;
         } else if (IsoGridSquare.getMatrixBit(var1.pathMatrix, 2, 1, 1)) {
            var2 |= this.BLOCKED_E;
         }

    return var2;
      }
   }

    bool isBlockedInAllDirections(int var1, int var2, int var3) {
      IsoGridSquare var4 = GameServer.bServer
         ? ServerMap.instance.getGridSquare(var1, var2, var3)
         : IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      if (var4 == nullptr) {
    return false;
      } else {
    bool var5 = IsoGridSquare.getMatrixBit(var4.pathMatrix, 1, 0, 1) && var4.nav[IsoDirections.N.index()] != nullptr;
    bool var6 = IsoGridSquare.getMatrixBit(var4.pathMatrix, 1, 2, 1) && var4.nav[IsoDirections.S.index()] != nullptr;
    bool var7 = IsoGridSquare.getMatrixBit(var4.pathMatrix, 0, 1, 1) && var4.nav[IsoDirections.W.index()] != nullptr;
    bool var8 = IsoGridSquare.getMatrixBit(var4.pathMatrix, 2, 1, 1) && var4.nav[IsoDirections.E.index()] != nullptr;
         return var5 && var6 && var7 && var8;
      }
   }

    bool canPathOnlyN(IsoGridSquare var1) {
      while (true) {
    int var2 = this.getBlockedBits(var1);
         if ((var2 & (this.BLOCKED_W | this.BLOCKED_E)) != (this.BLOCKED_W | this.BLOCKED_E)) {
    return false;
         }

         if ((var2 & this.NO_SQUARE_N) != 0) {
    return false;
         }

         if ((var2 & this.BLOCKED_N) != 0) {
    return true;
         }

         var1 = var1.nav[IsoDirections.N.index()];
      }
   }

    bool canPathOnlyS(IsoGridSquare var1) {
      while (true) {
    int var2 = this.getBlockedBits(var1);
         if ((var2 & (this.BLOCKED_W | this.BLOCKED_E)) != (this.BLOCKED_W | this.BLOCKED_E)) {
    return false;
         }

         if ((var2 & this.NO_SQUARE_S) != 0) {
    return false;
         }

         if ((var2 & this.BLOCKED_S) != 0) {
    return true;
         }

         var1 = var1.nav[IsoDirections.S.index()];
      }
   }

    bool canPathOnlyW(IsoGridSquare var1) {
      while (true) {
    int var2 = this.getBlockedBits(var1);
         if ((var2 & (this.BLOCKED_N | this.BLOCKED_S)) != (this.BLOCKED_N | this.BLOCKED_S)) {
    return false;
         }

         if ((var2 & this.NO_SQUARE_W) != 0) {
    return false;
         }

         if ((var2 & this.BLOCKED_W) != 0) {
    return true;
         }

         var1 = var1.nav[IsoDirections.W.index()];
      }
   }

    bool canPathOnlyE(IsoGridSquare var1) {
      while (true) {
    int var2 = this.getBlockedBits(var1);
         if ((var2 & (this.BLOCKED_N | this.BLOCKED_S)) != (this.BLOCKED_N | this.BLOCKED_S)) {
    return false;
         }

         if ((var2 & this.NO_SQUARE_E) != 0) {
    return false;
         }

         if ((var2 & this.BLOCKED_E) != 0) {
    return true;
         }

         var1 = var1.nav[IsoDirections.E.index()];
      }
   }

    bool canSpawnAt(int var1, int var2, int var3) {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      if (var4 != nullptr && var4.isFree(false)) {
    int var5 = this.getBlockedBits(var4);
         if (var5 == (this.BLOCKED_N | this.BLOCKED_S | this.BLOCKED_W | this.BLOCKED_E)) {
    return false;
         } else {
            return (var5 & (this.BLOCKED_N | this.BLOCKED_S)) == (this.BLOCKED_N | this.BLOCKED_S) && this.canPathOnlyW(var4) && this.canPathOnlyE(var4)
               ? false
               : (var5 & (this.BLOCKED_W | this.BLOCKED_E)) != (this.BLOCKED_W | this.BLOCKED_E) || !this.canPathOnlyN(var4) || !this.canPathOnlyS(var4);
         }
      } else {
    return false;
      }
   }

    int reusableZombiesSize() {
      return this.ReusableZombies.size();
   }
}
} // namespace zombie
