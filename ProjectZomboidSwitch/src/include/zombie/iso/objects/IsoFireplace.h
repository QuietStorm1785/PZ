#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/core/Core.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoHeatSource.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoFireplace : public IsoObject {
public:
    int FuelAmount = 0;
    bool bLit = false;
    bool bSmouldering = false;
    float LastUpdateTime = -1.0F;
    float MinuteAccumulator = 0.0F;
    int MinutesSinceExtinguished = -1;
    IsoSprite FuelSprite = nullptr;
    int FuelSpriteIndex = -1;
    int FireSpriteIndex = -1;
    IsoLightSource LightSource = nullptr;
    IsoHeatSource heatSource = nullptr;
    long soundInstance = 0L;
    static int SMOULDER_MINUTES = 10;

    public IsoFireplace(IsoCell var1) {
      super(var1);
   }

    public IsoFireplace(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      super(var1, var2, var3);
    std::string var4 = var3 != nullptr && var3.getProperties().Is(IsoFlagType.container) ? var3.getProperties().Val("container") : "fireplace";
      this.container = std::make_shared<ItemContainer>(var4, var2, this);
      this.container.setExplored(true);
   }

    std::string getObjectName() {
      return "Fireplace";
   }

    Vector2 getFacingPosition(Vector2 var1) {
      if (this.square == nullptr) {
         return var1.set(0.0F, 0.0F);
      } else {
         return this.getProperties() != nullptr && this.getProperties().Is(IsoFlagType.collideN)
            ? var1.set(this.getX() + 0.5F, this.getY())
            : var1.set(this.getX(), this.getY() + 0.5F);
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.FuelAmount = var1.getInt();
      this.bLit = var1.get() == 1;
      this.LastUpdateTime = var1.getFloat();
      this.MinutesSinceExtinguished = var1.getInt();
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.putInt(this.FuelAmount);
      var1.put((byte)(this.bLit ? 1 : 0));
      var1.putFloat(this.LastUpdateTime);
      var1.putInt(this.MinutesSinceExtinguished);
   }

    void setFuelAmount(int var1) {
      var1 = Math.max(0, var1);
    int var2 = this.getFuelAmount();
      if (var1 != var2) {
         this.FuelAmount = var1;
      }
   }

    int getFuelAmount() {
      return this.FuelAmount;
   }

    void addFuel(int var1) {
      this.setFuelAmount(this.getFuelAmount() + var1);
   }

    int useFuel(int var1) {
    int var2 = this.getFuelAmount();
    int var3 = 0;
      if (var2 >= var1) {
         var3 = var1;
      } else {
         var3 = var2;
      }

      this.setFuelAmount(var2 - var3);
    return var3;
   }

    bool hasFuel() {
      return this.getFuelAmount() > 0;
   }

    void setLit(bool var1) {
      this.bLit = var1;
   }

    bool isLit() {
      return this.bLit;
   }

    bool isSmouldering() {
      return this.bSmouldering;
   }

    void extinguish() {
      if (this.isLit()) {
         this.setLit(false);
         if (this.hasFuel()) {
            this.MinutesSinceExtinguished = 0;
         }
      }
   }

    float getTemperature() {
      return this.isLit() ? 1.8F : 1.0F;
   }

    void updateFuelSprite() {
      if (this.container == nullptr || !"woodstove" == this.container.getType())) {
         if (this.hasFuel()) {
            if (this.FuelSprite == nullptr) {
               this.FuelSprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
    Texture var1 = this.FuelSprite.LoadFrameExplicit("Item_Logs");
            }

            if (this.FuelSpriteIndex == -1) {
               DebugLog.log(DebugType.Fireplace, "fireplace: added fuel sprite");
               this.FuelSpriteIndex = this.AttachedAnimSprite != nullptr ? this.AttachedAnimSprite.size() : 0;
               if (this.getProperties() != nullptr && this.getProperties().Is(IsoFlagType.collideW)) {
                  this.AttachExistingAnim(this.FuelSprite, -10 * Core.TileScale, -90 * Core.TileScale, false, 0, false, 0.0F);
               } else {
                  this.AttachExistingAnim(this.FuelSprite, -35 * Core.TileScale, -90 * Core.TileScale, false, 0, false, 0.0F);
               }

               if (Core.TileScale == 1) {
                  ((IsoSpriteInstance)this.AttachedAnimSprite.get(this.FuelSpriteIndex)).setScale(0.5F, 0.5F);
               }
            }
         } else if (this.FuelSpriteIndex != -1) {
            DebugLog.log(DebugType.Fireplace, "fireplace: removed fuel sprite");
            this.AttachedAnimSprite.remove(this.FuelSpriteIndex);
            if (this.FireSpriteIndex > this.FuelSpriteIndex) {
               this.FireSpriteIndex--;
            }

            this.FuelSpriteIndex = -1;
         }
      }
   }

    void updateFireSprite() {
      if (this.container == nullptr || !"woodstove" == this.container.getType())) {
         if (this.isLit()) {
            if (this.FireSpriteIndex == -1) {
               DebugLog.log(DebugType.Fireplace, "fireplace: added fire sprite");
               this.FireSpriteIndex = this.AttachedAnimSprite != nullptr ? this.AttachedAnimSprite.size() : 0;
               if (this.getProperties() != nullptr && this.getProperties().Is(IsoFlagType.collideW)) {
                  this.AttachAnim(
                     "Fire",
                     "01",
                     4,
                     IsoFireManager.FireAnimDelay,
                     -11 * Core.TileScale,
                     -84 * Core.TileScale,
                     true,
                     0,
                     false,
                     0.7F,
                     IsoFireManager.FireTintMod
                  );
               } else {
                  this.AttachAnim(
                     "Fire",
                     "01",
                     4,
                     IsoFireManager.FireAnimDelay,
                     -35 * Core.TileScale,
                     -84 * Core.TileScale,
                     true,
                     0,
                     false,
                     0.7F,
                     IsoFireManager.FireTintMod
                  );
               }

               if (Core.TileScale == 1) {
                  ((IsoSpriteInstance)this.AttachedAnimSprite.get(this.FireSpriteIndex)).setScale(0.5F, 0.5F);
               }
            }
         } else if (this.FireSpriteIndex != -1) {
            DebugLog.log(DebugType.Fireplace, "fireplace: removed fire sprite");
            this.AttachedAnimSprite.remove(this.FireSpriteIndex);
            if (this.FuelSpriteIndex > this.FireSpriteIndex) {
               this.FuelSpriteIndex--;
            }

            this.FireSpriteIndex = -1;
         }
      }
   }

    int calcLightRadius() {
      return (int)GameTime.instance.Lerp(1.0F, 8.0F, Math.min(this.getFuelAmount(), 60) / 60.0F);
   }

    void updateLightSource() {
      if (this.isLit()) {
    int var1 = this.calcLightRadius();
         if (this.LightSource != nullptr && this.LightSource.getRadius() != var1) {
            this.LightSource.life = 0;
            this.LightSource = nullptr;
         }

         if (this.LightSource == nullptr) {
            this.LightSource = std::make_shared<IsoLightSource>(this.square.getX(), this.square.getY(), this.square.getZ(), 1.0F, 0.1F, 0.1F, var1);
            IsoWorld.instance.CurrentCell.addLamppost(this.LightSource);
            IsoGridSquare.RecalcLightTime = -1;
            GameTime.instance.lightSourceUpdate = 100.0F;
         }
      } else if (this.LightSource != nullptr) {
         IsoWorld.instance.CurrentCell.removeLamppost(this.LightSource);
         this.LightSource = nullptr;
      }
   }

    void updateHeatSource() {
      if (this.isLit()) {
    int var1 = this.calcLightRadius();
         if (this.heatSource == nullptr) {
            this.heatSource = std::make_shared<IsoHeatSource>((int)this.getX(), (int)this.getY(), (int)this.getZ(), var1, 35);
            IsoWorld.instance.CurrentCell.addHeatSource(this.heatSource);
         } else if (var1 != this.heatSource.getRadius()) {
            this.heatSource.setRadius(var1);
         }
      } else if (this.heatSource != nullptr) {
         IsoWorld.instance.CurrentCell.removeHeatSource(this.heatSource);
         this.heatSource = nullptr;
      }
   }

    void updateSound() {
      if (!GameServer.bServer) {
         if (this.isLit()) {
            if (this.emitter == nullptr) {
               this.emitter = IsoWorld.instance.getFreeEmitter(this.getX() + 0.5F, this.getY() + 0.5F, (int)this.getZ());
               IsoWorld.instance.setEmitterOwner(this.emitter, this);
            }

    std::string var1 = "FireplaceRunning";
            if (!this.emitter.isPlaying(var1)) {
               this.soundInstance = this.emitter.playSoundLoopedImpl(var1);
            }
         } else if (this.emitter != nullptr && this.soundInstance != 0L) {
            this.emitter.stopOrTriggerSound(this.soundInstance);
            this.emitter = nullptr;
            this.soundInstance = 0L;
         }
      }
   }

    void update() {
      if (!GameClient.bClient) {
    bool var1 = this.hasFuel();
    bool var2 = this.isLit();
    int var3 = this.calcLightRadius();
    float var4 = (float)GameTime.getInstance().getWorldAgeHours();
         if (this.LastUpdateTime < 0.0F) {
            this.LastUpdateTime = var4;
         } else if (this.LastUpdateTime > var4) {
            this.LastUpdateTime = var4;
         }

         if (var4 > this.LastUpdateTime) {
            this.MinuteAccumulator = this.MinuteAccumulator + (var4 - this.LastUpdateTime) * 60.0F;
    int var5 = (int)Math.floor(this.MinuteAccumulator);
            if (var5 > 0) {
               if (this.isLit()) {
                  DebugLog.log(DebugType.Fireplace, "IsoFireplace burned " + var5 + " minutes (" + this.getFuelAmount() + " remaining)");
                  this.useFuel(var5);
                  if (!this.hasFuel()) {
                     this.extinguish();
                  }
               } else if (this.MinutesSinceExtinguished != -1) {
    int var6 = Math.min(var5, SMOULDER_MINUTES - this.MinutesSinceExtinguished);
                  DebugLog.log(DebugType.Fireplace, "IsoFireplace smoldered " + var6 + " minutes (" + this.getFuelAmount() + " remaining)");
                  this.MinutesSinceExtinguished += var5;
                  this.useFuel(var6);
                  this.bSmouldering = true;
                  if (!this.hasFuel() || this.MinutesSinceExtinguished >= SMOULDER_MINUTES) {
                     this.MinutesSinceExtinguished = -1;
                     this.bSmouldering = false;
                  }
               }

               this.MinuteAccumulator -= var5;
            }
         }

         this.LastUpdateTime = var4;
         if (GameServer.bServer) {
            if (var1 != this.hasFuel() || var2 != this.isLit() || var3 != this.calcLightRadius()) {
               this.sendObjectChange("state");
            }

            return;
         }
      }

      this.updateFuelSprite();
      this.updateFireSprite();
      this.updateLightSource();
      this.updateHeatSource();
      this.updateSound();
      if (this.AttachedAnimSprite != nullptr && !this.AttachedAnimSprite.empty()) {
    int var7 = this.AttachedAnimSprite.size();

         for (int var8 = 0; var8 < var7; var8++) {
    IsoSpriteInstance var9 = (IsoSpriteInstance)this.AttachedAnimSprite.get(var8);
    IsoSprite var10 = var9.parentSprite;
            var9.update();
    float var11 = GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F;
            var9.Frame = var9.Frame + var9.AnimFrameIncrease * var11;
            if ((int)var9.Frame >= var10.CurrentAnim.Frames.size() && var10.Loop && var9.Looped) {
               var9.Frame = 0.0F;
            }
         }
      }
   }

    void addToWorld() {
    IsoCell var1 = this.getCell();
      var1.addToProcessIsoObject(this);
      this.container.addItemsToProcessItems();
   }

    void removeFromWorld() {
      if (this.LightSource != nullptr) {
         IsoWorld.instance.CurrentCell.removeLamppost(this.LightSource);
         this.LightSource = nullptr;
      }

      if (this.heatSource != nullptr) {
         IsoWorld.instance.CurrentCell.removeHeatSource(this.heatSource);
         this.heatSource = nullptr;
      }

      super.removeFromWorld();
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      super.render(var1, var2, var3, var4, false, var6, var7);
      if (this.AttachedAnimSprite != nullptr) {
         for (int var8 = 0; var8 < this.AttachedAnimSprite.size(); var8++) {
    IsoSpriteInstance var9 = (IsoSpriteInstance)this.AttachedAnimSprite.get(var8);
            var9.getParentSprite().render(var9, this, var1, var2, var3, this.dir, this.offsetX, this.offsetY, var4, true);
         }
      }
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      if ("state" == var1)) {
         var3.putInt(this.getFuelAmount());
         var3.put((byte)(this.isLit() ? 1 : 0));
      }
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      if ("state" == var1)) {
         this.setFuelAmount(var2.getInt());
         this.setLit(var2.get() == 1);
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
