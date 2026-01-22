#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SystemDisabler.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/states/ThumpState.h"
#include "zombie/characters/BaseCharacterSoundEmitter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Translator.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/BrokenFences.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObject/VisionResult.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/LosUtil/TestResults.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/IsoThumpable/1.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/util/Type.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeader/HeaderSize.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include "zombie/world/WorldDictionary.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoThumpable : public IsoObject {
public:
    KahluaTable table;
    KahluaTable modData;
    bool isDoor = false;
    bool isDoorFrame = false;
    std::string breakSound = "BreakObject";
    bool isCorner = false;
    bool isFloor = false;
    bool blockAllTheSquare = false;
    bool Locked = false;
    int MaxHealth = 500;
    int Health = 500;
    int PushedMaxStrength = 0;
    int PushedStrength = 0;
    IsoSprite closedSprite;
    bool north = false;
    int thumpDmg = 8;
    float crossSpeed = 1.0F;
    bool open = false;
    IsoSprite openSprite;
    bool destroyed = false;
    bool canBarricade = false;
    bool canPassThrough = false;
    bool isStairs = false;
    bool isContainer = false;
    bool dismantable = false;
    bool canBePlastered = false;
    bool paintable = false;
    bool isThumpable = true;
    bool isHoppable = false;
    int lightSourceRadius = -1;
    int lightSourceLife = -1;
    int lightSourceXOffset = 0;
    int lightSourceYOffset = 0;
    bool lightSourceOn = false;
    IsoLightSource lightSource = nullptr;
    std::string lightSourceFuel = nullptr;
    float lifeLeft = -1.0F;
    float lifeDelta = 0.0F;
    bool haveFuel = false;
    float updateAccumulator = 0.0F;
    float lastUpdateHours = -1.0F;
    int keyId = -1;
    bool lockedByKey = false;
    bool lockedByPadlock = false;
    bool canBeLockByPadlock = false;
    int lockedByCode = 0;
    int OldNumPlanks = 0;
    std::string thumpSound = "ZombieThumpGeneric";
    static const Vector2 tempo = std::make_shared<Vector2>();

    KahluaTable getModData() {
      if (this.modData == nullptr) {
         this.modData = LuaManager.platform.newTable();
      }

      return this.modData;
   }

    void setModData(KahluaTable var1) {
      this.modData = var1;
   }

    bool hasModData() {
      return this.modData != nullptr && !this.modData.empty();
   }

    bool isCanPassThrough() {
      return this.canPassThrough;
   }

    void setCanPassThrough(bool var1) {
      this.canPassThrough = var1;
   }

    bool isBlockAllTheSquare() {
      return this.blockAllTheSquare;
   }

    void setBlockAllTheSquare(bool var1) {
      this.blockAllTheSquare = var1;
   }

    void setIsDismantable(bool var1) {
      this.dismantable = var1;
   }

    bool isDismantable() {
      return this.dismantable;
   }

    float getCrossSpeed() {
      return this.crossSpeed;
   }

    void setCrossSpeed(float var1) {
      this.crossSpeed = var1;
   }

    void setIsFloor(bool var1) {
      this.isFloor = var1;
   }

    bool isCorner() {
      return this.isCorner;
   }

    bool isFloor() {
      return this.isFloor;
   }

    void setIsContainer(bool var1) {
      this.isContainer = var1;
      if (var1) {
         this.container = std::make_shared<ItemContainer>("crate", this.square, this);
         if (this.sprite.getProperties().Is("ContainerCapacity")) {
            this.container.Capacity = int.parseInt(this.sprite.getProperties().Val("ContainerCapacity"));
         }

         this.container.setExplored(true);
      }
   }

    void setIsStairs(bool var1) {
      this.isStairs = var1;
   }

    bool isStairs() {
      return this.isStairs;
   }

    bool isWindow() {
      return this.sprite != nullptr && (this.sprite.getProperties().Is(IsoFlagType.WindowN) || this.sprite.getProperties().Is(IsoFlagType.WindowW));
   }

    std::string getObjectName() {
      return "Thumpable";
   }

    public IsoThumpable(IsoCell var1) {
      super(var1);
   }

    void setCorner(bool var1) {
      this.isCorner = var1;
   }

    void setCanBarricade(bool var1) {
      this.canBarricade = var1;
   }

    bool getCanBarricade() {
      return this.canBarricade;
   }

    void setHealth(int var1) {
      this.Health = var1;
   }

    int getHealth() {
      return this.Health;
   }

    void setMaxHealth(int var1) {
      this.MaxHealth = var1;
   }

    int getMaxHealth() {
      return this.MaxHealth;
   }

    void setThumpDmg(int var1) {
      this.thumpDmg = var1;
   }

    int getThumpDmg() {
      return this.thumpDmg;
   }

    void setBreakSound(const std::string& var1) {
      this.breakSound = var1;
   }

    std::string getBreakSound() {
      return this.breakSound;
   }

    bool isDoor() {
      return this.isDoor;
   }

    bool getNorth() {
      return this.north;
   }

    Vector2 getFacingPosition(Vector2 var1) {
      if (this.square == nullptr) {
         return var1.set(0.0F, 0.0F);
      } else if (this.isDoor
         || this.isDoorFrame
         || this.isWindow()
         || this.isHoppable
         || this.getProperties() != nullptr && (this.getProperties().Is(IsoFlagType.collideN) || this.getProperties().Is(IsoFlagType.collideW))) {
         return this.north ? var1.set(this.getX() + 0.5F, this.getY()) : var1.set(this.getX(), this.getY() + 0.5F);
      } else {
         return var1.set(this.getX() + 0.5F, this.getY() + 0.5F);
      }
   }

    bool isDoorFrame() {
      return this.isDoorFrame;
   }

    void setIsDoor(bool var1) {
      this.isDoor = var1;
   }

    void setIsDoorFrame(bool var1) {
      this.isDoorFrame = var1;
   }

    void setSprite(const std::string& var1) {
      this.closedSprite = IsoSpriteManager.instance.getSprite(var1);
      this.sprite = this.closedSprite;
   }

    void setSpriteFromName(const std::string& var1) {
      this.sprite = IsoSpriteManager.instance.getSprite(var1);
   }

    void setClosedSprite(IsoSprite var1) {
      this.closedSprite = var1;
      this.sprite = this.closedSprite;
   }

    void setOpenSprite(IsoSprite var1) {
      this.openSprite = var1;
   }

    public IsoThumpable(IsoCell var1, IsoGridSquare var2, const std::string& var3, const std::string& var4, bool var5, KahluaTable var6) {
      this.OutlineOnMouseover = true;
      this.PushedMaxStrength = this.PushedStrength = 2500;
      this.openSprite = IsoSpriteManager.instance.getSprite(var4);
      this.closedSprite = IsoSpriteManager.instance.getSprite(var3);
      this.table = var6;
      this.sprite = this.closedSprite;
      this.square = var2;
      this.north = var5;
   }

    public IsoThumpable(IsoCell var1, IsoGridSquare var2, const std::string& var3, bool var4, KahluaTable var5) {
      this.OutlineOnMouseover = true;
      this.PushedMaxStrength = this.PushedStrength = 2500;
      this.closedSprite = IsoSpriteManager.instance.getSprite(var3);
      this.table = var5;
      this.sprite = this.closedSprite;
      this.square = var2;
      this.north = var4;
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
    BitHeaderRead var4 = BitHeader.allocRead(HeaderSize.int64_t, var1);
      this.OutlineOnMouseover = true;
      this.PushedMaxStrength = this.PushedStrength = 2500;
      if (!var4 == 0)) {
         this.open = var4.hasFlags(1);
         this.Locked = var4.hasFlags(2);
         this.north = var4.hasFlags(4);
         if (var4.hasFlags(8)) {
            this.MaxHealth = var1.getInt();
         }

         if (var4.hasFlags(16)) {
            this.Health = var1.getInt();
         } else {
            this.Health = this.MaxHealth;
         }

         if (var4.hasFlags(32)) {
            this.closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
         }

         if (var4.hasFlags(64)) {
            this.openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
         }

         if (var4.hasFlags(128)) {
            this.thumpDmg = var1.getInt();
         }

         this.isDoor = var4.hasFlags(512);
         this.isDoorFrame = var4.hasFlags(1024);
         this.isCorner = var4.hasFlags(2048);
         this.isStairs = var4.hasFlags(4096);
         this.isContainer = var4.hasFlags(8192);
         this.isFloor = var4.hasFlags(16384);
         this.canBarricade = var4.hasFlags(32768);
         this.canPassThrough = var4.hasFlags(65536);
         this.dismantable = var4.hasFlags(131072);
         this.canBePlastered = var4.hasFlags(262144);
         this.paintable = var4.hasFlags(524288);
         if (var4.hasFlags(1048576)) {
            this.crossSpeed = var1.getFloat();
         }

         if (var4.hasFlags(2097152)) {
            if (this.table == nullptr) {
               this.table = LuaManager.platform.newTable();
            }

            this.table.load(var1, var2);
         }

         if (var4.hasFlags(4194304)) {
            if (this.modData == nullptr) {
               this.modData = LuaManager.platform.newTable();
            }

            this.modData.load(var1, var2);
         }

         this.blockAllTheSquare = var4.hasFlags(8388608);
         this.isThumpable = var4.hasFlags(16777216);
         this.isHoppable = var4.hasFlags(33554432);
         if (var4.hasFlags(67108864)) {
            this.setLightSourceLife(var1.getInt());
         }

         if (var4.hasFlags(134217728)) {
            this.setLightSourceRadius(var1.getInt());
         }

         if (var4.hasFlags(268435456)) {
            this.setLightSourceXOffset(var1.getInt());
         }

         if (var4.hasFlags(536870912)) {
            this.setLightSourceYOffset(var1.getInt());
         }

         if (var4.hasFlags(1073741824)) {
            this.setLightSourceFuel(WorldDictionary.getItemTypeFromID(var1.getShort()));
         }

         if (var4.hasFlags(2147483648L)) {
            this.setLifeDelta(var1.getFloat());
         }

         if (var4.hasFlags(4294967296L)) {
            this.setLifeLeft(var1.getFloat());
         }

         if (var4.hasFlags(8589934592L)) {
            this.keyId = var1.getInt();
         }

         this.lockedByKey = var4.hasFlags(17179869184L);
         this.lockedByPadlock = var4.hasFlags(34359738368L);
         this.canBeLockByPadlock = var4.hasFlags(68719476736L);
         if (var4.hasFlags(137438953472L)) {
            this.lockedByCode = var1.getInt();
         }

         if (var4.hasFlags(274877906944L)) {
            this.thumpSound = GameWindow.ReadString(var1);
            if ("thumpa2" == this.thumpSound)) {
               this.thumpSound = "ZombieThumpGeneric";
            }

            if ("metalthump" == this.thumpSound)) {
               this.thumpSound = "ZombieThumpMetal";
            }
         }

         if (var4.hasFlags(549755813888L)) {
            this.lastUpdateHours = var1.getFloat();
         }

         if (var2 >= 183) {
            if (var4.hasFlags(1099511627776L)) {
               this.haveFuel = true;
            }

            if (var4.hasFlags(2199023255552L)) {
               this.lightSourceOn = true;
            }
         }
      }

      var4.release();
      if (this.getLightSourceFuel() != nullptr) {
    bool var5 = this.isLightSourceOn();
         this.createLightSource(
            this.getLightSourceRadius(),
            this.getLightSourceXOffset(),
            this.getLightSourceYOffset(),
            0,
            this.getLightSourceLife(),
            this.getLightSourceFuel(),
            nullptr,
            nullptr
         );
         if (this.lightSource != nullptr) {
            this.getLightSource().setActive(var5);
         }

         this.setLightSourceOn(var5);
      }

      if (SystemDisabler.doObjectStateSyncEnable && GameClient.bClient) {
         GameClient.instance.objectSyncReq.putRequestLoad(this.square);
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
    BitHeaderWrite var3 = BitHeader.allocWrite(HeaderSize.int64_t, var1);
      if (this.open) {
         var3.addFlags(1);
      }

      if (this.Locked) {
         var3.addFlags(2);
      }

      if (this.north) {
         var3.addFlags(4);
      }

      if (this.MaxHealth != 500) {
         var3.addFlags(8);
         var1.putInt(this.MaxHealth);
      }

      if (this.Health != this.MaxHealth) {
         var3.addFlags(16);
         var1.putInt(this.Health);
      }

      if (this.closedSprite != nullptr) {
         var3.addFlags(32);
         var1.putInt(this.closedSprite.ID);
      }

      if (this.openSprite != nullptr) {
         var3.addFlags(64);
         var1.putInt(this.openSprite.ID);
      }

      if (this.thumpDmg != 8) {
         var3.addFlags(128);
         var1.putInt(this.thumpDmg);
      }

      if (this.isDoor) {
         var3.addFlags(512);
      }

      if (this.isDoorFrame) {
         var3.addFlags(1024);
      }

      if (this.isCorner) {
         var3.addFlags(2048);
      }

      if (this.isStairs) {
         var3.addFlags(4096);
      }

      if (this.isContainer) {
         var3.addFlags(8192);
      }

      if (this.isFloor) {
         var3.addFlags(16384);
      }

      if (this.canBarricade) {
         var3.addFlags(32768);
      }

      if (this.canPassThrough) {
         var3.addFlags(65536);
      }

      if (this.dismantable) {
         var3.addFlags(131072);
      }

      if (this.canBePlastered) {
         var3.addFlags(262144);
      }

      if (this.paintable) {
         var3.addFlags(524288);
      }

      if (this.crossSpeed != 1.0F) {
         var3.addFlags(1048576);
         var1.putFloat(this.crossSpeed);
      }

      if (this.table != nullptr && !this.table.empty()) {
         var3.addFlags(2097152);
         this.table.save(var1);
      }

      if (this.modData != nullptr && !this.modData.empty()) {
         var3.addFlags(4194304);
         this.modData.save(var1);
      }

      if (this.blockAllTheSquare) {
         var3.addFlags(8388608);
      }

      if (this.isThumpable) {
         var3.addFlags(16777216);
      }

      if (this.isHoppable) {
         var3.addFlags(33554432);
      }

      if (this.getLightSourceLife() != -1) {
         var3.addFlags(67108864);
         var1.putInt(this.getLightSourceLife());
      }

      if (this.getLightSourceRadius() != -1) {
         var3.addFlags(134217728);
         var1.putInt(this.getLightSourceRadius());
      }

      if (this.getLightSourceXOffset() != 0) {
         var3.addFlags(268435456);
         var1.putInt(this.getLightSourceXOffset());
      }

      if (this.getLightSourceYOffset() != 0) {
         var3.addFlags(536870912);
         var1.putInt(this.getLightSourceYOffset());
      }

      if (this.getLightSourceFuel() != nullptr) {
         var3.addFlags(1073741824);
         var1.putShort(WorldDictionary.getItemRegistryID(this.getLightSourceFuel()));
      }

      if (this.getLifeDelta() != 0.0F) {
         var3.addFlags(2147483648L);
         var1.putFloat(this.getLifeDelta());
      }

      if (this.getLifeLeft() != -1.0F) {
         var3.addFlags(4294967296L);
         var1.putFloat(this.getLifeLeft());
      }

      if (this.keyId != -1) {
         var3.addFlags(8589934592L);
         var1.putInt(this.keyId);
      }

      if (this.isLockedByKey()) {
         var3.addFlags(17179869184L);
      }

      if (this.isLockedByPadlock()) {
         var3.addFlags(34359738368L);
      }

      if (this.canBeLockByPadlock()) {
         var3.addFlags(68719476736L);
      }

      if (this.getLockedByCode() != 0) {
         var3.addFlags(137438953472L);
         var1.putInt(this.getLockedByCode());
      }

      if (!this.thumpSound == "ZombieThumbGeneric")) {
         var3.addFlags(274877906944L);
         GameWindow.WriteString(var1, this.thumpSound);
      }

      if (this.lastUpdateHours != -1.0F) {
         var3.addFlags(549755813888L);
         var1.putFloat(this.lastUpdateHours);
      }

      if (this.haveFuel) {
         var3.addFlags(1099511627776L);
      }

      if (this.lightSourceOn) {
         var3.addFlags(2199023255552L);
      }

      var3.write();
      var3.release();
   }

    bool isDestroyed() {
      return this.destroyed;
   }

    bool IsOpen() {
      return this.open;
   }

    bool IsStrengthenedByPushedItems() {
    return false;
   }

    bool onMouseLeftClick(int var1, int var2) {
    return false;
   }

    bool TestPathfindCollide(IsoMovingObject var1, IsoGridSquare var2, IsoGridSquare var3) {
    bool var4 = this.north;
      if (dynamic_cast<IsoSurvivor*>(var1) != nullptr && ((IsoSurvivor)var1).getInventory().contains("Hammer")) {
    return false;
      } else if (this.open) {
    return false;
      } else {
         if (var2 == this.square) {
            if (var4 && var3.getY() < var2.getY()) {
    return true;
            }

            if (!var4 && var3.getX() < var2.getX()) {
    return true;
            }
         } else {
            if (var4 && var3.getY() > var2.getY()) {
    return true;
            }

            if (!var4 && var3.getX() > var2.getX()) {
    return true;
            }
         }

    return false;
      }
   }

    bool TestCollide(IsoMovingObject var1, IsoGridSquare var2, IsoGridSquare var3) {
      if (dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isNoClip()) {
    return false;
      } else {
    bool var4 = this.north;
         if (this.open) {
    return false;
         } else if (this.blockAllTheSquare) {
            if (var2 != this.square) {
               if (var1 != nullptr) {
                  var1.collideWith(this);
               }

    return true;
            } else {
    return false;
            }
         } else {
            if (var2 == this.square) {
               if (var4 && var3.getY() < var2.getY()) {
                  if (var1 != nullptr) {
                     var1.collideWith(this);
                  }

                  if (!this.canPassThrough && !this.isStairs && !this.isCorner) {
    return true;
                  }
               }

               if (!var4 && var3.getX() < var2.getX()) {
                  if (var1 != nullptr) {
                     var1.collideWith(this);
                  }

                  if (!this.canPassThrough && !this.isStairs && !this.isCorner) {
    return true;
                  }
               }
            } else {
               if (var4 && var3.getY() > var2.getY()) {
                  if (var1 != nullptr) {
                     var1.collideWith(this);
                  }

                  if (!this.canPassThrough && !this.isStairs && !this.isCorner) {
    return true;
                  }
               }

               if (!var4 && var3.getX() > var2.getX()) {
                  if (var1 != nullptr) {
                     var1.collideWith(this);
                  }

                  if (!this.canPassThrough && !this.isStairs && !this.isCorner) {
    return true;
                  }
               }
            }

            if (this.isCorner) {
               if (var3.getY() < var2.getY() && var3.getX() < var2.getX()) {
                  if (var1 != nullptr) {
                     var1.collideWith(this);
                  }

                  if (!this.canPassThrough) {
    return true;
                  }
               }

               if (var3.getY() > var2.getY() && var3.getX() > var2.getX()) {
                  if (var1 != nullptr) {
                     var1.collideWith(this);
                  }

                  if (!this.canPassThrough) {
    return true;
                  }
               }
            }

    return false;
         }
      }
   }

    VisionResult TestVision(IsoGridSquare var1, IsoGridSquare var2) {
      if (this.canPassThrough) {
         return VisionResult.NoEffect;
      } else {
    bool var3 = this.north;
         if (this.open) {
            var3 = !var3;
         }

         if (var2.getZ() != var1.getZ()) {
            return VisionResult.NoEffect;
         } else {
    bool var4 = this.sprite != nullptr && this.sprite.getProperties().Is("doorTrans");
            if (var1 == this.square) {
               if (var3 && var2.getY() < var1.getY()) {
                  if (var4) {
                     return VisionResult.Unblocked;
                  }

                  if (this.isWindow()) {
                     return VisionResult.Unblocked;
                  }

                  return VisionResult.Blocked;
               }

               if (!var3 && var2.getX() < var1.getX()) {
                  if (var4) {
                     return VisionResult.Unblocked;
                  }

                  if (this.isWindow()) {
                     return VisionResult.Unblocked;
                  }

                  return VisionResult.Blocked;
               }
            } else {
               if (var3 && var2.getY() > var1.getY()) {
                  if (var4) {
                     return VisionResult.Unblocked;
                  }

                  if (this.isWindow()) {
                     return VisionResult.Unblocked;
                  }

                  return VisionResult.Blocked;
               }

               if (!var3 && var2.getX() > var1.getX()) {
                  if (var4) {
                     return VisionResult.Unblocked;
                  }

                  if (this.isWindow()) {
                     return VisionResult.Unblocked;
                  }

                  return VisionResult.Blocked;
               }
            }

            return VisionResult.NoEffect;
         }
      }
   }

    void Thump(IsoMovingObject var1) {
      if (SandboxOptions.instance.Lore.ThumpOnConstruction.getValue()) {
         if (dynamic_cast<IsoGameCharacter*>(var1) != nullptr) {
    Thumpable var2 = this.getThumpableFor((IsoGameCharacter)var1);
            if (var2 == nullptr) {
               return;
            }

            if (var2 != this) {
               var2.Thump(var1);
               return;
            }
         }

    bool var6 = BrokenFences.getInstance().isBreakableObject(this);
         if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
            if (((IsoZombie)var1).cognition == 1 && this.isDoor() && !this.IsOpen() && !this.isLocked()) {
               this.ToggleDoor((IsoGameCharacter)var1);
               return;
            }

    int var3 = var1.getCurrentSquare().getMovingObjects().size();
            if (var1.getCurrentSquare().getW() != nullptr) {
               var3 += var1.getCurrentSquare().getW().getMovingObjects().size();
            }

            if (var1.getCurrentSquare().getE() != nullptr) {
               var3 += var1.getCurrentSquare().getE().getMovingObjects().size();
            }

            if (var1.getCurrentSquare().getS() != nullptr) {
               var3 += var1.getCurrentSquare().getS().getMovingObjects().size();
            }

            if (var1.getCurrentSquare().getN() != nullptr) {
               var3 += var1.getCurrentSquare().getN().getMovingObjects().size();
            }

    int var4 = this.thumpDmg;
            if (var3 >= var4) {
    int var5 = 1 * ThumpState.getFastForwardDamageMultiplier();
               this.Health -= var5;
            } else {
               this.partialThumpDmg = this.partialThumpDmg + (float)var3 / var4 * ThumpState.getFastForwardDamageMultiplier();
               if ((int)this.partialThumpDmg > 0) {
    int var9 = (int)this.partialThumpDmg;
                  this.Health -= var9;
                  this.partialThumpDmg -= var9;
               }
            }

            WorldSoundManager.instance.addSound(var1, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, true, 4.0F, 15.0F);
            if (this.isDoor()) {
               this.setRenderEffect(RenderEffectType.Hit_Door, true);
            }
         }

         if (this.Health <= 0) {
            ((IsoGameCharacter)var1).getEmitter().playSound(this.breakSound, this);
            if (GameServer.bServer) {
               GameServer.PlayWorldSoundServer((IsoGameCharacter)var1, this.breakSound, false, var1.getCurrentSquare(), 0.2F, 20.0F, 1.1F, true);
            }

            WorldSoundManager.instance.addSound(nullptr, this.square.getX(), this.square.getY(), this.square.getZ(), 10, 20, true, 4.0F, 15.0F);
            var1.setThumpTarget(nullptr);
            if (IsoDoor.destroyDoubleDoor(this)) {
               return;
            }

            if (IsoDoor.destroyGarageDoor(this)) {
               return;
            }

            if (var6) {
    PropertyContainer var8 = this.getProperties();
    IsoDirections var7;
               if (var8.Is(IsoFlagType.collideN) && var8.Is(IsoFlagType.collideW)) {
                  var7 = var1.getY() >= this.getY() ? IsoDirections.N : IsoDirections.S;
               } else if (var8.Is(IsoFlagType.collideN)) {
                  var7 = var1.getY() >= this.getY() ? IsoDirections.N : IsoDirections.S;
               } else {
                  var7 = var1.getX() >= this.getX() ? IsoDirections.W : IsoDirections.E;
               }

               BrokenFences.getInstance().destroyFence(this, var7);
               return;
            }

            this.destroy();
         }
      }
   }

    Thumpable getThumpableFor(IsoGameCharacter var1) {
      if (this.isDoor() || this.isWindow()) {
    IsoBarricade var2 = this.getBarricadeForCharacter(var1);
         if (var2 != nullptr) {
    return var2;
         }

         var2 = this.getBarricadeOppositeCharacter(var1);
         if (var2 != nullptr) {
    return var2;
         }
      }

    bool var5 = this.isThumpable;
    bool var3 = dynamic_cast<IsoZombie*>(var1) != nullptr && ((IsoZombie)var1).isCrawling();
      if (!var5 && var3 && BrokenFences.getInstance().isBreakableObject(this)) {
         var5 = true;
      }

      if (!var5 && var3 && this.isHoppable()) {
         var5 = true;
      }

      if (var5 && !this.isDestroyed()) {
         if ((!this.isDoor() || !this.IsOpen()) && !this.isWindow()) {
            return !var3 && this.isHoppable() ? nullptr : this;
         } else {
    return nullptr;
         }
      } else {
    return nullptr;
      }
   }

    float getThumpCondition() {
      return (float)PZMath.clamp(this.Health, 0, this.MaxHealth) / this.MaxHealth;
   }

    void WeaponHit(IsoGameCharacter var1, HandWeapon var2) {
    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
      if (GameClient.bClient) {
         if (var3 != nullptr) {
            GameClient.instance.sendWeaponHit(var3, var2, this);
         }

         if (this.isDoor()) {
            this.setRenderEffect(RenderEffectType.Hit_Door, true);
         }
      } else {
    Thumpable var4 = this.getThumpableFor(var1);
         if (var4 != nullptr) {
            if (dynamic_cast<IsoBarricade*>(var4) != nullptr) {
               ((IsoBarricade)var4).WeaponHit(var1, var2);
            } else {
               LuaEventManager.triggerEvent("OnWeaponHitThumpable", var1, var2, this);
               this.Damage(var2.getDoorDamage());
               if (var2.getDoorHitSound() != nullptr) {
                  if (var3 != nullptr) {
                     var3.setMeleeHitSurface(this.getSoundPrefix());
                  }

                  var1.getEmitter().playSound(var2.getDoorHitSound(), this);
                  if (GameServer.bServer) {
                     GameServer.PlayWorldSoundServer(var1, var2.getDoorHitSound(), false, this.getSquare(), 0.2F, 20.0F, 1.0F, false);
                  }
               }

               WorldSoundManager.instance.addSound(var1, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, false, 0.0F, 15.0F);
               if (this.isDoor()) {
                  this.setRenderEffect(RenderEffectType.Hit_Door, true);
               }

               if (!this.IsStrengthenedByPushedItems() && this.Health <= 0 || this.IsStrengthenedByPushedItems() && this.Health <= -this.PushedMaxStrength) {
                  var1.getEmitter().playSound(this.breakSound, this);
                  WorldSoundManager.instance.addSound(var1, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, false, 0.0F, 15.0F);
                  if (GameClient.bClient) {
                     GameClient.instance
                        .sendClientCommandV(
                           nullptr,
                           "object",
                           "OnDestroyIsoThumpable",
                           new Object[]{"x", (int)this.getX(), "y", (int)this.getY(), "z", (int)this.getZ(), "index", this.getObjectIndex()}
                        );
                  }

                  LuaEventManager.triggerEvent("OnDestroyIsoThumpable", this, nullptr);
                  if (IsoDoor.destroyDoubleDoor(this)) {
                     return;
                  }

                  if (IsoDoor.destroyGarageDoor(this)) {
                     return;
                  }

                  this.destroyed = true;
                  if (this.getObjectIndex() != -1) {
                     this.square.transmitRemoveItemFromSquare(this);
                  }
               }
            }
         }
      }
   }

    IsoGridSquare getOtherSideOfDoor(IsoGameCharacter var1) {
      if (this.north) {
         return var1.getCurrentSquare().getRoom() == this.square.getRoom()
            ? IsoWorld.instance.CurrentCell.getGridSquare(this.square.getX(), this.square.getY() - 1, this.square.getZ())
            : IsoWorld.instance.CurrentCell.getGridSquare(this.square.getX(), this.square.getY(), this.square.getZ());
      } else {
         return var1.getCurrentSquare().getRoom() == this.square.getRoom()
            ? IsoWorld.instance.CurrentCell.getGridSquare(this.square.getX() - 1, this.square.getY(), this.square.getZ())
            : IsoWorld.instance.CurrentCell.getGridSquare(this.square.getX(), this.square.getY(), this.square.getZ());
      }
   }

    void ToggleDoorActual(IsoGameCharacter var1) {
      if (this.isBarricaded()) {
         if (var1 != nullptr) {
            this.playDoorSound(var1.getEmitter(), "Blocked");
            var1.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBarricaded"), 255, 255, 255, 256.0F);
            this.setRenderEffect(RenderEffectType.Hit_Door, true);
         }
      } else if (this.isLockedByKey()
         && dynamic_cast<IsoPlayer*>(var1) != nullptr
         && var1.getCurrentSquare().Is(IsoFlagType.exterior)
         && var1.getInventory().haveThisKeyId(this.getKeyId()) == nullptr) {
         this.playDoorSound(var1.getEmitter(), "Locked");
         this.setRenderEffect(RenderEffectType.Hit_Door, true);
      } else {
         if (this.isLockedByKey() && dynamic_cast<IsoPlayer*>(var1) != nullptr && var1.getInventory().haveThisKeyId(this.getKeyId()) != nullptr) {
            this.playDoorSound(var1.getEmitter(), "Unlock");
            this.setIsLocked(false);
            this.setLockedByKey(false);
         }

         this.DirtySlice();
         this.square.InvalidateSpecialObjectPaths();
         if (this.Locked && dynamic_cast<IsoPlayer*>(var1) != nullptr && var1.getCurrentSquare().Is(IsoFlagType.exterior) && !this.open) {
            this.playDoorSound(var1.getEmitter(), "Locked");
            this.setRenderEffect(RenderEffectType.Hit_Door, true);
         } else {
            if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
            }

            for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
               LosUtil.cachecleared[var2] = true;
            }

            IsoGridSquare.setRecalcLightTime(-1);
            GameTime.instance.lightSourceUpdate = 100.0F;
            if (this.getSprite().getProperties().Is("DoubleDoor")) {
               if (IsoDoor.isDoubleDoorObstructed(this)) {
                  if (var1 != nullptr) {
                     this.playDoorSound(var1.getEmitter(), "Blocked");
                     var1.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBlocked"), 255, 255, 255, 256.0F);
                  }
               } else {
    bool var3 = this.open;
                  IsoDoor.toggleDoubleDoor(this, true);
                  if (var3 != this.open) {
                     this.playDoorSound(var1.getEmitter(), this.open ? "Open" : "Close");
                  }
               }
            } else if (this.isObstructed()) {
               if (var1 != nullptr) {
                  this.playDoorSound(var1.getEmitter(), "Blocked");
                  var1.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBlocked"), 255, 255, 255, 256.0F);
               }
            } else {
               this.sprite = this.closedSprite;
               this.open = !this.open;
               this.setLockedByKey(false);
               if (this.open) {
                  this.playDoorSound(var1.getEmitter(), "Open");
                  this.sprite = this.openSprite;
               } else {
                  this.playDoorSound(var1.getEmitter(), "Close");
               }

               this.square.RecalcProperties();
               this.syncIsoObject(false, (byte)(this.open ? 1 : 0), nullptr, nullptr);
               LuaEventManager.triggerEvent("OnContainerUpdate");
            }
         }
      }
   }

    void ToggleDoor(IsoGameCharacter var1) {
      this.ToggleDoorActual(var1);
   }

    void ToggleDoorSilent() {
      if (!this.isBarricaded()) {
         this.square.InvalidateSpecialObjectPaths();

         for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
            LosUtil.cachecleared[var1] = true;
         }

         IsoGridSquare.setRecalcLightTime(-1);
         this.open = !this.open;
         this.sprite = this.closedSprite;
         if (this.open) {
            this.sprite = this.openSprite;
         }
      }
   }

    bool isObstructed() {
      return IsoDoor.isDoorObstructed(this);
   }

    bool haveSheetRope() {
      return IsoWindow.isTopOfSheetRopeHere(this.square, this.north);
   }

    int countAddSheetRope() {
      return !this.isHoppable() && !this.isWindow() ? 0 : IsoWindow.countAddSheetRope(this.square, this.north);
   }

    bool canAddSheetRope() {
      return !this.isHoppable() && !this.isWindow() ? false : IsoWindow.canAddSheetRope(this.square, this.north);
   }

    bool addSheetRope(IsoPlayer var1, const std::string& var2) {
      return !this.canAddSheetRope() ? false : IsoWindow.addSheetRope(var1, this.square, this.north, var2);
   }

    bool removeSheetRope(IsoPlayer var1) {
      return this.haveSheetRope() ? IsoWindow.removeSheetRope(var1, this.square, this.north) : false;
   }

    void createLightSource(int var1, int var2, int var3, int var4, int var5, const std::string& var6, InventoryItem var7, IsoGameCharacter var8) {
      this.setLightSourceXOffset(var2);
      this.setLightSourceYOffset(var3);
      this.setLightSourceRadius(var1);
      this.setLightSourceFuel(var6);
      if (var7 != nullptr) {
         if (!(dynamic_cast<DrainableComboItem*>(var7) != nullptr)) {
            this.setLifeLeft(1.0F);
            this.setHaveFuel(true);
         } else {
            this.setLifeLeft(((DrainableComboItem)var7).getUsedDelta());
            this.setLifeDelta(((DrainableComboItem)var7).getUseDelta());
            this.setHaveFuel(!"Base.Torch" == var7.getFullType()) || ((DrainableComboItem)var7).getUsedDelta() > 0.0F);
         }

         var8.removeFromHands(var7);
    IsoWorldInventoryObject var9 = var7.getWorldItem();
         if (var9 != nullptr) {
            if (var9.getSquare() != nullptr) {
               var9.getSquare().transmitRemoveItemFromSquare(var9);
               LuaEventManager.triggerEvent("OnContainerUpdate");
            }
         } else if (var7.getContainer() != nullptr) {
            var7.getContainer().Remove(var7);
         }
      }

      this.setLightSourceOn(this.haveFuel);
      if (this.lightSource != nullptr) {
         this.lightSource.setActive(this.isLightSourceOn());
      }
   }

    InventoryItem insertNewFuel(InventoryItem var1, IsoGameCharacter var2) {
      if (var1 != nullptr) {
    InventoryItem var3 = this.removeCurrentFuel(var2);
         if (var2 != nullptr) {
            var2.removeFromHands(var1);
            var2.getInventory().Remove(var1);
         }

         if (dynamic_cast<DrainableComboItem*>(var1) != nullptr) {
            this.setLifeLeft(((DrainableComboItem)var1).getUsedDelta());
            this.setLifeDelta(((DrainableComboItem)var1).getUseDelta());
         } else {
            this.setLifeLeft(1.0F);
         }

         this.setHaveFuel(true);
         this.toggleLightSource(true);
    return var3;
      } else {
    return nullptr;
      }
   }

    InventoryItem removeCurrentFuel(IsoGameCharacter var1) {
      if (this.haveFuel()) {
    InventoryItem var2 = InventoryItemFactory.CreateItem(this.getLightSourceFuel());
         if (dynamic_cast<DrainableComboItem*>(var2) != nullptr) {
            ((DrainableComboItem)var2).setUsedDelta(this.getLifeLeft());
         }

         if (var1 != nullptr) {
            var1.getInventory().AddItem(var2);
         }

         this.setLifeLeft(0.0F);
         this.setLifeDelta(-1.0F);
         this.toggleLightSource(false);
         this.setHaveFuel(false);
    return var2;
      } else {
    return nullptr;
      }
   }

    int calcLightSourceX() {
    int var1 = (int)this.getX();
    int var2 = (int)this.getY();
      if (this.lightSourceXOffset != 0) {
         for (int var3 = 1; var3 <= Math.abs(this.lightSourceXOffset); var3++) {
    int var4 = this.lightSourceXOffset > 0 ? 1 : -1;
            TestResults var5 = LosUtil.lineClear(
               this.getCell(), (int)this.getX(), (int)this.getY(), (int)this.getZ(), var1 + var4, var2, (int)this.getZ(), false
            );
            if (var5 == TestResults.Blocked || var5 == TestResults.ClearThroughWindow) {
               break;
            }

            var1 += var4;
         }
      }

    return var1;
   }

    int calcLightSourceY() {
    int var1 = (int)this.getX();
    int var2 = (int)this.getY();
      if (this.lightSourceYOffset != 0) {
         for (int var3 = 1; var3 <= Math.abs(this.lightSourceYOffset); var3++) {
    int var4 = this.lightSourceYOffset > 0 ? 1 : -1;
            TestResults var5 = LosUtil.lineClear(
               this.getCell(), (int)this.getX(), (int)this.getY(), (int)this.getZ(), var1, var2 + var4, (int)this.getZ(), false
            );
            if (var5 == TestResults.Blocked || var5 == TestResults.ClearThroughWindow) {
               break;
            }

            var2 += var4;
         }
      }

    return var2;
   }

    void update() {
      if (this.getObjectIndex() != -1) {
         if (!GameServer.bServer) {
            if (this.lightSource != nullptr && !this.lightSource.isInBounds()) {
               this.lightSource = nullptr;
            }

            if (this.lightSourceFuel != nullptr && !this.lightSourceFuel.empty() && this.lightSource == nullptr && this.square != nullptr) {
    uint8_t var1 = 0;
    int var2 = this.calcLightSourceX();
    int var3 = this.calcLightSourceY();
               if (IsoWorld.instance.CurrentCell.isInChunkMap(var2, var3)) {
    int var4 = this.getLightSourceLife();
                  this.setLightSource(std::make_shared<IsoLightSource>(var2, var3, (int)this.getZ() + var1, 1.0F, 1.0F, 1.0F, this.lightSourceRadius, var4 > 0 ? var4 : -1));
                  this.lightSource.setActive(this.isLightSourceOn());
                  IsoWorld.instance.getCell().getLamppostPositions().push_back(this.getLightSource());
               }
            }

            if (this.lightSource != nullptr && this.lightSource.isActive()) {
    uint8_t var5 = 0;
    int var7 = this.calcLightSourceX();
    int var9 = this.calcLightSourceY();
               if (var7 != this.lightSource.x || var9 != this.lightSource.y) {
                  this.getCell().removeLamppost(this.lightSource);
    int var11 = this.getLightSourceLife();
                  this.setLightSource(std::make_shared<IsoLightSource>(var7, var9, (int)this.getZ() + var5, 1.0F, 1.0F, 1.0F, this.lightSourceRadius, var11 > 0 ? var11 : -1));
                  this.lightSource.setActive(this.isLightSourceOn());
                  IsoWorld.instance.getCell().getLamppostPositions().push_back(this.getLightSource());
               }
            }
         }

         if (this.getLifeLeft() > -1.0F) {
    float var6 = (float)GameTime.getInstance().getWorldAgeHours();
            if (this.lastUpdateHours == -1.0F) {
               this.lastUpdateHours = var6;
            } else if (this.lastUpdateHours > var6) {
               this.lastUpdateHours = var6;
            }

    float var8 = var6 - this.lastUpdateHours;
            this.lastUpdateHours = var6;
            if (this.isLightSourceOn()) {
               this.updateAccumulator += var8;
    int var10 = (int)Math.floor(this.updateAccumulator / 0.004166667F);
               if (var10 > 0) {
                  this.updateAccumulator -= 0.004166667F * var10;
                  this.setLifeLeft(this.getLifeLeft() - this.getLifeDelta() * var10);
                  if (this.getLifeLeft() <= 0.0F) {
                     this.setLifeLeft(0.0F);
                     this.toggleLightSource(false);
                  }
               }
            } else {
               this.updateAccumulator = 0.0F;
            }
         }
      }
   }

    void Damage(int var1) {
      if (this.isThumpable()) {
         this.DirtySlice();
         this.Health -= var1;
      }
   }

    void destroy() {
      if (!this.destroyed) {
         if (this.getObjectIndex() != -1) {
            if (GameClient.bClient) {
               GameClient.instance
                  .sendClientCommandV(
                     nullptr,
                     "object",
                     "OnDestroyIsoThumpable",
                     new Object[]{"x", this.square.getX(), "y", this.square.getY(), "z", this.square.getZ(), "index", this.getObjectIndex()}
                  );
            }

            LuaEventManager.triggerEvent("OnDestroyIsoThumpable", this, nullptr);
            this.Health = 0;
            this.destroyed = true;
            if (this.getObjectIndex() != -1) {
               this.square.transmitRemoveItemFromSquare(this);
            }
         }
      }
   }

    IsoBarricade getBarricadeOnSameSquare() {
      return IsoBarricade.GetBarricadeOnSquare(this.square, this.north ? IsoDirections.N : IsoDirections.W);
   }

    IsoBarricade getBarricadeOnOppositeSquare() {
      return IsoBarricade.GetBarricadeOnSquare(this.getOppositeSquare(), this.north ? IsoDirections.S : IsoDirections.E);
   }

    bool isBarricaded() {
    IsoBarricade var1 = this.getBarricadeOnSameSquare();
      if (var1 == nullptr) {
         var1 = this.getBarricadeOnOppositeSquare();
      }

      return var1 != nullptr;
   }

    bool isBarricadeAllowed() {
      return this.canBarricade;
   }

    IsoBarricade getBarricadeForCharacter(IsoGameCharacter var1) {
      return IsoBarricade.GetBarricadeForCharacter(this, var1);
   }

    IsoBarricade getBarricadeOppositeCharacter(IsoGameCharacter var1) {
      return IsoBarricade.GetBarricadeOppositeCharacter(this, var1);
   }

    void setIsDoor(bool var1) {
      this.isDoor = var1;
   }

    KahluaTable getTable() {
      return this.table;
   }

    void setTable(KahluaTable var1) {
      this.table = var1;
   }

    bool canBePlastered() {
      return this.canBePlastered;
   }

    void setCanBePlastered(bool var1) {
      this.canBePlastered = var1;
   }

    bool isPaintable() {
      return this.paintable;
   }

    void setPaintable(bool var1) {
      this.paintable = var1;
   }

    bool isLocked() {
      return this.Locked;
   }

    void setIsLocked(bool var1) {
      this.Locked = var1;
   }

    bool isThumpable() {
      return this.isBarricaded() ? true : this.isThumpable;
   }

    void setIsThumpable(bool var1) {
      this.isThumpable = var1;
   }

    void setIsHoppable(bool var1) {
      this.setHoppable(var1);
   }

    IsoSprite getOpenSprite() {
      return this.openSprite;
   }

    bool isHoppable() {
      if (this.isDoor() && !this.IsOpen() && this.closedSprite != nullptr) {
    PropertyContainer var1 = this.closedSprite.getProperties();
         return var1.Is(IsoFlagType.HoppableN) || var1.Is(IsoFlagType.HoppableW);
      } else {
         return this.sprite == nullptr || !this.sprite.getProperties().Is(IsoFlagType.HoppableN) && !this.sprite.getProperties().Is(IsoFlagType.HoppableW)
            ? this.isHoppable
            : true;
      }
   }

    void setHoppable(bool var1) {
      this.isHoppable = var1;
   }

    int getLightSourceRadius() {
      return this.lightSourceRadius;
   }

    void setLightSourceRadius(int var1) {
      this.lightSourceRadius = var1;
   }

    int getLightSourceXOffset() {
      return this.lightSourceXOffset;
   }

    void setLightSourceXOffset(int var1) {
      this.lightSourceXOffset = var1;
   }

    int getLightSourceYOffset() {
      return this.lightSourceYOffset;
   }

    void setLightSourceYOffset(int var1) {
      this.lightSourceYOffset = var1;
   }

    int getLightSourceLife() {
      return this.lightSourceLife;
   }

    void setLightSourceLife(int var1) {
      this.lightSourceLife = var1;
   }

    bool isLightSourceOn() {
      return this.lightSourceOn;
   }

    void setLightSourceOn(bool var1) {
      this.lightSourceOn = var1;
   }

    IsoLightSource getLightSource() {
      return this.lightSource;
   }

    void setLightSource(IsoLightSource var1) {
      this.lightSource = var1;
   }

    void toggleLightSource(bool var1) {
      this.setLightSourceOn(var1);
      if (this.lightSource != nullptr) {
         this.getLightSource().setActive(var1);
         IsoGridSquare.setRecalcLightTime(-1);
         GameTime.instance.lightSourceUpdate = 100.0F;
      }
   }

    std::string getLightSourceFuel() {
      return this.lightSourceFuel;
   }

    void setLightSourceFuel(const std::string& var1) {
      if (var1 != nullptr && var1.empty()) {
         var1 = nullptr;
      }

      this.lightSourceFuel = var1;
   }

    float getLifeLeft() {
      return this.lifeLeft;
   }

    void setLifeLeft(float var1) {
      this.lifeLeft = var1;
   }

    float getLifeDelta() {
      return this.lifeDelta;
   }

    void setLifeDelta(float var1) {
      this.lifeDelta = var1;
   }

    bool haveFuel() {
      return this.haveFuel;
   }

    void setHaveFuel(bool var1) {
      this.haveFuel = var1;
   }

    void syncIsoObjectSend(ByteBufferWriter var1) {
      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
    uint8_t var2 = (byte)this.square.getObjects().indexOf(this);
      var1.putByte(var2);
      var1.putByte((byte)1);
      var1.putByte((byte)0);
      var1.putBoolean(this.open);
      var1.putBoolean(this.Locked);
      var1.putBoolean(this.lockedByKey);
   }

    void syncIsoObject(bool var1, uint8_t var2, UdpConnection var3, ByteBuffer var4) {
      if (this.square == nullptr) {
         System.out.println("ERROR: " + this.getClass().getSimpleName() + " square is nullptr");
      } else if (this.getObjectIndex() == -1) {
         System.out
            .println(
               "ERROR: " + this.getClass().getSimpleName() + " not found on square " + this.square.getX() + "," + this.square.getY() + "," + this.square.getZ()
            );
      } else if (this.isDoor()) {
    bool var5 = var4 != nullptr && var4.get() == 1;
    bool var6 = var4 != nullptr && var4.get() == 1;
    bool var7 = var4 != nullptr && var4.get() == 1;
    short var8 = -1;
         if ((GameServer.bServer || GameClient.bClient) && var4 != nullptr) {
            var8 = var4.getShort();
         }

         if (GameClient.bClient && !var1) {
            var8 = IsoPlayer.getInstance().getOnlineID();
    ByteBufferWriter var16 = GameClient.connection.startPacket();
            PacketType.SyncIsoObject.doPacket(var16);
            this.syncIsoObjectSend(var16);
            var16.putShort(var8);
            PacketType.SyncIsoObject.send(GameClient.connection);
         } else if (GameServer.bServer && !var1) {
            for (UdpConnection var17 : GameServer.udpEngine.connections) {
    ByteBufferWriter var18 = var17.startPacket();
               PacketType.SyncIsoObject.doPacket(var18);
               this.syncIsoObjectSend(var18);
               var18.putShort(var8);
               PacketType.SyncIsoObject.send(var17);
            }
         } else if (var1) {
            if (GameClient.bClient && var8 != -1) {
    IsoPlayer var9 = (IsoPlayer)GameClient.IDToPlayerMap.get(var8);
               if (var9 != nullptr) {
                  var9.networkAI.setNoCollision(1000L);
               }
            }

            if (IsoDoor.getDoubleDoorIndex(this) != -1) {
               if (var5 != this.open) {
                  IsoDoor.toggleDoubleDoor(this, false);
               }
            } else if (var5) {
               this.open = true;
               this.sprite = this.openSprite;
            } else {
               this.open = false;
               this.sprite = this.closedSprite;
            }

            this.Locked = var6;
            this.lockedByKey = var7;
            if (GameServer.bServer) {
               for (UdpConnection var10 : GameServer.udpEngine.connections) {
                  if (var3 != nullptr && var10.getConnectedGUID() != var3.getConnectedGUID()) {
    ByteBufferWriter var11 = var10.startPacket();
                     PacketType.SyncIsoObject.doPacket(var11);
                     this.syncIsoObjectSend(var11);
                     var11.putShort(var8);
                     PacketType.SyncIsoObject.send(var10);
                  }
               }
            }

            this.square.InvalidateSpecialObjectPaths();
            this.square.RecalcProperties();
            this.square.RecalcAllWithNeighbours(true);

            for (int var14 = 0; var14 < IsoPlayer.numPlayers; var14++) {
               LosUtil.cachecleared[var14] = true;
            }

            IsoGridSquare.setRecalcLightTime(-1);
            GameTime.instance.lightSourceUpdate = 100.0F;
            LuaEventManager.triggerEvent("OnContainerUpdate");
         }
      }
   }

    void addToWorld() {
      super.addToWorld();
      this.getCell().addToProcessIsoObject(this);
   }

    void removeFromWorld() {
      if (this.lightSource != nullptr) {
         IsoWorld.instance.CurrentCell.removeLamppost(this.lightSource);
      }

      super.removeFromWorld();
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      super.saveChange(var1, var2, var3);
      if ("lightSource" == var1)) {
         var3.put((byte)(this.lightSourceOn ? 1 : 0));
         var3.put((byte)(this.haveFuel ? 1 : 0));
         var3.putFloat(this.lifeLeft);
         var3.putFloat(this.lifeDelta);
      } else if ("paintable" == var1)) {
         var3.put((byte)(this.isPaintable() ? 1 : 0));
      }
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      super.loadChange(var1, var2);
      if ("lightSource" == var1)) {
    bool var3 = var2.get() == 1;
         this.haveFuel = var2.get() == 1;
         this.lifeLeft = var2.getFloat();
         this.lifeDelta = var2.getFloat();
         if (var3 != this.lightSourceOn) {
            this.toggleLightSource(var3);
         }
      } else if ("paintable" == var1)) {
         this.setPaintable(var2.get() == 1);
      }
   }

    IsoCurtain HasCurtains() {
    IsoGridSquare var1 = this.getOppositeSquare();
      if (var1 != nullptr) {
    IsoCurtain var2 = var1.getCurtain(this.getNorth() ? IsoObjectType.curtainS : IsoObjectType.curtainE);
         if (var2 != nullptr) {
    return var2;
         }
      }

      return this.getSquare().getCurtain(this.getNorth() ? IsoObjectType.curtainN : IsoObjectType.curtainW);
   }

    IsoGridSquare getInsideSquare() {
      return this.north
         ? this.square.getCell().getGridSquare(this.square.getX(), this.square.getY() - 1, this.square.getZ())
         : this.square.getCell().getGridSquare(this.square.getX() - 1, this.square.getY(), this.square.getZ());
   }

    IsoGridSquare getOppositeSquare() {
      return this.getInsideSquare();
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool isAdjacentToSquare(IsoGridSquare var1) {
    IsoGridSquare var2 = this.getSquare();
      if (var2 != nullptr && var1 != nullptr) {
    bool var3 = !this.IsOpen();
    IsoGridSquare var4 = var2.getAdjacentSquare(IsoDirections.NW);
    IsoGridSquare var5 = var2.getAdjacentSquare(IsoDirections.N);
    IsoGridSquare var6 = var2.getAdjacentSquare(IsoDirections.NE);
    IsoGridSquare var7 = var2.getAdjacentSquare(IsoDirections.W);
    IsoGridSquare var8 = var2.getAdjacentSquare(IsoDirections.E);
    IsoGridSquare var9 = var2.getAdjacentSquare(IsoDirections.SW);
    IsoGridSquare var10 = var2.getAdjacentSquare(IsoDirections.S);
    IsoGridSquare var11 = var2.getAdjacentSquare(IsoDirections.SE);
         switch (1.$SwitchMap$zombie$iso$IsoDirections[this.getSpriteEdge(false).ordinal()]) {
            case 1:
               if (var1 == var4) {
                  if (!var4.isWallTo(var5)
                     && !var4.isWindowTo(var5)
                     && !var4.hasDoorOnEdge(IsoDirections.E, false)
                     && !var5.hasDoorOnEdge(IsoDirections.W, false)) {
                     if (var5.hasDoorOnEdge(IsoDirections.S, false)) {
    return false;
                     }

                     if (this.IsOpen() && var2.hasClosedDoorOnEdge(IsoDirections.N)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var5) {
                  if (var5.hasDoorOnEdge(IsoDirections.S, false)) {
    return false;
                  }

                  if (this.IsOpen() && var2.hasClosedDoorOnEdge(IsoDirections.N)) {
    return false;
                  }

    return true;
               }

               if (var1 == var6) {
                  if (!var6.isWallTo(var5)
                     && !var6.isWindowTo(var5)
                     && !var6.hasDoorOnEdge(IsoDirections.W, false)
                     && !var5.hasDoorOnEdge(IsoDirections.E, false)) {
                     if (var5.hasDoorOnEdge(IsoDirections.S, false)) {
    return false;
                     }

                     if (this.IsOpen() && var2.hasClosedDoorOnEdge(IsoDirections.N)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var7) {
                  if (!var7.isWallTo(var2)
                     && !var7.isWindowTo(var2)
                     && !var7.hasDoorOnEdge(IsoDirections.E, false)
                     && !var2.hasDoorOnEdge(IsoDirections.W, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.N)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var2) {
                  if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.N)) {
    return false;
                  }

    return true;
               }

               if (var1 == var8) {
                  if (!var8.isWallTo(var2)
                     && !var8.isWindowTo(var2)
                     && !var8.hasDoorOnEdge(IsoDirections.W, false)
                     && !var2.hasDoorOnEdge(IsoDirections.E, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.N)) {
    return false;
                     }

    return true;
                  }

    return false;
               }
               break;
            case 2:
               if (var1 == var7) {
                  if (!var7.isWallTo(var2)
                     && !var7.isWindowTo(var2)
                     && !var7.hasDoorOnEdge(IsoDirections.E, false)
                     && !var2.hasDoorOnEdge(IsoDirections.W, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.S)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var2) {
                  if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.S)) {
    return false;
                  }

    return true;
               }

               if (var1 == var8) {
                  if (!var8.isWallTo(var2)
                     && !var8.isWindowTo(var2)
                     && !var8.hasDoorOnEdge(IsoDirections.W, false)
                     && !var2.hasDoorOnEdge(IsoDirections.E, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.S)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var9) {
                  if (!var9.isWallTo(var10)
                     && !var9.isWindowTo(var10)
                     && !var9.hasDoorOnEdge(IsoDirections.E, false)
                     && !var10.hasDoorOnEdge(IsoDirections.W, false)) {
                     if (var10.hasDoorOnEdge(IsoDirections.N, false)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var10) {
                  if (var10.hasDoorOnEdge(IsoDirections.N, false)) {
    return false;
                  }

    return true;
               }

               if (var1 == var11) {
                  if (!var11.isWallTo(var10)
                     && !var11.isWindowTo(var10)
                     && !var11.hasDoorOnEdge(IsoDirections.W, false)
                     && !var10.hasDoorOnEdge(IsoDirections.E, false)) {
                     if (var10.hasDoorOnEdge(IsoDirections.N, false)) {
    return false;
                     }

    return true;
                  }

    return false;
               }
               break;
            case 3:
               if (var1 == var4) {
                  if (!var4.isWallTo(var7)
                     && !var4.isWindowTo(var7)
                     && !var4.hasDoorOnEdge(IsoDirections.S, false)
                     && !var7.hasDoorOnEdge(IsoDirections.N, false)) {
                     if (var3 && var7.hasDoorOnEdge(IsoDirections.E, false)) {
    return false;
                     }

                     if (this.IsOpen() && var2.hasClosedDoorOnEdge(IsoDirections.W)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var7) {
                  if (var3 && var7.hasDoorOnEdge(IsoDirections.E, false)) {
    return false;
                  }

                  if (this.IsOpen() && var2.hasClosedDoorOnEdge(IsoDirections.W)) {
    return false;
                  }

    return true;
               }

               if (var1 == var9) {
                  if (!var9.isWallTo(var7)
                     && !var9.isWindowTo(var7)
                     && !var9.hasDoorOnEdge(IsoDirections.N, false)
                     && !var7.hasDoorOnEdge(IsoDirections.S, false)) {
                     if (var3 && var7.hasDoorOnEdge(IsoDirections.E, false)) {
    return false;
                     }

                     if (this.IsOpen() && var2.hasClosedDoorOnEdge(IsoDirections.W)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var5) {
                  if (!var5.isWallTo(var2)
                     && !var5.isWindowTo(var2)
                     && !var5.hasDoorOnEdge(IsoDirections.S, false)
                     && !var2.hasDoorOnEdge(IsoDirections.N, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.W)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var2) {
                  if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.W)) {
    return false;
                  }

    return true;
               }

               if (var1 == var10) {
                  if (!var10.isWallTo(var2)
                     && !var10.isWindowTo(var2)
                     && !var10.hasDoorOnEdge(IsoDirections.N, false)
                     && !var2.hasDoorOnEdge(IsoDirections.S, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.W)) {
    return false;
                     }

    return true;
                  }

    return false;
               }
               break;
            case 4:
               if (var1 == var5) {
                  if (!var5.isWallTo(var2)
                     && !var5.isWindowTo(var2)
                     && !var5.hasDoorOnEdge(IsoDirections.S, false)
                     && !var2.hasDoorOnEdge(IsoDirections.N, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.E)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var2) {
                  if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.E)) {
    return false;
                  }

    return true;
               }

               if (var1 == var10) {
                  if (!var10.isWallTo(var2)
                     && !var10.isWindowTo(var2)
                     && !var10.hasDoorOnEdge(IsoDirections.N, false)
                     && !var2.hasDoorOnEdge(IsoDirections.S, false)) {
                     if (var3 && var2.hasOpenDoorOnEdge(IsoDirections.E)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var6) {
                  if (!var6.isWallTo(var8)
                     && !var6.isWindowTo(var8)
                     && !var6.hasDoorOnEdge(IsoDirections.S, false)
                     && !var7.hasDoorOnEdge(IsoDirections.N, false)) {
                     if (var8.hasDoorOnEdge(IsoDirections.W, false)) {
    return false;
                     }

    return true;
                  }

    return false;
               }

               if (var1 == var8) {
                  if (var8.hasDoorOnEdge(IsoDirections.W, false)) {
    return false;
                  }

    return true;
               }

               if (var1 == var11) {
                  if (!var11.isWallTo(var8)
                     && !var11.isWindowTo(var8)
                     && !var11.hasDoorOnEdge(IsoDirections.N, false)
                     && !var8.hasDoorOnEdge(IsoDirections.S, false)) {
                     if (var8.hasDoorOnEdge(IsoDirections.E, false)) {
    return false;
                     }

    return true;
                  }

    return false;
               }
               break;
            default:
    return false;
         }

    return false;
      } else {
    return false;
      }
   }

    IsoGridSquare getAddSheetSquare(IsoGameCharacter var1) {
      if (var1 != nullptr && var1.getCurrentSquare() != nullptr) {
    IsoGridSquare var2 = var1.getCurrentSquare();
    IsoGridSquare var3 = this.getSquare();
         if (this.north) {
            return var2.getY() < var3.getY() ? this.getCell().getGridSquare(var3.x, var3.y - 1, var3.z) : var3;
         } else {
            return var2.getX() < var3.getX() ? this.getCell().getGridSquare(var3.x - 1, var3.y, var3.z) : var3;
         }
      } else {
    return nullptr;
      }
   }

    void addSheet(IsoGameCharacter var1) {
    IsoGridSquare var2 = this.getIndoorSquare();
    IsoObjectType var3;
      if (this.north) {
         var3 = IsoObjectType.curtainN;
         if (var2 != this.square) {
            var3 = IsoObjectType.curtainS;
         }
      } else {
         var3 = IsoObjectType.curtainW;
         if (var2 != this.square) {
            var3 = IsoObjectType.curtainE;
         }
      }

      if (var1 != nullptr) {
         if (this.north) {
            if (var1.getY() < this.getY()) {
               var2 = this.getCell().getGridSquare(this.getX(), this.getY() - 1.0F, this.getZ());
               var3 = IsoObjectType.curtainS;
            } else {
               var2 = this.getSquare();
               var3 = IsoObjectType.curtainN;
            }
         } else if (var1.getX() < this.getX()) {
            var2 = this.getCell().getGridSquare(this.getX() - 1.0F, this.getY(), this.getZ());
            var3 = IsoObjectType.curtainE;
         } else {
            var2 = this.getSquare();
            var3 = IsoObjectType.curtainW;
         }
      }

      if (var2 != nullptr) {
         if (var2.getCurtain(var3) == nullptr) {
            if (var2 != nullptr) {
    int var4 = 16;
               if (var3 == IsoObjectType.curtainE) {
                  var4++;
               }

               if (var3 == IsoObjectType.curtainS) {
                  var4 += 3;
               }

               if (var3 == IsoObjectType.curtainN) {
                  var4 += 2;
               }

               var4 += 4;
    IsoCurtain var5 = std::make_shared<IsoCurtain>(this.getCell(), var2, "fixtures_windows_curtains_01_" + var4, this.north);
               var2.AddSpecialTileObject(var5);
               if (GameServer.bServer) {
                  var5.transmitCompleteItemToClients();
                  var1.sendObjectChange("removeOneOf", new Object[]{"type", "Sheet"});
               } else {
                  var1.getInventory().RemoveOneOf("Sheet");
               }
            }
         }
      }
   }

    IsoGridSquare getIndoorSquare() {
      if (this.square.getRoom() != nullptr) {
         return this.square;
      } else {
    IsoGridSquare var1;
         if (this.north) {
            var1 = IsoWorld.instance.CurrentCell.getGridSquare(this.square.getX(), this.square.getY() - 1, this.square.getZ());
         } else {
            var1 = IsoWorld.instance.CurrentCell.getGridSquare(this.square.getX() - 1, this.square.getY(), this.square.getZ());
         }

         if (var1 == nullptr || var1.getFloor() == nullptr) {
            return this.square;
         } else if (var1.getRoom() != nullptr) {
    return var1;
         } else if (this.square.getFloor() == nullptr) {
    return var1;
         } else {
    std::string var2 = var1.getFloor().getSprite().getName();
            return var2 != nullptr && var2.startsWith("carpentry_02_") ? var1 : this.square;
         }
      }
   }

    int getKeyId() {
      return this.keyId;
   }

    void setKeyId(int var1, bool var2) {
      if (var2 && this.keyId != var1 && GameClient.bClient) {
         this.keyId = var1;
         this.syncIsoThumpable();
      } else {
         this.keyId = var1;
      }
   }

    void setKeyId(int var1) {
      this.setKeyId(var1, true);
   }

    bool isLockedByKey() {
      return this.lockedByKey;
   }

    void setLockedByKey(bool var1) {
    bool var2 = var1 != this.lockedByKey;
      this.lockedByKey = var1;
      this.setIsLocked(var1);
      if (!GameServer.bServer && var2) {
         if (var1) {
            this.syncIsoObject(false, (byte)3, nullptr, nullptr);
         } else {
            this.syncIsoObject(false, (byte)4, nullptr, nullptr);
         }
      }
   }

    bool isLockedByPadlock() {
      return this.lockedByPadlock;
   }

    void syncIsoThumpable() {
    ByteBufferWriter var1 = GameClient.connection.startPacket();
      PacketType.SyncThumpable.doPacket(var1);
      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
    uint8_t var2 = (byte)this.square.getObjects().indexOf(this);
      if (var2 == -1) {
         System.out.println("ERROR: Thumpable door not found on square " + this.square.getX() + ", " + this.square.getY() + ", " + this.square.getZ());
         GameClient.connection.cancelPacket();
      } else {
         var1.putByte(var2);
         var1.putInt(this.getLockedByCode());
         var1.putByte((byte)(this.lockedByPadlock ? 1 : 0));
         var1.putInt(this.getKeyId());
         PacketType.SyncThumpable.send(GameClient.connection);
      }
   }

    void setLockedByPadlock(bool var1) {
      if (this.lockedByPadlock != var1 && GameClient.bClient) {
         this.lockedByPadlock = var1;
         this.syncIsoThumpable();
      } else {
         this.lockedByPadlock = var1;
      }
   }

    bool canBeLockByPadlock() {
      return this.canBeLockByPadlock;
   }

    void setCanBeLockByPadlock(bool var1) {
      this.canBeLockByPadlock = var1;
   }

    int getLockedByCode() {
      return this.lockedByCode;
   }

    void setLockedByCode(int var1) {
      if (this.lockedByCode != var1 && GameClient.bClient) {
         this.lockedByCode = var1;
         this.syncIsoThumpable();
      } else {
         this.lockedByCode = var1;
      }
   }

    bool isLockedToCharacter(IsoGameCharacter var1) {
      if (GameClient.bClient && dynamic_cast<IsoPlayer*>(var1) != nullptr && !((IsoPlayer)var1).accessLevel == "")) {
    return false;
      } else {
         return this.getLockedByCode() > 0
            ? true
            : this.isLockedByPadlock() && (var1.getInventory() == nullptr || var1.getInventory().haveThisKeyId(this.getKeyId()) == nullptr);
      }
   }

    bool canClimbOver(IsoGameCharacter var1) {
      if (this.square == nullptr) {
    return false;
      } else {
         return !this.isHoppable() ? false : var1 == nullptr || IsoWindow.canClimbThroughHelper(var1, this.getSquare(), this.getOppositeSquare(), this.north);
      }
   }

    bool canClimbThrough(IsoGameCharacter var1) {
      if (this.square == nullptr) {
    return false;
      } else if (!this.isWindow()) {
    return false;
      } else {
         return this.isBarricaded() ? false : var1 == nullptr || IsoWindow.canClimbThroughHelper(var1, this.getSquare(), this.getOppositeSquare(), this.north);
      }
   }

    std::string getThumpSound() {
      return this.thumpSound;
   }

    void setThumpSound(const std::string& var1) {
      this.thumpSound = var1;
   }

    IsoObject getRenderEffectMaster() {
    int var1 = IsoDoor.getDoubleDoorIndex(this);
      if (var1 != -1) {
    IsoObject var2 = nullptr;
         if (var1 == 2) {
            var2 = IsoDoor.getDoubleDoorObject(this, 1);
         } else if (var1 == 3) {
            var2 = IsoDoor.getDoubleDoorObject(this, 4);
         }

         if (var2 != nullptr) {
    return var2;
         }
      } else {
    IsoObject var3 = IsoDoor.getGarageDoorFirst(this);
         if (var3 != nullptr) {
    return var3;
         }
      }

    return this;
   }

    IsoDirections getSpriteEdge(bool var1) {
      if (!this.isDoor() && !this.isWindow()) {
    return nullptr;
      } else if (this.open && !var1) {
    PropertyContainer var2 = this.getProperties();
         if (var2 != nullptr && var2.Is(IsoFlagType.attachedE)) {
            return IsoDirections.E;
         } else if (var2 != nullptr && var2.Is(IsoFlagType.attachedS)) {
            return IsoDirections.S;
         } else {
            return this.north ? IsoDirections.W : IsoDirections.N;
         }
      } else {
         return this.north ? IsoDirections.N : IsoDirections.W;
      }
   }

    std::string getSoundPrefix() {
      if (this.closedSprite == nullptr) {
         return "WoodDoor";
      } else {
    PropertyContainer var1 = this.closedSprite.getProperties();
         return var1.Is("DoorSound") ? var1.Val("DoorSound") : "WoodDoor";
      }
   }

    void playDoorSound(BaseCharacterSoundEmitter var1, const std::string& var2) {
      var1.playSound(this.getSoundPrefix() + var2, this);
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
