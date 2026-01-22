#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/AmbientStreamManager.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/states/ThumpState.h"
#include "zombie/audio/parameters/ParameterMeleeHitSurface/Material.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoLivingCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObject/VisionResult.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/objects/IsoWindow/1.h"
#include "zombie/iso/objects/IsoWindow/WindowType.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoWindow : public IsoObject {
public:
    int Health = 75;
    int MaxHealth = 75;
    WindowType type = WindowType.SinglePane;
    IsoSprite closedSprite;
    IsoSprite smashedSprite;
    bool north = false;
    bool Locked = false;
    bool PermaLocked = false;
    bool open = false;
    IsoSprite openSprite;
    bool destroyed = false;
    bool glassRemoved = false;
    IsoSprite glassRemovedSprite;
    int OldNumPlanks;

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

    IsoGridSquare getIndoorSquare() {
      if (this.square.getRoom() != nullptr) {
         return this.square;
      } else {
         if (this.north) {
    IsoGridSquare var1 = IsoWorld.instance.CurrentCell.getGridSquare(this.square.getX(), this.square.getY() - 1, this.square.getZ());
            if (var1 != nullptr && var1.getRoom() != nullptr) {
    return var1;
            }
         } else {
    IsoGridSquare var2 = IsoWorld.instance.CurrentCell.getGridSquare(this.square.getX() - 1, this.square.getY(), this.square.getZ());
            if (var2 != nullptr && var2.getRoom() != nullptr) {
    return var2;
            }
         }

    return nullptr;
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

    void AttackObject(IsoGameCharacter var1) {
      super.AttackObject(var1);
    IsoObject var2 = this.square.getWall(this.north);
      if (var2 != nullptr) {
         var2.AttackObject(var1);
      }
   }

    IsoGridSquare getInsideSquare() {
      if (this.square == nullptr) {
    return nullptr;
      } else {
         return this.north
            ? this.getCell().getGridSquare(this.square.getX(), this.square.getY() - 1, this.square.getZ())
            : this.getCell().getGridSquare(this.square.getX() - 1, this.square.getY(), this.square.getZ());
      }
   }

    IsoGridSquare getOppositeSquare() {
      return this.getInsideSquare();
   }

    bool isExterior() {
    IsoGridSquare var1 = this.getSquare();
    IsoGridSquare var2 = this.getOppositeSquare();
    return var2 = = nullptr ? false : var1.isInARoom() != var2.isInARoom();
   }

    public IsoWindow(IsoCell var1) {
      super(var1);
   }

    std::string getObjectName() {
      return "Window";
   }

    void WeaponHit(IsoGameCharacter var1, HandWeapon var2) {
    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
      if (GameClient.bClient) {
         if (var3 != nullptr) {
            GameClient.instance.sendWeaponHit(var3, var2, this);
         }
      } else {
    Thumpable var4 = this.getThumpableFor(var1);
         if (var4 != nullptr) {
            if (dynamic_cast<IsoBarricade*>(var4) != nullptr) {
               ((IsoBarricade)var4).WeaponHit(var1, var2);
            } else {
               LuaEventManager.triggerEvent("OnWeaponHitThumpable", var1, var2, this);
               if (var2 == ((IsoLivingCharacter)var1).bareHands) {
                  if (var3 != nullptr) {
                     var3.setMeleeHitSurface(Material.Glass);
                     var3.getEmitter().playSound(var2.getDoorHitSound(), this);
                  }
               } else {
                  if (var2 != nullptr) {
                     this.Damage(var2.getDoorDamage() * 5, var1);
                  } else {
                     this.Damage(100.0F, var1);
                  }

                  this.DirtySlice();
                  if (var2 != nullptr && var2.getDoorHitSound() != nullptr) {
                     if (var3 != nullptr) {
                        var3.setMeleeHitSurface(Material.Glass);
                     }

                     var1.getEmitter().playSound(var2.getDoorHitSound(), this);
                     if (GameServer.bServer) {
                        GameServer.PlayWorldSoundServer(var1, var2.getDoorHitSound(), false, this.getSquare(), 1.0F, 20.0F, 2.0F, false);
                     }
                  }

                  WorldSoundManager.instance.addSound(var1, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, false, 0.0F, 15.0F);
                  if (!this.isDestroyed() && this.Health <= 0) {
                     this.smashWindow();
                     this.addBrokenGlass(var1);
                  }
               }
            }
         }
      }
   }

    void smashWindow(bool var1, bool var2) {
      if (!this.destroyed) {
         if (GameClient.bClient && !var1) {
            GameClient.instance.smashWindow(this, 1);
         }

         if (!var1) {
            if (GameServer.bServer) {
               GameServer.PlayWorldSoundServer("SmashWindow", false, this.square, 0.2F, 20.0F, 1.1F, true);
            } else {
               SoundManager.instance.PlayWorldSound("SmashWindow", this.square, 0.2F, 20.0F, 1.0F, true);
            }

            WorldSoundManager.instance.addSound(nullptr, this.square.getX(), this.square.getY(), this.square.getZ(), 10, 20, true, 4.0F, 15.0F);
         }

         this.destroyed = true;
         this.sprite = this.smashedSprite;
         if (this.getAttachedAnimSprite() != nullptr) {
            this.getSquare().removeBlood(false, true);
            System.out.println(this.wallBloodSplats);

            for (int var3 = 0; var3 < this.getAttachedAnimSprite().size(); var3++) {
    IsoSprite var4 = ((IsoSpriteInstance)this.getAttachedAnimSprite().get(var3)).parentSprite;
               if (var4 != nullptr && var4.getProperties().Is("AttachedToGlass")) {
                  this.getAttachedAnimSprite().remove(var3);
                  var3--;
               }
            }
         }

         this.getSquare().removeLightSwitch();
         if (var2) {
            this.handleAlarm();
         }

         if (GameServer.bServer && !var1) {
            GameServer.smashWindow(this, 1);
         }

         this.square.InvalidateSpecialObjectPaths();
      }
   }

    void smashWindow(bool var1) {
      this.smashWindow(var1, true);
   }

    void smashWindow() {
      this.smashWindow(false, true);
   }

    void addBrokenGlass(IsoMovingObject var1) {
      if (var1 != nullptr) {
         if (this.getSquare() != nullptr) {
            if (this.getNorth()) {
               this.addBrokenGlass(var1.getY() >= this.getSquare().getY());
            } else {
               this.addBrokenGlass(var1.getX() >= this.getSquare().getX());
            }
         }
      }
   }

    void addBrokenGlass(bool var1) {
    IsoGridSquare var2 = var1 ? this.getOppositeSquare() : this.getSquare();
      if (var2 != nullptr) {
         var2.addBrokenGlass();
      }
   }

    void handleAlarm() {
      if (!GameClient.bClient) {
    IsoGridSquare var1 = this.getIndoorSquare();
         if (var1 != nullptr) {
    IsoRoom var2 = var1.getRoom();
    RoomDef var3 = var2.def;
            if (var3.building.bAlarmed && !GameClient.bClient) {
               AmbientStreamManager.instance.doAlarm(var3);
            }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    public IsoWindow(IsoCell var1, IsoGridSquare var2, IsoSprite var3, bool var4) {
      var3.getProperties().UnSet(IsoFlagType.cutN);
      var3.getProperties().UnSet(IsoFlagType.cutW);
    int var5 = 0;
      if (var3.getProperties().Is("OpenTileOffset")) {
         var5 = int.parseInt(var3.getProperties().Val("OpenTileOffset"));
      }

    int var6 = 0;
      this.PermaLocked = var3.getProperties().Is("WindowLocked");
      if (var3.getProperties().Is("SmashedTileOffset")) {
         var6 = int.parseInt(var3.getProperties().Val("SmashedTileOffset"));
      }

      this.closedSprite = var3;
      if (var4) {
         this.closedSprite.getProperties().Set(IsoFlagType.cutN);
         this.closedSprite.getProperties().Set(IsoFlagType.windowN);
      } else {
         this.closedSprite.getProperties().Set(IsoFlagType.cutW);
         this.closedSprite.getProperties().Set(IsoFlagType.windowW);
      }

      this.openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, var5);
      this.smashedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3, var6);
      if (this.closedSprite.getProperties().Is("GlassRemovedOffset")) {
    int var7 = int.parseInt(this.closedSprite.getProperties().Val("GlassRemovedOffset"));
         this.glassRemovedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, this.closedSprite, var7);
      } else {
         this.glassRemovedSprite = this.smashedSprite;
      }

      if (this.smashedSprite != this.closedSprite && this.smashedSprite != nullptr) {
         this.smashedSprite.AddProperties(this.closedSprite);
         this.smashedSprite.setType(this.closedSprite.getType());
      }

      if (this.openSprite != this.closedSprite && this.openSprite != nullptr) {
         this.openSprite.AddProperties(this.closedSprite);
         this.openSprite.setType(this.closedSprite.getType());
      }

      if (this.glassRemovedSprite != this.closedSprite && this.glassRemovedSprite != nullptr) {
         this.glassRemovedSprite.AddProperties(this.closedSprite);
         this.glassRemovedSprite.setType(this.closedSprite.getType());
      }

      this.sprite = this.closedSprite;
    IsoObject var9 = var2.getWall(var4);
      if (var9 != nullptr) {
         var9.rerouteCollide = this;
      }

      this.square = var2;
      this.north = var4;
      switch (1.$SwitchMap$zombie$iso$objects$IsoWindow$WindowType[this.type.ordinal()]) {
         case 1:
            this.MaxHealth = this.Health = 50;
            break;
         case 2:
            this.MaxHealth = this.Health = 150;
      }

    uint8_t var8 = 69;
      if (SandboxOptions.instance.LockedHouses.getValue() == 1) {
         var8 = -1;
      } else if (SandboxOptions.instance.LockedHouses.getValue() == 2) {
         var8 = 5;
      } else if (SandboxOptions.instance.LockedHouses.getValue() == 3) {
         var8 = 10;
      } else if (SandboxOptions.instance.LockedHouses.getValue() == 4) {
         var8 = 50;
      } else if (SandboxOptions.instance.LockedHouses.getValue() == 5) {
         var8 = 60;
      } else if (SandboxOptions.instance.LockedHouses.getValue() == 6) {
         var8 = 70;
      }

      if (var8 > -1) {
         this.Locked = Rand.Next(100) < var8;
      }
   }

    bool isDestroyed() {
      return this.destroyed;
   }

    bool IsOpen() {
      return this.open;
   }

    bool onMouseLeftClick(int var1, int var2) {
    return false;
   }

    bool TestCollide(IsoMovingObject var1, IsoGridSquare var2, IsoGridSquare var3) {
      if (var2 == this.square) {
         if (this.north && var3.getY() < var2.getY()) {
            if (var1 != nullptr) {
               var1.collideWith(this);
            }

    return true;
         }

         if (!this.north && var3.getX() < var2.getX()) {
            if (var1 != nullptr) {
               var1.collideWith(this);
            }

    return true;
         }
      } else {
         if (this.north && var3.getY() > var2.getY()) {
            if (var1 != nullptr) {
               var1.collideWith(this);
            }

    return true;
         }

         if (!this.north && var3.getX() > var2.getX()) {
            if (var1 != nullptr) {
               var1.collideWith(this);
            }

    return true;
         }
      }

    return false;
   }

    VisionResult TestVision(IsoGridSquare var1, IsoGridSquare var2) {
      if (var2.getZ() != var1.getZ()) {
         return VisionResult.NoEffect;
      } else {
         if (var1 == this.square) {
            if (this.north && var2.getY() < var1.getY()) {
               return VisionResult.Unblocked;
            }

            if (!this.north && var2.getX() < var1.getX()) {
               return VisionResult.Unblocked;
            }
         } else {
            if (this.north && var2.getY() > var1.getY()) {
               return VisionResult.Unblocked;
            }

            if (!this.north && var2.getX() > var1.getX()) {
               return VisionResult.Unblocked;
            }
         }

         return VisionResult.NoEffect;
      }
   }

    void Thump(IsoMovingObject var1) {
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

      if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
         if (((IsoZombie)var1).cognition == 1
            && !this.canClimbThrough((IsoZombie)var1)
            && !this.isInvincible()
            && (!this.Locked || var1.getCurrentSquare() != nullptr && !var1.getCurrentSquare().Is(IsoFlagType.exterior))) {
            this.ToggleWindow((IsoGameCharacter)var1);
            if (this.canClimbThrough((IsoZombie)var1)) {
               return;
            }
         }

    int var3 = ThumpState.getFastForwardDamageMultiplier();
         this.DirtySlice();
         this.Damage(((IsoZombie)var1).strength * var3, var1);
         WorldSoundManager.instance.addSound(var1, this.square.getX(), this.square.getY(), this.square.getZ(), 20, 20, true, 4.0F, 15.0F);
      }

      if (!this.isDestroyed() && this.Health <= 0) {
         if (this.getSquare().getBuilding() != nullptr) {
            this.getSquare().getBuilding().forceAwake();
         }

         if (GameServer.bServer) {
            GameServer.smashWindow(this, 1);
            GameServer.PlayWorldSoundServer((IsoGameCharacter)var1, "SmashWindow", false, var1.getCurrentSquare(), 0.2F, 20.0F, 1.1F, true);
         }

         ((IsoGameCharacter)var1).getEmitter().playSound("SmashWindow", this);
         WorldSoundManager.instance.addSound(nullptr, this.square.getX(), this.square.getY(), this.square.getZ(), 10, 20, true, 4.0F, 15.0F);
         var1.setThumpTarget(nullptr);
         this.destroyed = true;
         this.sprite = this.smashedSprite;
         this.square.InvalidateSpecialObjectPaths();
         this.addBrokenGlass(var1);
         if (dynamic_cast<IsoZombie*>(var1) != nullptr && this.getThumpableFor((IsoZombie)var1) != nullptr) {
            var1.setThumpTarget(this.getThumpableFor((IsoZombie)var1));
         }
      }
   }

    Thumpable getThumpableFor(IsoGameCharacter var1) {
    IsoBarricade var2 = this.getBarricadeForCharacter(var1);
      if (var2 != nullptr) {
    return var2;
      } else if (!this.isDestroyed() && !this.IsOpen()) {
    return this;
      } else {
         var2 = this.getBarricadeOppositeCharacter(var1);
         return var2 != nullptr ? var2 : nullptr;
      }
   }

    float getThumpCondition() {
      return (float)PZMath.clamp(this.Health, 0, this.MaxHealth) / this.MaxHealth;
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.open = var1.get() == 1;
      this.north = var1.get() == 1;
      if (var2 >= 87) {
         this.Health = var1.getInt();
      } else {
    int var4 = var1.getInt();
         this.Health = var1.getInt();
    int var5 = var1.getInt();
         if (var2 >= 49) {
    short var6 = var1.getShort();
         } else {
    int var9 = Math.max(var5, var4 * 1000);
         }

         this.OldNumPlanks = var4;
      }

      this.Locked = var1.get() == 1;
      this.PermaLocked = var1.get() == 1;
      this.destroyed = var1.get() == 1;
      if (var2 >= 64) {
         this.glassRemoved = var1.get() == 1;
         if (var1.get() == 1) {
            this.openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
         }

         if (var1.get() == 1) {
            this.closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
         }

         if (var1.get() == 1) {
            this.smashedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
         }

         if (var1.get() == 1) {
            this.glassRemovedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
         }
      } else {
         if (var1.getInt() == 1) {
            this.openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
         }

         if (var1.getInt() == 1) {
            this.closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
         }

         if (var1.getInt() == 1) {
            this.smashedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
         }

         if (this.closedSprite != nullptr) {
            if (this.destroyed && this.closedSprite.getProperties().Is("SmashedTileOffset")) {
    int var7 = int.parseInt(this.closedSprite.getProperties().Val("SmashedTileOffset"));
               this.closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, this.closedSprite, -var7);
            }

            if (this.closedSprite.getProperties().Is("GlassRemovedOffset")) {
    int var8 = int.parseInt(this.closedSprite.getProperties().Val("GlassRemovedOffset"));
               this.glassRemovedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, this.closedSprite, var8);
            }
         }

         if (this.glassRemovedSprite == nullptr) {
            this.glassRemovedSprite = this.smashedSprite != nullptr ? this.smashedSprite : this.closedSprite;
         }
      }

      this.MaxHealth = var1.getInt();
      if (this.closedSprite != nullptr) {
         if (this.north) {
            this.closedSprite.getProperties().Set(IsoFlagType.cutN);
            this.closedSprite.getProperties().Set(IsoFlagType.windowN);
         } else {
            this.closedSprite.getProperties().Set(IsoFlagType.cutW);
            this.closedSprite.getProperties().Set(IsoFlagType.windowW);
         }

         if (this.smashedSprite != this.closedSprite && this.smashedSprite != nullptr) {
            this.smashedSprite.AddProperties(this.closedSprite);
            this.smashedSprite.setType(this.closedSprite.getType());
         }

         if (this.openSprite != this.closedSprite && this.openSprite != nullptr) {
            this.openSprite.AddProperties(this.closedSprite);
            this.openSprite.setType(this.closedSprite.getType());
         }

         if (this.glassRemovedSprite != this.closedSprite && this.glassRemovedSprite != nullptr) {
            this.glassRemovedSprite.AddProperties(this.closedSprite);
            this.glassRemovedSprite.setType(this.closedSprite.getType());
         }
      }

      if (SystemDisabler.doObjectStateSyncEnable && GameClient.bClient) {
         GameClient.instance.objectSyncReq.putRequestLoad(this.square);
      }
   }

    void addToWorld() {
      super.addToWorld();
      this.getCell().addToWindowList(this);
   }

    void removeFromWorld() {
      super.removeFromWorld();
      this.getCell().removeFromWindowList(this);
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.put((byte)(this.open ? 1 : 0));
      var1.put((byte)(this.north ? 1 : 0));
      var1.putInt(this.Health);
      var1.put((byte)(this.Locked ? 1 : 0));
      var1.put((byte)(this.PermaLocked ? 1 : 0));
      var1.put((byte)(this.destroyed ? 1 : 0));
      var1.put((byte)(this.glassRemoved ? 1 : 0));
      if (this.openSprite != nullptr) {
         var1.put((byte)1);
         var1.putInt(this.openSprite.ID);
      } else {
         var1.put((byte)0);
      }

      if (this.closedSprite != nullptr) {
         var1.put((byte)1);
         var1.putInt(this.closedSprite.ID);
      } else {
         var1.put((byte)0);
      }

      if (this.smashedSprite != nullptr) {
         var1.put((byte)1);
         var1.putInt(this.smashedSprite.ID);
      } else {
         var1.put((byte)0);
      }

      if (this.glassRemovedSprite != nullptr) {
         var1.put((byte)1);
         var1.putInt(this.glassRemovedSprite.ID);
      } else {
         var1.put((byte)0);
      }

      var1.putInt(this.MaxHealth);
   }

    void saveState(ByteBuffer var1) {
      var1.put((byte)(this.Locked ? 1 : 0));
   }

    void loadState(ByteBuffer var1) {
    bool var2 = var1.get() == 1;
      if (var2 != this.Locked) {
         this.Locked = var2;
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      super.render(var1, var2, var3, var4, var5, var6, var7);
   }

    void openCloseCurtain(IsoGameCharacter var1) {
      if (var1 == IsoPlayer.getInstance()) {
    void* var2 = nullptr;
    void* var3 = nullptr;
    IsoDirections var4 = IsoDirections.N;
         if (this.north) {
    IsoGridSquare var5 = this.square;
            var4 = IsoDirections.N;
            if (var5.getRoom() == nullptr) {
               var5 = this.getCell().getGridSquare(var5.getX(), var5.getY() - 1, var5.getZ());
               var4 = IsoDirections.S;
            }

            var3 = var2;
            var2 = var5;
         } else {
    IsoGridSquare var12 = this.square;
            var4 = IsoDirections.W;
            if (var12.getRoom() == nullptr) {
               var12 = this.getCell().getGridSquare(var12.getX() - 1, var12.getY(), var12.getZ());
               var4 = IsoDirections.E;
            }

            var3 = var2;
            var2 = var12;
         }

         if (var2 != nullptr) {
            for (int var13 = 0; var13 < var2.getSpecialObjects().size(); var13++) {
               if (var2.getSpecialObjects().get(var13) instanceof IsoCurtain) {
                  ((IsoCurtain)var2.getSpecialObjects().get(var13)).ToggleDoorSilent();
                  return;
               }
            }
         }

         if (var3 != nullptr) {
            for (int var14 = 0; var14 < var3.getSpecialObjects().size(); var14++) {
               if (var3.getSpecialObjects().get(var14) instanceof IsoCurtain) {
                  ((IsoCurtain)var3.getSpecialObjects().get(var14)).ToggleDoorSilent();
                  return;
               }
            }
         }
      }
   }

    void removeSheet(IsoGameCharacter var1) {
    IsoGridSquare var2 = nullptr;
    IsoDirections var3 = IsoDirections.N;
      if (this.north) {
    IsoGridSquare var4 = this.square;
         var3 = IsoDirections.N;
         if (var4.getRoom() == nullptr) {
            var4 = this.getCell().getGridSquare(var4.getX(), var4.getY() - 1, var4.getZ());
            var3 = IsoDirections.S;
         }

         var2 = var4;
      } else {
    IsoGridSquare var11 = this.square;
         var3 = IsoDirections.W;
         if (var11.getRoom() == nullptr) {
            var11 = this.getCell().getGridSquare(var11.getX() - 1, var11.getY(), var11.getZ());
            var3 = IsoDirections.E;
         }

         var2 = var11;
      }

      for (int var12 = 0; var12 < var2.getSpecialObjects().size(); var12++) {
    IsoObject var5 = (IsoObject)var2.getSpecialObjects().get(var12);
         if (dynamic_cast<IsoCurtain*>(var5) != nullptr) {
            var2.transmitRemoveItemFromSquare(var5);
            if (var1 != nullptr) {
               if (GameServer.bServer) {
                  var1.sendObjectChange("addItemOfType", new Object[]{"type", var5.getName()});
               } else {
                  var1.getInventory().AddItem(var5.getName());
               }
            }
            break;
         }
      }
   }

    void addSheet(IsoGameCharacter var1) {
    IsoGridSquare var2 = nullptr;
    IsoObjectType var3;
      if (this.north) {
    IsoGridSquare var4 = this.square;
         var3 = IsoObjectType.curtainN;
         if (var1 != nullptr) {
            if (var1.getY() < this.getY()) {
               var4 = this.getCell().getGridSquare(var4.getX(), var4.getY() - 1, var4.getZ());
               var3 = IsoObjectType.curtainS;
            }
         } else if (var4.getRoom() == nullptr) {
            var4 = this.getCell().getGridSquare(var4.getX(), var4.getY() - 1, var4.getZ());
            var3 = IsoObjectType.curtainS;
         }

         var2 = var4;
      } else {
    IsoGridSquare var7 = this.square;
         var3 = IsoObjectType.curtainW;
         if (var1 != nullptr) {
            if (var1.getX() < this.getX()) {
               var7 = this.getCell().getGridSquare(var7.getX() - 1, var7.getY(), var7.getZ());
               var3 = IsoObjectType.curtainE;
            }
         } else if (var7.getRoom() == nullptr) {
            var7 = this.getCell().getGridSquare(var7.getX() - 1, var7.getY(), var7.getZ());
            var3 = IsoObjectType.curtainE;
         }

         var2 = var7;
      }

      if (var2.getCurtain(var3) == nullptr) {
         if (var2 != nullptr) {
    int var8 = 16;
            if (var3 == IsoObjectType.curtainE) {
               var8++;
            }

            if (var3 == IsoObjectType.curtainS) {
               var8 += 3;
            }

            if (var3 == IsoObjectType.curtainN) {
               var8 += 2;
            }

            var8 += 4;
    IsoCurtain var5 = std::make_shared<IsoCurtain>(this.getCell(), var2, "fixtures_windows_curtains_01_" + var8, this.north);
            var2.AddSpecialTileObject(var5);
            if (!var5.open) {
               var5.ToggleDoorSilent();
            }

            if (GameServer.bServer) {
               var5.transmitCompleteItemToClients();
               if (var1 != nullptr) {
                  var1.sendObjectChange("removeOneOf", new Object[]{"type", "Sheet"});
               }
            } else if (var1 != nullptr) {
               var1.getInventory().RemoveOneOf("Sheet");
            }
         }
      }
   }

    void ToggleWindow(IsoGameCharacter var1) {
      this.DirtySlice();
      IsoGridSquare.setRecalcLightTime(-1);
      if (!this.PermaLocked) {
         if (!this.destroyed) {
            if (var1 == nullptr || this.getBarricadeForCharacter(var1) == nullptr) {
               this.Locked = false;
               this.open = !this.open;
               this.sprite = this.closedSprite;
               this.square.InvalidateSpecialObjectPaths();
               if (this.open) {
                  if (!(dynamic_cast<IsoZombie*>(var1) != nullptr) || SandboxOptions.getInstance().Lore.TriggerHouseAlarm.getValue()) {
                     this.handleAlarm();
                  }

                  this.sprite = this.openSprite;
               }

               this.square.RecalcProperties();
               this.syncIsoObject(false, (byte)(this.open ? 1 : 0), nullptr, nullptr);
               PolygonalMap2.instance.squareChanged(this.square);
               LuaEventManager.triggerEvent("OnContainerUpdate");
            }
         }
      }
   }

    void syncIsoObjectSend(ByteBufferWriter var1) {
      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
    uint8_t var2 = (byte)this.square.getObjects().indexOf(this);
      var1.putByte(var2);
      var1.putByte((byte)1);
      var1.putByte((byte)(this.open ? 1 : 0));
      var1.putByte((byte)(this.destroyed ? 1 : 0));
      var1.putByte((byte)(this.Locked ? 1 : 0));
      var1.putByte((byte)(this.PermaLocked ? 1 : 0));
   }

    void syncIsoObject(bool var1, uint8_t var2, UdpConnection var3, ByteBuffer var4) {
      if (this.square == nullptr) {
         System.out.println("ERROR: " + this.getClass().getSimpleName() + " square is nullptr");
      } else if (this.getObjectIndex() == -1) {
         System.out
            .println(
               "ERROR: " + this.getClass().getSimpleName() + " not found on square " + this.square.getX() + "," + this.square.getY() + "," + this.square.getZ()
            );
      } else {
         if (GameClient.bClient && !var1) {
    ByteBufferWriter var12 = GameClient.connection.startPacket();
            PacketType.SyncIsoObject.doPacket(var12);
            this.syncIsoObjectSend(var12);
            PacketType.SyncIsoObject.send(GameClient.connection);
         } else if (GameServer.bServer && !var1) {
            for (UdpConnection var13 : GameServer.udpEngine.connections) {
    ByteBufferWriter var14 = var13.startPacket();
               PacketType.SyncIsoObject.doPacket(var14);
               this.syncIsoObjectSend(var14);
               PacketType.SyncIsoObject.send(var13);
            }
         } else if (var1) {
    bool var5 = var4.get() == 1;
    bool var6 = var4.get() == 1;
    bool var7 = var4.get() == 1;
            if (var2 == 1) {
               this.open = true;
               this.sprite = this.openSprite;
            } else if (var2 == 0) {
               this.open = false;
               this.sprite = this.closedSprite;
            }

            if (var5) {
               this.destroyed = true;
               this.sprite = this.smashedSprite;
            }

            this.Locked = var6;
            this.PermaLocked = var7;
            if (GameServer.bServer) {
               for (UdpConnection var9 : GameServer.udpEngine.connections) {
                  if (var3 != nullptr && var9.getConnectedGUID() != var3.getConnectedGUID()) {
    ByteBufferWriter var10 = var9.startPacket();
                     PacketType.SyncIsoObject.doPacket(var10);
                     this.syncIsoObjectSend(var10);
                     PacketType.SyncIsoObject.send(var9);
                  }
               }
            }

            this.square.RecalcProperties();
            LuaEventManager.triggerEvent("OnContainerUpdate");
         }
      }
   }

    static bool isTopOfSheetRopeHere(IsoGridSquare var0) {
      return var0 == nullptr
         ? false
         : var0.Is(IsoFlagType.climbSheetTopN)
            || var0.Is(IsoFlagType.climbSheetTopS)
            || var0.Is(IsoFlagType.climbSheetTopW)
            || var0.Is(IsoFlagType.climbSheetTopE);
   }

    static bool isTopOfSheetRopeHere(IsoGridSquare var0, bool var1) {
      if (var0 == nullptr) {
    return false;
      } else {
         if (var1) {
            if (var0.Is(IsoFlagType.climbSheetTopN)) {
    return true;
            }

            if (var0.nav[IsoDirections.N.index()] != nullptr && var0.nav[IsoDirections.N.index()].Is(IsoFlagType.climbSheetTopS)) {
    return true;
            }
         } else {
            if (var0.Is(IsoFlagType.climbSheetTopW)) {
    return true;
            }

            if (var0.nav[IsoDirections.W.index()] != nullptr && var0.nav[IsoDirections.W.index()].Is(IsoFlagType.climbSheetTopE)) {
    return true;
            }
         }

    return false;
      }
   }

    bool haveSheetRope() {
    return isTopOfSheetRopeHere();
   }

    static bool isSheetRopeHere(IsoGridSquare var0) {
      return var0 == nullptr
         ? false
         : var0.Is(IsoFlagType.climbSheetTopW)
            || var0.Is(IsoFlagType.climbSheetTopN)
            || var0.Is(IsoFlagType.climbSheetTopE)
            || var0.Is(IsoFlagType.climbSheetTopS)
            || var0.Is(IsoFlagType.climbSheetW)
            || var0.Is(IsoFlagType.climbSheetN)
            || var0.Is(IsoFlagType.climbSheetE)
            || var0.Is(IsoFlagType.climbSheetS);
   }

    static bool canClimbHere(IsoGridSquare var0) {
      if (var0 == nullptr) {
    return false;
      } else if (var0.getProperties().Is(IsoFlagType.solid)) {
    return false;
      } else {
         return var0.Has(IsoObjectType.stairsBN) || var0.Has(IsoObjectType.stairsMN) || var0.Has(IsoObjectType.stairsTN)
            ? false
            : !var0.Has(IsoObjectType.stairsBW) && !var0.Has(IsoObjectType.stairsMW) && !var0.Has(IsoObjectType.stairsTW);
      }
   }

    static int countAddSheetRope(IsoGridSquare var0, bool var1) {
      if (isTopOfSheetRopeHere(var0, var1)) {
    return 0;
      } else {
    IsoCell var2 = IsoWorld.instance.CurrentCell;
         if (var0.TreatAsSolidFloor()) {
            if (var1) {
    IsoGridSquare var3 = var2.getOrCreateGridSquare(var0.getX(), var0.getY() - 1, var0.getZ());
               if (var3 == nullptr || var3.TreatAsSolidFloor() || isSheetRopeHere(var3) || !canClimbHere(var3)) {
    return 0;
               }

               var0 = var3;
            } else {
    IsoGridSquare var4 = var2.getOrCreateGridSquare(var0.getX() - 1, var0.getY(), var0.getZ());
               if (var4 == nullptr || var4.TreatAsSolidFloor() || isSheetRopeHere(var4) || !canClimbHere(var4)) {
    return 0;
               }

               var0 = var4;
            }
         }

         for (int var5 = 1; var0 != nullptr; var5++) {
            if (!canClimbHere(var0)) {
    return 0;
            }

            if (var0.TreatAsSolidFloor()) {
    return var5;
            }

            if (var0.getZ() == 0) {
    return var5;
            }

            var0 = var2.getOrCreateGridSquare(var0.getX(), var0.getY(), var0.getZ() - 1);
         }

    return 0;
      }
   }

    int countAddSheetRope() {
    return countAddSheetRope();
   }

    static bool canAddSheetRope(IsoGridSquare var0, bool var1) {
    return countAddSheetRope();
   }

    bool canAddSheetRope() {
      return !this.canClimbThrough(nullptr) ? false : canAddSheetRope(this.square, this.north);
   }

    bool addSheetRope(IsoPlayer var1, const std::string& var2) {
      return !this.canAddSheetRope() ? false : addSheetRope(var1, this.square, this.north, var2);
   }

    static bool addSheetRope(IsoPlayer var0, IsoGridSquare var1, bool var2, const std::string& var3) {
    bool var4 = false;
    int var5 = 0;
    uint8_t var6 = 0;
      if (var2) {
         var6 = 1;
      }

    bool var7 = false;
    bool var8 = false;
    IsoGridSquare var9 = nullptr;
    IsoGridSquare var10 = nullptr;
    IsoCell var11 = IsoWorld.instance.CurrentCell;
      if (var1.TreatAsSolidFloor()) {
         if (!var2) {
            var9 = var11.getGridSquare(var1.getX() - 1, var1.getY(), var1.getZ());
            if (var9 != nullptr) {
               var8 = true;
               var6 = 3;
            }
         } else {
            var10 = var11.getGridSquare(var1.getX(), var1.getY() - 1, var1.getZ());
            if (var10 != nullptr) {
               var7 = true;
               var6 = 4;
            }
         }
      }

      if (var1.getProperties().Is(IsoFlagType.solidfloor)) {
      }

      while (var1 != nullptr && (GameServer.bServer || var0.getInventory().contains(var3))) {
    std::string var12 = "crafted_01_" + var6;
         if (var5 > 0) {
            if (var8) {
               var12 = "crafted_01_10";
            } else if (var7) {
               var12 = "crafted_01_13";
            } else {
               var12 = "crafted_01_" + (var6 + 8);
            }
         }

    IsoObject var13 = std::make_shared<IsoObject>(var11, var1, var12);
         var13.setName(var3);
         var13.sheetRope = true;
         var1.getObjects().push_back(var13);
         var13.transmitCompleteItemToClients();
         var1.haveSheetRope = true;
         if (var7 && var5 == 0) {
            var1 = var10;
            var13 = std::make_shared<IsoObject>(var11, var10, "crafted_01_5");
            var13.setName(var3);
            var13.sheetRope = true;
            var10.getObjects().push_back(var13);
            var13.transmitCompleteItemToClients();
         }

         if (var8 && var5 == 0) {
            var1 = var9;
            var13 = std::make_shared<IsoObject>(var11, var9, "crafted_01_2");
            var13.setName(var3);
            var13.sheetRope = true;
            var9.getObjects().push_back(var13);
            var13.transmitCompleteItemToClients();
         }

         var1.RecalcProperties();
         var1.getProperties().UnSet(IsoFlagType.solidtrans);
         if (GameServer.bServer) {
            if (var5 == 0) {
               var0.sendObjectChange("removeOneOf", new Object[]{"type", "Nails"});
            }

            var0.sendObjectChange("removeOneOf", new Object[]{"type", var3});
         } else {
            if (var5 == 0) {
               var0.getInventory().RemoveOneOf("Nails");
            }

            var0.getInventory().RemoveOneOf(var3);
         }

         var5++;
         if (var4) {
            break;
         }

         var1 = var11.getOrCreateGridSquare(var1.getX(), var1.getY(), var1.getZ() - 1);
         if (var1 != nullptr && var1.TreatAsSolidFloor()) {
            var4 = true;
         }
      }

    return true;
   }

    bool removeSheetRope(IsoPlayer var1) {
      return !this.haveSheetRope() ? false : removeSheetRope(var1, this.square, this.north);
   }

    static bool removeSheetRope(IsoPlayer var0, IsoGridSquare var1, bool var2) {
      if (var1 == nullptr) {
    return false;
      } else {
    IsoGridSquare var6 = var1;
         var1.haveSheetRope = false;
    IsoFlagType var3;
    IsoFlagType var4;
         if (var2) {
            if (var1.Is(IsoFlagType.climbSheetTopN)) {
               var3 = IsoFlagType.climbSheetTopN;
               var4 = IsoFlagType.climbSheetN;
            } else {
               if (var1.nav[IsoDirections.N.index()] == nullptr || !var1.nav[IsoDirections.N.index()].Is(IsoFlagType.climbSheetTopS)) {
    return false;
               }

               var3 = IsoFlagType.climbSheetTopS;
               var4 = IsoFlagType.climbSheetS;
    std::string var5 = "crafted_01_4";

               for (int var7 = 0; var7 < var6.getObjects().size(); var7++) {
    IsoObject var8 = (IsoObject)var6.getObjects().get(var7);
                  if (var8.sprite != nullptr && var8.sprite.getName() != nullptr && var8.sprite.getName() == var5)) {
                     var6.transmitRemoveItemFromSquare(var8);
                     break;
                  }
               }

               var6 = var1.nav[IsoDirections.N.index()];
            }
         } else if (var1.Is(IsoFlagType.climbSheetTopW)) {
            var3 = IsoFlagType.climbSheetTopW;
            var4 = IsoFlagType.climbSheetW;
         } else {
            if (var1.nav[IsoDirections.W.index()] == nullptr || !var1.nav[IsoDirections.W.index()].Is(IsoFlagType.climbSheetTopE)) {
    return false;
            }

            var3 = IsoFlagType.climbSheetTopE;
            var4 = IsoFlagType.climbSheetE;
    std::string var10 = "crafted_01_3";

            for (int var11 = 0; var11 < var6.getObjects().size(); var11++) {
    IsoObject var13 = (IsoObject)var6.getObjects().get(var11);
               if (var13.sprite != nullptr && var13.sprite.getName() != nullptr && var13.sprite.getName() == var10)) {
                  var6.transmitRemoveItemFromSquare(var13);
                  break;
               }
            }

            var6 = var1.nav[IsoDirections.W.index()];
         }

         while (var6 != nullptr) {
    bool var12 = false;

            for (int var14 = 0; var14 < var6.getObjects().size(); var14++) {
    IsoObject var9 = (IsoObject)var6.getObjects().get(var14);
               if (var9.getProperties() != nullptr && (var9.getProperties().Is(var3) || var9.getProperties().Is(var4))) {
                  var6.transmitRemoveItemFromSquare(var9);
                  if (GameServer.bServer) {
                     if (var0 != nullptr) {
                        var0.sendObjectChange("addItemOfType", new Object[]{"type", var9.getName()});
                     }
                  } else if (var0 != nullptr) {
                     var0.getInventory().AddItem(var9.getName());
                  }

                  var12 = true;
                  break;
               }
            }

            if (!var12 || var6.getZ() == 0) {
               break;
            }

            var6 = var6.getCell().getGridSquare(var6.getX(), var6.getY(), var6.getZ() - 1);
         }

    return true;
      }
   }

    void Damage(float var1) {
      this.Damage(var1, false);
   }

    void Damage(float var1, bool var2) {
      if (!this.isInvincible() && !"Tutorial" == Core.GameMode)) {
         this.DirtySlice();
         this.Health = (int)(this.Health - var1);
         if (this.Health < 0) {
            this.Health = 0;
         }

         if (!this.isDestroyed() && this.Health == 0) {
            this.smashWindow(false, !var2 || SandboxOptions.getInstance().Lore.TriggerHouseAlarm.getValue());
            if (this.getSquare().getBuilding() != nullptr) {
               this.getSquare().getBuilding().forceAwake();
            }
         }
      }
   }

    void Damage(float var1, IsoMovingObject var2) {
      if (!this.isInvincible() && !"Tutorial" == Core.GameMode)) {
         this.Health = (int)(this.Health - var1);
         if (this.Health < 0) {
            this.Health = 0;
         }

         if (!this.isDestroyed() && this.Health == 0) {
    bool var3 = !(dynamic_cast<IsoZombie*>(var2) != nullptr) || SandboxOptions.getInstance().Lore.TriggerHouseAlarm.getValue();
            this.smashWindow(false, var3);
            this.addBrokenGlass(var2);
         }
      }
   }

    bool isLocked() {
      return this.Locked;
   }

    bool isSmashed() {
      return this.destroyed;
   }

    bool isInvincible() {
      if (this.square != nullptr && this.square.Is(IsoFlagType.makeWindowInvincible)) {
    int var1 = this.getObjectIndex();
         if (var1 != -1) {
            IsoObject[] var2 = (IsoObject[])this.square.getObjects().getElements();
    int var3 = this.square.getObjects().size();

            for (int var4 = 0; var4 < var3; var4++) {
               if (var4 != var1) {
    IsoObject var5 = var2[var4];
    PropertyContainer var6 = var5.getProperties();
                  if (var6 != nullptr && var6.Is(this.getNorth() ? IsoFlagType.cutN : IsoFlagType.cutW) && var6.Is(IsoFlagType.makeWindowInvincible)) {
    return true;
                  }
               }
            }
         }

         return this.sprite != nullptr && this.sprite.getProperties().Is(IsoFlagType.makeWindowInvincible);
      } else {
    return false;
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
    return true;
   }

    IsoBarricade getBarricadeForCharacter(IsoGameCharacter var1) {
      return IsoBarricade.GetBarricadeForCharacter(this, var1);
   }

    IsoBarricade getBarricadeOppositeCharacter(IsoGameCharacter var1) {
      return IsoBarricade.GetBarricadeOppositeCharacter(this, var1);
   }

    bool getNorth() {
      return this.north;
   }

    Vector2 getFacingPosition(Vector2 var1) {
      if (this.square == nullptr) {
         return var1.set(0.0F, 0.0F);
      } else {
         return this.north ? var1.set(this.getX() + 0.5F, this.getY()) : var1.set(this.getX(), this.getY() + 0.5F);
      }
   }

    void setIsLocked(bool var1) {
      this.Locked = var1;
   }

    IsoSprite getOpenSprite() {
      return this.openSprite;
   }

    void setOpenSprite(IsoSprite var1) {
      this.openSprite = var1;
   }

    void setSmashed(bool var1) {
      if (var1) {
         this.destroyed = true;
         this.sprite = this.smashedSprite;
      } else {
         this.destroyed = false;
         this.sprite = this.open ? this.openSprite : this.closedSprite;
         this.Health = this.MaxHealth;
      }

      this.glassRemoved = false;
   }

    IsoSprite getSmashedSprite() {
      return this.smashedSprite;
   }

    void setSmashedSprite(IsoSprite var1) {
      this.smashedSprite = var1;
   }

    void setPermaLocked(bool var1) {
      this.PermaLocked = var1;
   }

    bool isPermaLocked() {
      return this.PermaLocked;
   }

    static bool canClimbThroughHelper(IsoGameCharacter var0, IsoGridSquare var1, IsoGridSquare var2, bool var3) {
    IsoGridSquare var4 = var1;
    float var5 = 0.5F;
    float var6 = 0.5F;
      if (var3) {
         if (var0.getY() >= var1.getY()) {
            var4 = var2;
            var6 = 0.7F;
         } else {
            var6 = 0.3F;
         }
      } else if (var0.getX() >= var1.getX()) {
         var4 = var2;
         var5 = 0.7F;
      } else {
         var5 = 0.3F;
      }

      if (var4 == nullptr) {
    return false;
      } else if (var4.isSolid()) {
    return false;
      } else if (var4.Is(IsoFlagType.water)) {
    return false;
      } else {
         return !var0.canClimbDownSheetRope(var4)
               && !var4.HasStairsBelow()
               && !PolygonalMap2.instance.canStandAt(var4.x + var5, var4.y + var6, var4.z, nullptr, 19)
            ? !var4.TreatAsSolidFloor()
            : !GameClient.bClient
               || !(dynamic_cast<IsoPlayer*>(var0) != nullptr)
               || SafeHouse.isSafeHouse(var4, ((IsoPlayer)var0).getUsername(), true) == nullptr
               || ServerOptions.instance.SafehouseAllowTrepass.getValue();
      }
   }

    bool canClimbThrough(IsoGameCharacter var1) {
      if (this.square == nullptr || this.isInvincible()) {
    return false;
      } else if (this.isBarricaded()) {
    return false;
      } else if (var1 != nullptr && !canClimbThroughHelper(var1, this.getSquare(), this.getOppositeSquare(), this.north)) {
    return false;
      } else {
    IsoGameCharacter var2 = this.getFirstCharacterClosing();
         if (var2 != nullptr && var2.isVariable("CloseWindowOutcome", "success")) {
    return false;
         } else {
            return this.Health > 0 && !this.destroyed ? this.open : true;
         }
      }
   }

    IsoGameCharacter getFirstCharacterClimbingThrough() {
    IsoGameCharacter var1 = this.getFirstCharacterClimbingThrough(this.getSquare());
      return var1 != nullptr ? var1 : this.getFirstCharacterClimbingThrough(this.getOppositeSquare());
   }

    IsoGameCharacter getFirstCharacterClimbingThrough(IsoGridSquare var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
         for (int var2 = 0; var2 < var1.getMovingObjects().size(); var2++) {
    IsoGameCharacter var3 = (IsoGameCharacter)Type.tryCastTo((IsoMovingObject)var1.getMovingObjects().get(var2), IsoGameCharacter.class);
            if (var3 != nullptr && var3.isClimbingThroughWindow(this)) {
    return var3;
            }
         }

    return nullptr;
      }
   }

    IsoGameCharacter getFirstCharacterClosing() {
    IsoGameCharacter var1 = this.getFirstCharacterClosing(this.getSquare());
      return var1 != nullptr ? var1 : this.getFirstCharacterClosing(this.getOppositeSquare());
   }

    IsoGameCharacter getFirstCharacterClosing(IsoGridSquare var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
         for (int var2 = 0; var2 < var1.getMovingObjects().size(); var2++) {
    IsoGameCharacter var3 = (IsoGameCharacter)Type.tryCastTo((IsoMovingObject)var1.getMovingObjects().get(var2), IsoGameCharacter.class);
            if (var3 != nullptr && var3.isClosingWindow(this)) {
    return var3;
            }
         }

    return nullptr;
      }
   }

    bool isGlassRemoved() {
      return this.glassRemoved;
   }

    void setGlassRemoved(bool var1) {
      if (this.destroyed) {
         if (var1) {
            this.sprite = this.glassRemovedSprite;
            this.glassRemoved = true;
         } else {
            this.sprite = this.smashedSprite;
            this.glassRemoved = false;
         }

         if (this.getObjectIndex() != -1) {
            PolygonalMap2.instance.squareChanged(this.square);
         }
      }
   }

    void removeBrokenGlass() {
      if (GameClient.bClient) {
         GameClient.instance.smashWindow(this, 2);
      } else {
         this.setGlassRemoved(true);
      }
   }

    IsoBarricade addBarricadesDebug(int var1, bool var2) {
    IsoGridSquare var3 = this.square.getRoom() == nullptr ? this.square : this.getOppositeSquare();
    bool var4 = var3 != this.square;
    IsoBarricade var5 = IsoBarricade.AddBarricadeToObject(this, var4);
      if (var5 != nullptr) {
         for (int var6 = 0; var6 < var1; var6++) {
            if (var2) {
               var5.addMetalBar(nullptr, nullptr);
            } else {
               var5.addPlank(nullptr, nullptr);
            }
         }
      }

    return var5;
   }

    void addRandomBarricades() {
    IsoGridSquare var1 = this.square.getRoom() == nullptr ? this.square : this.getOppositeSquare();
      if (this.getZ() == 0.0F && var1 != nullptr && var1.getRoom() == nullptr) {
    bool var2 = var1 != this.square;
    IsoBarricade var3 = IsoBarricade.AddBarricadeToObject(this, var2);
         if (var3 != nullptr) {
    int var4 = Rand.Next(1, 4);

            for (int var5 = 0; var5 < var4; var5++) {
               var3.addPlank(nullptr, nullptr);
            }

            if (GameServer.bServer) {
               var3.transmitCompleteItemToClients();
            }
         }
      } else {
         this.addSheet(nullptr);
         this.HasCurtains().ToggleDoor(nullptr);
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
