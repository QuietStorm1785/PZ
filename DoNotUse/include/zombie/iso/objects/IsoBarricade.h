#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SoundManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/states/ThumpState.h"
#include "zombie/audio/parameters/ParameterMeleeHitSurface/Material.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObject/VisionResult.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/IsoBarricade/1.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/Type.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoBarricade : public IsoObject {
public:
    static const int MAX_PLANKS = 4;
    static const int PLANK_HEALTH = 1000;
   private int[] plankHealth = new int[4];
    static const int METAL_HEALTH = 5000;
    static const int METAL_HEALTH_DAMAGED = 2500;
    int metalHealth;
    static const int METAL_BAR_HEALTH = 3000;
    int metalBarHealth;

    public IsoBarricade(IsoCell var1) {
      super(var1);
   }

    public IsoBarricade(IsoCell var1, IsoGridSquare var2, IsoDirections var3) {
      this.square = var2;
      this.dir = var3;
   }

    std::string getObjectName() {
      return "Barricade";
   }

    void addPlank(IsoGameCharacter var1, InventoryItem var2) {
      if (this.canAddPlank()) {
    int var3 = 1000;
         if (var2 != nullptr) {
            var3 = (int)((float)var2.getCondition() / var2.getConditionMax() * 1000.0F);
         }

         if (var1 != nullptr) {
            var3 = (int)(var3 * var1.getBarricadeStrengthMod());
         }

         for (int var4 = 0; var4 < 4; var4++) {
            if (this.plankHealth[var4] <= 0) {
               this.plankHealth[var4] = var3;
               break;
            }
         }

         this.chooseSprite();
         if (!GameServer.bServer) {
            for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
               LosUtil.cachecleared[var5] = true;
            }

            IsoGridSquare.setRecalcLightTime(-1);
            GameTime.instance.lightSourceUpdate = 100.0F;
         }

         if (this.square != nullptr) {
            this.square.RecalcProperties();
         }
      }
   }

    InventoryItem removePlank(IsoGameCharacter var1) {
      if (this.getNumPlanks() <= 0) {
    return nullptr;
      } else {
    InventoryItem var2 = nullptr;

         for (int var3 = 3; var3 >= 0; var3--) {
            if (this.plankHealth[var3] > 0) {
    float var4 = Math.min(this.plankHealth[var3] / 1000.0F, 1.0F);
               var2 = InventoryItemFactory.CreateItem("Base.Plank");
               var2.setCondition((int)Math.max(var2.getConditionMax() * var4, 1.0F));
               this.plankHealth[var3] = 0;
               break;
            }
         }

         if (this.getNumPlanks() <= 0) {
            if (this.square != nullptr) {
               if (GameServer.bServer) {
                  this.square.transmitRemoveItemFromSquare(this);
               } else {
                  this.square.RemoveTileObject(this);
               }
            }
         } else {
            this.chooseSprite();
            if (!GameServer.bServer) {
               for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
                  LosUtil.cachecleared[var5] = true;
               }

               IsoGridSquare.setRecalcLightTime(-1);
               GameTime.instance.lightSourceUpdate = 100.0F;
            }

            if (this.square != nullptr) {
               this.square.RecalcProperties();
            }
         }

    return var2;
      }
   }

    int getNumPlanks() {
    int var1 = 0;

      for (int var2 = 0; var2 < 4; var2++) {
         if (this.plankHealth[var2] > 0) {
            var1++;
         }
      }

    return var1;
   }

    bool canAddPlank() {
      return !this.isMetal() && this.getNumPlanks() < 4 && !this.isMetalBar();
   }

    void addMetalBar(IsoGameCharacter var1, InventoryItem var2) {
      if (this.getNumPlanks() <= 0) {
         if (this.metalHealth <= 0) {
            if (this.metalBarHealth <= 0) {
               this.metalBarHealth = 3000;
               if (var2 != nullptr) {
                  this.metalBarHealth = (int)((float)var2.getCondition() / var2.getConditionMax() * 5000.0F);
               }

               if (var1 != nullptr) {
                  this.metalBarHealth = (int)(this.metalBarHealth * var1.getMetalBarricadeStrengthMod());
               }

               this.chooseSprite();
               if (!GameServer.bServer) {
                  for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
                     LosUtil.cachecleared[var3] = true;
                  }

                  IsoGridSquare.setRecalcLightTime(-1);
                  GameTime.instance.lightSourceUpdate = 100.0F;
               }

               if (this.square != nullptr) {
                  this.square.RecalcProperties();
               }
            }
         }
      }
   }

    InventoryItem removeMetalBar(IsoGameCharacter var1) {
      if (this.metalBarHealth <= 0) {
    return nullptr;
      } else {
    float var2 = Math.min(this.metalBarHealth / 3000.0F, 1.0F);
         this.metalBarHealth = 0;
    InventoryItem var3 = InventoryItemFactory.CreateItem("Base.MetalBar");
         var3.setCondition((int)Math.max(var3.getConditionMax() * var2, 1.0F));
         if (this.square != nullptr) {
            if (GameServer.bServer) {
               this.square.transmitRemoveItemFromSquare(this);
            } else {
               this.square.RemoveTileObject(this);
            }
         }

    return var3;
      }
   }

    void addMetal(IsoGameCharacter var1, InventoryItem var2) {
      if (this.getNumPlanks() <= 0) {
         if (this.metalHealth <= 0) {
            this.metalHealth = 5000;
            if (var2 != nullptr) {
               this.metalHealth = (int)((float)var2.getCondition() / var2.getConditionMax() * 5000.0F);
            }

            if (var1 != nullptr) {
               this.metalHealth = (int)(this.metalHealth * var1.getMetalBarricadeStrengthMod());
            }

            this.chooseSprite();
            if (!GameServer.bServer) {
               for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
                  LosUtil.cachecleared[var3] = true;
               }

               IsoGridSquare.setRecalcLightTime(-1);
               GameTime.instance.lightSourceUpdate = 100.0F;
            }

            if (this.square != nullptr) {
               this.square.RecalcProperties();
            }
         }
      }
   }

    bool isMetalBar() {
      return this.metalBarHealth > 0;
   }

    InventoryItem removeMetal(IsoGameCharacter var1) {
      if (this.metalHealth <= 0) {
    return nullptr;
      } else {
    float var2 = Math.min(this.metalHealth / 5000.0F, 1.0F);
         this.metalHealth = 0;
    InventoryItem var3 = InventoryItemFactory.CreateItem("Base.SheetMetal");
         var3.setCondition((int)Math.max(var3.getConditionMax() * var2, 1.0F));
         if (this.square != nullptr) {
            if (GameServer.bServer) {
               this.square.transmitRemoveItemFromSquare(this);
            } else {
               this.square.RemoveTileObject(this);
            }
         }

    return var3;
      }
   }

    bool isMetal() {
      return this.metalHealth > 0;
   }

    bool isBlockVision() {
      return this.isMetal() || this.getNumPlanks() > 2;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void chooseSprite() {
    IsoSpriteManager var1 = IsoSpriteManager.instance;
      if (this.metalHealth > 0) {
    int var5 = this.metalHealth <= 2500 ? 2 : 0;
    std::string var6 = "constructedobjects_01";
         switch (1.$SwitchMap$zombie$iso$IsoDirections[this.dir.ordinal()]) {
            case 1:
               this.sprite = var1.getSprite(var6 + "_" + (24 + var5));
               break;
            case 2:
               this.sprite = var1.getSprite(var6 + "_" + (25 + var5));
               break;
            case 3:
               this.sprite = var1.getSprite(var6 + "_" + (28 + var5));
               break;
            case 4:
               this.sprite = var1.getSprite(var6 + "_" + (29 + var5));
               break;
            default:
               this.sprite.LoadFramesNoDirPageSimple("media/ui/missing-tile.png");
         }
      } else if (this.metalBarHealth > 0) {
    std::string var4 = "constructedobjects_01";
         switch (1.$SwitchMap$zombie$iso$IsoDirections[this.dir.ordinal()]) {
            case 1:
               this.sprite = var1.getSprite(var4 + "_55");
               break;
            case 2:
               this.sprite = var1.getSprite(var4 + "_53");
               break;
            case 3:
               this.sprite = var1.getSprite(var4 + "_52");
               break;
            case 4:
               this.sprite = var1.getSprite(var4 + "_54");
               break;
            default:
               this.sprite.LoadFramesNoDirPageSimple("media/ui/missing-tile.png");
         }
      } else {
    int var2 = this.getNumPlanks();
         if (var2 <= 0) {
            this.sprite = var1.getSprite("media/ui/missing-tile.png");
         } else {
    std::string var3 = "carpentry_01";
            switch (1.$SwitchMap$zombie$iso$IsoDirections[this.dir.ordinal()]) {
               case 1:
                  this.sprite = var1.getSprite(var3 + "_" + (8 + (var2 - 1) * 2));
                  break;
               case 2:
                  this.sprite = var1.getSprite(var3 + "_" + (9 + (var2 - 1) * 2));
                  break;
               case 3:
                  this.sprite = var1.getSprite(var3 + "_" + (0 + (var2 - 1) * 2));
                  break;
               case 4:
                  this.sprite = var1.getSprite(var3 + "_" + (1 + (var2 - 1) * 2));
                  break;
               default:
                  this.sprite.LoadFramesNoDirPageSimple("media/ui/missing-tile.png");
            }
         }
      }
   }

    bool isDestroyed() {
      return this.metalHealth <= 0 && this.getNumPlanks() <= 0 && this.metalBarHealth <= 0;
   }

    bool TestCollide(IsoMovingObject var1, IsoGridSquare var2, IsoGridSquare var3) {
    return false;
   }

    VisionResult TestVision(IsoGridSquare var1, IsoGridSquare var2) {
      if (this.metalHealth <= 0 && this.getNumPlanks() <= 2) {
         return VisionResult.NoEffect;
      } else {
         if (var1 == this.square) {
            if (this.dir == IsoDirections.N && var2.getY() < var1.getY()) {
               return VisionResult.Blocked;
            }

            if (this.dir == IsoDirections.S && var2.getY() > var1.getY()) {
               return VisionResult.Blocked;
            }

            if (this.dir == IsoDirections.W && var2.getX() < var1.getX()) {
               return VisionResult.Blocked;
            }

            if (this.dir == IsoDirections.E && var2.getX() > var1.getX()) {
               return VisionResult.Blocked;
            }
         } else if (var2 == this.square && var1 != this.square) {
            return this.TestVision(var2, var1);
         }

         return VisionResult.NoEffect;
      }
   }

    void Thump(IsoMovingObject var1) {
      if (!this.isDestroyed()) {
         if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
    int var2 = this.getNumPlanks();
    bool var3 = this.metalHealth > 2500;
    int var4 = ThumpState.getFastForwardDamageMultiplier();
            this.Damage(((IsoZombie)var1).strength * var4);
            if (var2 != this.getNumPlanks()) {
               ((IsoGameCharacter)var1).getEmitter().playSound("BreakBarricadePlank");
               if (GameServer.bServer) {
                  GameServer.PlayWorldSoundServer("BreakBarricadePlank", false, var1.getCurrentSquare(), 0.2F, 20.0F, 1.1F, true);
               }
            }

            if (this.isDestroyed()) {
               if (this.getSquare().getBuilding() != nullptr) {
                  this.getSquare().getBuilding().forceAwake();
               }

               this.square.transmitRemoveItemFromSquare(this);
               if (!GameServer.bServer) {
                  this.square.RemoveTileObject(this);
               }
            } else if ((var2 != this.getNumPlanks() || var3 && this.metalHealth < 2500) && GameServer.bServer) {
               this.sendObjectChange("state");
            }

            if (!this.isDestroyed()) {
               this.setRenderEffect(RenderEffectType.Hit_Door, true);
            }

            WorldSoundManager.instance.addSound(var1, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, true, 4.0F, 15.0F);
         }
      }
   }

    Thumpable getThumpableFor(IsoGameCharacter var1) {
      return this.isDestroyed() ? nullptr : this;
   }

    Vector2 getFacingPosition(Vector2 var1) {
      if (this.square == nullptr) {
         return var1.set(0.0F, 0.0F);
      } else if (this.dir == IsoDirections.N) {
         return var1.set(this.getX() + 0.5F, this.getY());
      } else if (this.dir == IsoDirections.S) {
         return var1.set(this.getX() + 0.5F, this.getY() + 1.0F);
      } else if (this.dir == IsoDirections.W) {
         return var1.set(this.getX(), this.getY() + 0.5F);
      } else {
         return this.dir == IsoDirections.E ? var1.set(this.getX() + 1.0F, this.getY() + 0.5F) : var1.set(this.getX(), this.getY() + 0.5F);
      }
   }

    void WeaponHit(IsoGameCharacter var1, HandWeapon var2) {
      if (!this.isDestroyed()) {
    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
         if (GameClient.bClient) {
            if (var3 != nullptr) {
               GameClient.instance.sendWeaponHit(var3, var2, this);
            }
         } else {
            LuaEventManager.triggerEvent("OnWeaponHitThumpable", var1, var2, this);
    std::string var4 = !this.isMetal() && !this.isMetalBar() ? "HitBarricadePlank" : "HitBarricadeMetal";
            if (var3 != nullptr) {
               var3.setMeleeHitSurface(!this.isMetal() && !this.isMetalBar() ? Material.Wood : Material.Metal);
            }

            SoundManager.instance.PlayWorldSound(var4, false, this.getSquare(), 1.0F, 20.0F, 2.0F, false);
            if (GameServer.bServer) {
               GameServer.PlayWorldSoundServer(var4, false, this.getSquare(), 1.0F, 20.0F, 2.0F, false);
            }

            if (var2 != nullptr) {
               this.Damage(var2.getDoorDamage() * 5);
            } else {
               this.Damage(100);
            }

            WorldSoundManager.instance.addSound(var1, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, false, 0.0F, 15.0F);
            if (this.isDestroyed()) {
               if (var1 != nullptr) {
    std::string var5 = var4 == "HitBarricadeMetal" ? "BreakBarricadeMetal" : "BreakBarricadePlank";
                  var1.getEmitter().playSound(var5);
                  if (GameServer.bServer) {
                     GameServer.PlayWorldSoundServer(var5, false, var1.getCurrentSquare(), 0.2F, 20.0F, 1.1F, true);
                  }
               }

               this.square.transmitRemoveItemFromSquare(this);
               if (!GameServer.bServer) {
                  this.square.RemoveTileObject(this);
               }
            }

            if (!this.isDestroyed()) {
               this.setRenderEffect(RenderEffectType.Hit_Door, true);
            }
         }
      }
   }

    void DamageBarricade(int var1) {
      this.Damage(var1);
   }

    void Damage(int var1) {
      if (!"Tutorial" == Core.GameMode)) {
         if (this.metalHealth > 0) {
            this.metalHealth -= var1;
            if (this.metalHealth <= 0) {
               this.metalHealth = 0;
               this.chooseSprite();
            }
         } else if (this.metalBarHealth > 0) {
            this.metalBarHealth -= var1;
            if (this.metalBarHealth <= 0) {
               this.metalBarHealth = 0;
               this.chooseSprite();
            }
         } else {
            for (int var2 = 3; var2 >= 0; var2--) {
               if (this.plankHealth[var2] > 0) {
                  this.plankHealth[var2] = this.plankHealth[var2] - var1;
                  if (this.plankHealth[var2] <= 0) {
                     this.plankHealth[var2] = 0;
                     this.chooseSprite();
                  }
                  break;
               }
            }
         }
      }
   }

    float getThumpCondition() {
      if (this.metalHealth > 0) {
         return PZMath.clamp(this.metalHealth, 0, 5000) / 5000.0F;
      } else if (this.metalBarHealth > 0) {
         return PZMath.clamp(this.metalBarHealth, 0, 3000) / 3000.0F;
      } else {
         for (int var1 = 3; var1 >= 0; var1--) {
            if (this.plankHealth[var1] > 0) {
               return PZMath.clamp(this.plankHealth[var1], 0, 1000) / 1000.0F;
            }
         }

         return 0.0F;
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
    uint8_t var4 = var1.get();
      this.dir = IsoDirections.fromIndex(var4);
    uint8_t var5 = var1.get();

      for (int var6 = 0; var6 < var5; var6++) {
    short var7 = var1.getShort();
         if (var6 < 4) {
            this.plankHealth[var6] = var7;
         }
      }

      this.metalHealth = var1.getShort();
      if (var2 >= 90) {
         this.metalBarHealth = var1.getShort();
      }

      this.chooseSprite();
   }

    void save(ByteBuffer var1, bool var2) {
      var1.put((byte)1);
      var1.put(IsoObject.factoryGetClassID(this.getObjectName()));
      var1.put((byte)this.dir.index());
      var1.put((byte)4);

      for (int var3 = 0; var3 < 4; var3++) {
         var1.putShort((short)this.plankHealth[var3]);
      }

      var1.putShort((short)this.metalHealth);
      var1.putShort((short)this.metalBarHealth);
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      if ("state" == var1)) {
         for (int var4 = 0; var4 < 4; var4++) {
            var3.putShort((short)this.plankHealth[var4]);
         }

         var3.putShort((short)this.metalHealth);
         var3.putShort((short)this.metalBarHealth);
      }
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      if ("state" == var1)) {
         for (int var3 = 0; var3 < 4; var3++) {
            this.plankHealth[var3] = var2.getShort();
         }

         this.metalHealth = var2.getShort();
         this.metalBarHealth = var2.getShort();
         this.chooseSprite();
         if (this.square != nullptr) {
            this.square.RecalcProperties();
         }

         for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
            LosUtil.cachecleared[var4] = true;
         }

         IsoGridSquare.setRecalcLightTime(-1);
         GameTime.instance.lightSourceUpdate = 100.0F;
      }
   }

    BarricadeAble getBarricadedObject() {
    int var1 = this.getSpecialObjectIndex();
      if (var1 == -1) {
    return nullptr;
      } else {
    std::vector var2 = this.getSquare().getSpecialObjects();
         if (this.getDir() != IsoDirections.W && this.getDir() != IsoDirections.N) {
            if (this.getDir() == IsoDirections.E || this.getDir() == IsoDirections.S) {
    bool var10 = this.getDir() == IsoDirections.S;
    int var11 = this.getSquare().getX() + (this.getDir() == IsoDirections.E ? 1 : 0);
    int var12 = this.getSquare().getY() + (this.getDir() == IsoDirections.S ? 1 : 0);
    IsoGridSquare var6 = this.getCell().getGridSquare(var11, var12, this.getZ());
               if (var6 != nullptr) {
                  var2 = var6.getSpecialObjects();

                  for (int var7 = var2.size() - 1; var7 >= 0; var7--) {
    IsoObject var8 = (IsoObject)var2.get(var7);
                     if (dynamic_cast<BarricadeAble*>(var8) != nullptr && var10 == ((BarricadeAble)var8).getNorth()) {
                        return (BarricadeAble)var8;
                     }
                  }
               }
            }
         } else {
    bool var3 = this.getDir() == IsoDirections.N;

            for (int var4 = var1 - 1; var4 >= 0; var4--) {
    IsoObject var5 = (IsoObject)var2.get(var4);
               if (dynamic_cast<BarricadeAble*>(var5) != nullptr && var3 == ((BarricadeAble)var5).getNorth()) {
                  return (BarricadeAble)var5;
               }
            }
         }

    return nullptr;
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
    int var8 = IsoCamera.frameState.playerIndex;
    BarricadeAble var9 = this.getBarricadedObject();
      if (var9 != nullptr && this.square.lighting[var8].targetDarkMulti() <= var9.getSquare().lighting[var8].targetDarkMulti()) {
         var4 = var9.getSquare().lighting[var8].lightInfo();
         this.setTargetAlpha(var8, ((IsoObject)var9).getTargetAlpha(var8));
      }

      super.render(var1, var2, var3, var4, var5, var6, var7);
   }

    static IsoBarricade GetBarricadeOnSquare(IsoGridSquare var0, IsoDirections var1) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
         for (int var2 = 0; var2 < var0.getSpecialObjects().size(); var2++) {
    IsoObject var3 = (IsoObject)var0.getSpecialObjects().get(var2);
            if (dynamic_cast<IsoBarricade*>(var3) != nullptr var4 && var4.getDir() == var1) {
    return var4;
            }
         }

    return nullptr;
      }
   }

    static IsoBarricade GetBarricadeForCharacter(BarricadeAble var0, IsoGameCharacter var1) {
      if (var0 != nullptr && var0.getSquare() != nullptr) {
         if (var1 != nullptr) {
            if (var0.getNorth()) {
               if (var1.getY() < var0.getSquare().getY()) {
    return GetBarricadeOnSquare();
               }
            } else if (var1.getX() < var0.getSquare().getX()) {
    return GetBarricadeOnSquare();
            }
         }

    return GetBarricadeOnSquare();
      } else {
    return nullptr;
      }
   }

    static IsoBarricade GetBarricadeOppositeCharacter(BarricadeAble var0, IsoGameCharacter var1) {
      if (var0 != nullptr && var0.getSquare() != nullptr) {
         if (var1 != nullptr) {
            if (var0.getNorth()) {
               if (var1.getY() < var0.getSquare().getY()) {
    return GetBarricadeOnSquare();
               }
            } else if (var1.getX() < var0.getSquare().getX()) {
    return GetBarricadeOnSquare();
            }
         }

    return GetBarricadeOnSquare();
      } else {
    return nullptr;
      }
   }

    static IsoBarricade AddBarricadeToObject(BarricadeAble var0, bool var1) {
    IsoGridSquare var2 = var1 ? var0.getOppositeSquare() : var0.getSquare();
    void* var3 = nullptr;
      if (var0.getNorth()) {
         var3 = var1 ? IsoDirections.S : IsoDirections.N;
      } else {
         var3 = var1 ? IsoDirections.E : IsoDirections.W;
      }

      if (var2 != nullptr && var3 != nullptr) {
    IsoBarricade var4 = GetBarricadeOnSquare(var2, (IsoDirections)var3);
         if (var4 != nullptr) {
    return var4;
         } else {
            var4 = std::make_shared<IsoBarricade>(IsoWorld.instance.CurrentCell, var2, (IsoDirections)var3);
    int var5 = -1;

            for (int var6 = 0; var6 < var2.getObjects().size(); var6++) {
    IsoObject var7 = (IsoObject)var2.getObjects().get(var6);
               if (dynamic_cast<IsoCurtain*>(var7) != nullptr var8) {
                  if (var8.getType() == IsoObjectType.curtainW && var3 == IsoDirections.W) {
                     var5 = var6;
                  } else if (var8.getType() == IsoObjectType.curtainN && var3 == IsoDirections.N) {
                     var5 = var6;
                  } else if (var8.getType() == IsoObjectType.curtainE && var3 == IsoDirections.E) {
                     var5 = var6;
                  } else if (var8.getType() == IsoObjectType.curtainS && var3 == IsoDirections.S) {
                     var5 = var6;
                  }

                  if (var5 != -1) {
                     break;
                  }
               }
            }

            var2.AddSpecialObject(var4, var5);

            for (int var11 = 0; var11 < IsoPlayer.numPlayers; var11++) {
               LosUtil.cachecleared[var11] = true;
            }

            IsoGridSquare.setRecalcLightTime(-1);
            GameTime.instance.lightSourceUpdate = 100.0F;
    return var4;
         }
      } else {
    return nullptr;
      }
   }

    static IsoBarricade AddBarricadeToObject(BarricadeAble var0, IsoGameCharacter var1) {
      if (var0 == nullptr || var0.getSquare() == nullptr || var1 == nullptr) {
    return nullptr;
      } else if (var0.getNorth()) {
    bool var3 = var1.getY() < var0.getSquare().getY();
    return AddBarricadeToObject();
      } else {
    bool var2 = var1.getX() < var0.getSquare().getX();
    return AddBarricadeToObject();
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
