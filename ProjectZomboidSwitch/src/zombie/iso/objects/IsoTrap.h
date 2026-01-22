#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoTrap/ExplosionMode.h"
#include "zombie/iso/sprite/IsoDirectionFrame.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoTrap : public IsoObject {
public:
    int timerBeforeExplosion = 0;
    int FPS;
    int sensorRange = 0;
    int firePower = 0;
    int fireRange = 0;
    int explosionPower = 0;
    int explosionRange = 0;
    int smokeRange = 0;
    int noiseRange = 0;
    int noiseDuration = 0;
    float noiseStartTime = 0.0F;
    float lastWorldSoundTime = 0.0F;
    float extraDamage = 0.0F;
    int remoteControlID = -1;
    std::string countDownSound = nullptr;
    std::string explosionSound = nullptr;
    int lastBeep = 0;
    HandWeapon weapon;
    bool instantExplosion;

    public IsoTrap(IsoCell var1) {
      super(var1);
      this.FPS = GameServer.bServer ? 10 : PerformanceSettings.getLockFPS();
   }

    public IsoTrap(HandWeapon var1, IsoCell var2, IsoGridSquare var3) {
      this.square = var3;
      this.initSprite(var1);
      this.setSensorRange(var1.getSensorRange());
      this.setFireRange(var1.getFireRange());
      this.setFirePower(var1.getFirePower());
      this.setExplosionPower(var1.getExplosionPower());
      this.setExplosionRange(var1.getExplosionRange());
      this.setSmokeRange(var1.getSmokeRange());
      this.setNoiseRange(var1.getNoiseRange());
      this.setNoiseDuration(var1.getNoiseDuration());
      this.setExtraDamage(var1.getExtraDamage());
      this.setRemoteControlID(var1.getRemoteControlID());
      this.setCountDownSound(var1.getCountDownSound());
      this.setExplosionSound(var1.getExplosionSound());
      this.FPS = GameServer.bServer ? 10 : PerformanceSettings.getLockFPS();
      if (var1.getExplosionTimer() > 0) {
         this.timerBeforeExplosion = var1.getExplosionTimer() * this.FPS - 1;
      } else if (!var1.canBeRemote()) {
         this.timerBeforeExplosion = 1;
      }

      if (var1.canBePlaced()) {
         this.weapon = var1;
      }

      this.instantExplosion = var1.isInstantExplosion();
   }

    void initSprite(HandWeapon var1) {
      if (var1 != nullptr) {
    std::string var2;
         if (var1.getPlacedSprite() != nullptr && !var1.getPlacedSprite().empty()) {
            var2 = var1.getPlacedSprite();
         } else if (var1.getTex() != nullptr && var1.getTex().getName() != nullptr) {
            var2 = var1.getTex().getName();
         } else {
            var2 = "media/inventory/world/WItem_Sack.png";
         }

         this.sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
    Texture var3 = this.sprite.LoadFrameExplicit(var2);
         if (var2.startsWith("Item_") && var3 != nullptr) {
            if (var1.getScriptItem() == nullptr) {
               this.sprite.def.scaleAspect(var3.getWidthOrig(), var3.getHeightOrig(), 16 * Core.TileScale, 16 * Core.TileScale);
            } else {
    float var10001 = Core.TileScale;
    float var4 = var1.getScriptItem().ScaleWorldIcon * (var10001 / 2.0F);
               this.sprite.def.setScale(var4, var4);
            }
         }
      }
   }

    void update() {
      if (this.timerBeforeExplosion > 0) {
         if (this.timerBeforeExplosion / this.FPS + 1 != this.lastBeep) {
            this.lastBeep = this.timerBeforeExplosion / this.FPS + 1;
            if (!GameServer.bServer && this.getObjectIndex() != -1) {
               this.getOrCreateEmitter();
               if (!StringUtils.isNullOrWhitespace(this.getCountDownSound())) {
                  this.emitter.playSound(this.getCountDownSound());
               } else if (this.lastBeep == 1) {
                  this.emitter.playSound("TrapTimerExpired");
               } else {
                  this.emitter.playSound("TrapTimerLoop");
               }
            }
         }

         this.timerBeforeExplosion--;
         if (this.timerBeforeExplosion == 0) {
            this.triggerExplosion(this.getSensorRange() > 0);
         }
      }

      this.updateSounds();
   }

    void updateSounds() {
      if (this.noiseStartTime > 0.0F) {
    float var1 = (float)GameTime.getInstance().getWorldAgeHours();
         this.noiseStartTime = PZMath.min(this.noiseStartTime, var1);
         this.lastWorldSoundTime = PZMath.min(this.lastWorldSoundTime, var1);
    float var2 = 60.0F / SandboxOptions.getInstance().getDayLengthMinutes();
    float var3 = 60.0F;
         if (var1 - this.noiseStartTime > this.getNoiseDuration() / var3 * var2) {
            this.noiseStartTime = 0.0F;
            if (this.emitter != nullptr) {
               this.emitter.stopAll();
            }
         } else {
            if (!GameServer.bServer && (this.emitter == nullptr || !this.emitter.isPlaying(this.getExplosionSound()))) {
    BaseSoundEmitter var4 = this.getOrCreateEmitter();
               if (var4 != nullptr) {
                  var4.playSound(this.getExplosionSound());
               }
            }

            if (var1 - this.lastWorldSoundTime > 1.0F / var3 * var2 && this.getObjectIndex() != -1) {
               this.lastWorldSoundTime = var1;
               WorldSoundManager.instance
                  .addSoundRepeating(nullptr, this.getSquare().getX(), this.getSquare().getY(), this.getSquare().getZ(), this.getNoiseRange(), 1, true);
            }
         }
      }

      if (this.emitter != nullptr) {
         this.emitter.tick();
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.sprite.CurrentAnim != nullptr && !this.sprite.CurrentAnim.Frames.empty()) {
    Texture var8 = ((IsoDirectionFrame)this.sprite.CurrentAnim.Frames.get(0)).getTexture(this.dir);
         if (var8 != nullptr) {
            if (var8.getName().startsWith("Item_")) {
    float var9 = var8.getWidthOrig() * this.sprite.def.getScaleX() / 2.0F;
    float var10 = var8.getHeightOrig() * this.sprite.def.getScaleY() * 3.0F / 4.0F;
               this.setAlphaAndTarget(1.0F);
               this.offsetX = 0.0F;
               this.offsetY = 0.0F;
               this.sx = 0.0F;
               this.sprite.render(this, var1 + 0.5F, var2 + 0.5F, var3, this.dir, this.offsetX + var9, this.offsetY + var10, var4, true);
            } else {
               this.offsetX = 32 * Core.TileScale;
               this.offsetY = 96 * Core.TileScale;
               this.sx = 0.0F;
               super.render(var1, var2, var3, var4, var5, var6, var7);
            }
         }
      }
   }

    void triggerExplosion(bool var1) {
      LuaEventManager.triggerEvent("OnThrowableExplode", this, this.square);
      if (var1) {
         if (this.getSensorRange() > 0) {
            this.square.setTrapPositionX(this.square.getX());
            this.square.setTrapPositionY(this.square.getY());
            this.square.setTrapPositionZ(this.square.getZ());
            this.square.drawCircleExplosion(this.getSensorRange(), this, ExplosionMode.Sensor);
         }
      } else {
         if (this.getExplosionSound() != nullptr) {
            this.playExplosionSound();
         }

         if (this.getNoiseRange() > 0) {
            WorldSoundManager.instance.addSound(nullptr, (int)this.getX(), (int)this.getY(), (int)this.getZ(), this.getNoiseRange(), 1);
         } else if (this.getExplosionSound() != nullptr) {
            WorldSoundManager.instance.addSound(nullptr, (int)this.getX(), (int)this.getY(), (int)this.getZ(), 50, 1);
         }

         if (this.getExplosionRange() > 0) {
            this.square.drawCircleExplosion(this.getExplosionRange(), this, ExplosionMode.Explosion);
         }

         if (this.getFireRange() > 0) {
            this.square.drawCircleExplosion(this.getFireRange(), this, ExplosionMode.Fire);
         }

         if (this.getSmokeRange() > 0) {
            this.square.drawCircleExplosion(this.getSmokeRange(), this, ExplosionMode.Smoke);
         }

         if (this.weapon == nullptr || !this.weapon.canBeReused()) {
            if (GameServer.bServer) {
               GameServer.RemoveItemFromMap(this);
            } else {
               this.removeFromWorld();
               this.removeFromSquare();
            }
         }
      }
   }

    BaseSoundEmitter getOrCreateEmitter() {
      if (this.getObjectIndex() == -1) {
    return nullptr;
      } else {
         if (this.emitter == nullptr) {
            this.emitter = IsoWorld.instance.getFreeEmitter(this.getX() + 0.5F, this.getY() + 0.5F, this.getZ());
            IsoWorld.instance.takeOwnershipOfEmitter(this.emitter);
         }

         return this.emitter;
      }
   }

    void playExplosionSound() {
      if (!StringUtils.isNullOrWhitespace(this.getExplosionSound())) {
         if (this.getObjectIndex() != -1) {
            if (this.getNoiseRange() > 0 && this.getNoiseDuration() > 0.0F) {
               this.noiseStartTime = (float)GameTime.getInstance().getWorldAgeHours();
            }

            if (!GameServer.bServer) {
               this.getOrCreateEmitter();
               if (!this.emitter.isPlaying(this.getExplosionSound())) {
                  this.emitter.playSoundImpl(this.getExplosionSound(), (IsoObject)nullptr);
               }
            }
         }
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.sensorRange = var1.getInt();
      this.firePower = var1.getInt();
      this.fireRange = var1.getInt();
      this.explosionPower = var1.getInt();
      this.explosionRange = var1.getInt();
      this.smokeRange = var1.getInt();
      this.noiseRange = var1.getInt();
      if (var2 >= 180) {
         this.noiseDuration = var1.getInt();
         this.noiseStartTime = var1.getFloat();
      }

      this.extraDamage = var1.getFloat();
      this.remoteControlID = var1.getInt();
      if (var2 >= 78) {
         this.timerBeforeExplosion = var1.getInt() * this.FPS;
         this.countDownSound = GameWindow.ReadStringUTF(var1);
         this.explosionSound = GameWindow.ReadStringUTF(var1);
         if ("bigExplosion" == this.explosionSound)) {
            this.explosionSound = "BigExplosion";
         }

         if ("smallExplosion" == this.explosionSound)) {
            this.explosionSound = "SmallExplosion";
         }

         if ("feedback" == this.explosionSound)) {
            this.explosionSound = "NoiseTrapExplosion";
         }
      }

      if (var2 >= 82) {
    bool var4 = var1.get() == 1;
         if (var4) {
    InventoryItem var5 = InventoryItem.loadItem(var1, var2);
            if (dynamic_cast<HandWeapon*>(var5) != nullptr) {
               this.weapon = (HandWeapon)var5;
               this.initSprite(this.weapon);
            }
         }
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.putInt(this.sensorRange);
      var1.putInt(this.firePower);
      var1.putInt(this.fireRange);
      var1.putInt(this.explosionPower);
      var1.putInt(this.explosionRange);
      var1.putInt(this.smokeRange);
      var1.putInt(this.noiseRange);
      var1.putInt(this.noiseDuration);
      var1.putFloat(this.noiseStartTime);
      var1.putFloat(this.extraDamage);
      var1.putInt(this.remoteControlID);
      var1.putInt(this.timerBeforeExplosion > 1 ? Math.max(this.timerBeforeExplosion / this.FPS, 1) : 0);
      GameWindow.WriteStringUTF(var1, this.countDownSound);
      GameWindow.WriteStringUTF(var1, this.explosionSound);
      if (this.weapon != nullptr) {
         var1.put((byte)1);
         this.weapon.saveWithSize(var1, false);
      } else {
         var1.put((byte)0);
      }
   }

    void addToWorld() {
      this.getCell().addToProcessIsoObject(this);
   }

    void removeFromWorld() {
      if (this.emitter != nullptr) {
         if (this.noiseStartTime > 0.0F) {
            this.emitter.stopAll();
         }

         IsoWorld.instance.returnOwnershipOfEmitter(this.emitter);
         this.emitter = nullptr;
      }

      super.removeFromWorld();
   }

    int getTimerBeforeExplosion() {
      return this.timerBeforeExplosion;
   }

    void setTimerBeforeExplosion(int var1) {
      this.timerBeforeExplosion = var1;
   }

    int getSensorRange() {
      return this.sensorRange;
   }

    void setSensorRange(int var1) {
      this.sensorRange = var1;
   }

    int getFireRange() {
      return this.fireRange;
   }

    void setFireRange(int var1) {
      this.fireRange = var1;
   }

    int getFirePower() {
      return this.firePower;
   }

    void setFirePower(int var1) {
      this.firePower = var1;
   }

    int getExplosionPower() {
      return this.explosionPower;
   }

    void setExplosionPower(int var1) {
      this.explosionPower = var1;
   }

    int getNoiseDuration() {
      return this.noiseDuration;
   }

    void setNoiseDuration(int var1) {
      this.noiseDuration = var1;
   }

    int getNoiseRange() {
      return this.noiseRange;
   }

    void setNoiseRange(int var1) {
      this.noiseRange = var1;
   }

    int getExplosionRange() {
      return this.explosionRange;
   }

    void setExplosionRange(int var1) {
      this.explosionRange = var1;
   }

    int getSmokeRange() {
      return this.smokeRange;
   }

    void setSmokeRange(int var1) {
      this.smokeRange = var1;
   }

    float getExtraDamage() {
      return this.extraDamage;
   }

    void setExtraDamage(float var1) {
      this.extraDamage = var1;
   }

    std::string getObjectName() {
      return "IsoTrap";
   }

    int getRemoteControlID() {
      return this.remoteControlID;
   }

    void setRemoteControlID(int var1) {
      this.remoteControlID = var1;
   }

    std::string getCountDownSound() {
      return this.countDownSound;
   }

    void setCountDownSound(const std::string& var1) {
      this.countDownSound = var1;
   }

    std::string getExplosionSound() {
      return this.explosionSound;
   }

    void setExplosionSound(const std::string& var1) {
      this.explosionSound = var1;
   }

    InventoryItem getItem() {
      return this.weapon;
   }

    static void triggerRemote(IsoPlayer var0, int var1, int var2) {
    int var3 = (int)var0.getX();
    int var4 = (int)var0.getY();
    int var5 = (int)var0.getZ();
    int var6 = Math.max(var5 - var2 / 2, 0);
    int var7 = Math.min(var5 + var2 / 2, 8);
    IsoCell var8 = IsoWorld.instance.CurrentCell;

      for (int var9 = var6; var9 < var7; var9++) {
         for (int var10 = var4 - var2; var10 < var4 + var2; var10++) {
            for (int var11 = var3 - var2; var11 < var3 + var2; var11++) {
    IsoGridSquare var12 = var8.getGridSquare(var11, var10, var9);
               if (var12 != nullptr) {
                  for (int var13 = var12.getObjects().size() - 1; var13 >= 0; var13--) {
    IsoObject var14 = (IsoObject)var12.getObjects().get(var13);
                     if (dynamic_cast<IsoTrap*>(var14) != nullptr && ((IsoTrap)var14).getRemoteControlID() == var1) {
                        ((IsoTrap)var14).triggerExplosion(false);
                     }
                  }
               }
            }
         }
      }
   }

    bool isInstantExplosion() {
      return this.instantExplosion;
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
