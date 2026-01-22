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
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoHeatSource.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
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


class IsoBarbecue : public IsoObject {
public:
    bool bHasPropaneTank = false;
    int FuelAmount = 0;
    bool bLit = false;
    bool bIsSmouldering = false;
    float LastUpdateTime = -1.0F;
    float MinuteAccumulator = 0.0F;
    int MinutesSinceExtinguished = -1;
    IsoSprite normalSprite = nullptr;
    IsoSprite noTankSprite = nullptr;
    IsoHeatSource heatSource;
    long soundInstance = 0L;
    static int SMOULDER_MINUTES = 10;

    public IsoBarbecue(IsoCell var1) {
      super(var1);
   }

    public IsoBarbecue(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      super(var1, var2, var3);
      this.container = std::make_shared<ItemContainer>("barbecue", var2, this);
      this.container.setExplored(true);
      if (isSpriteWithPropaneTank(this.sprite)) {
         this.bHasPropaneTank = true;
         this.FuelAmount = 1200;
    uint8_t var4 = 8;
         this.normalSprite = this.sprite;
         this.noTankSprite = IsoSprite.getSprite(IsoSpriteManager.instance, this.sprite, var4);
      } else if (isSpriteWithoutPropaneTank(this.sprite)) {
    uint8_t var5 = -8;
         this.normalSprite = IsoSprite.getSprite(IsoSpriteManager.instance, this.sprite, var5);
         this.noTankSprite = this.sprite;
      }
   }

    std::string getObjectName() {
      return "Barbecue";
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.bHasPropaneTank = var1.get() == 1;
      this.FuelAmount = var1.getInt();
      this.bLit = var1.get() == 1;
      this.LastUpdateTime = var1.getFloat();
      this.MinutesSinceExtinguished = var1.getInt();
      if (var1.get() == 1) {
         this.normalSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
      }

      if (var1.get() == 1) {
         this.noTankSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1.getInt());
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.put((byte)(this.bHasPropaneTank ? 1 : 0));
      var1.putInt(this.FuelAmount);
      var1.put((byte)(this.bLit ? 1 : 0));
      var1.putFloat(this.LastUpdateTime);
      var1.putInt(this.MinutesSinceExtinguished);
      if (this.normalSprite != nullptr) {
         var1.put((byte)1);
         var1.putInt(this.normalSprite.ID);
      } else {
         var1.put((byte)0);
      }

      if (this.noTankSprite != nullptr) {
         var1.put((byte)1);
         var1.putInt(this.noTankSprite.ID);
      } else {
         var1.put((byte)0);
      }
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

    bool hasPropaneTank() {
      return this.isPropaneBBQ() && this.bHasPropaneTank;
   }

    bool isPropaneBBQ() {
      return this.getSprite() != nullptr && this.getProperties().Is("propaneTank");
   }

    static bool isSpriteWithPropaneTank(IsoSprite var0) {
      if (var0 != nullptr && var0.getProperties().Is("propaneTank")) {
    uint8_t var1 = 8;
    IsoSprite var2 = IsoSprite.getSprite(IsoSpriteManager.instance, var0, var1);
         return var2 != nullptr && var2.getProperties().Is("propaneTank");
      } else {
    return false;
      }
   }

    static bool isSpriteWithoutPropaneTank(IsoSprite var0) {
      if (var0 != nullptr && var0.getProperties().Is("propaneTank")) {
    uint8_t var1 = -8;
    IsoSprite var2 = IsoSprite.getSprite(IsoSpriteManager.instance, var0, var1);
         return var2 != nullptr && var2.getProperties().Is("propaneTank");
      } else {
    return false;
      }
   }

    void setPropaneTank(InventoryItem var1) {
      if (var1.getFullType() == "Base.PropaneTank")) {
         this.bHasPropaneTank = true;
         this.FuelAmount = 1200;
         if (dynamic_cast<DrainableComboItem*>(var1) != nullptr) {
            this.FuelAmount = (int)(this.FuelAmount * ((DrainableComboItem)var1).getUsedDelta());
         }
      }
   }

    InventoryItem removePropaneTank() {
      if (!this.bHasPropaneTank) {
    return nullptr;
      } else {
         this.bHasPropaneTank = false;
         this.bLit = false;
    InventoryItem var1 = InventoryItemFactory.CreateItem("Base.PropaneTank");
         if (dynamic_cast<DrainableComboItem*>(var1) != nullptr) {
            ((DrainableComboItem)var1).setUsedDelta(this.getFuelAmount() / 1200.0F);
         }

         this.FuelAmount = 0;
    return var1;
      }
   }

    void setLit(bool var1) {
      this.bLit = var1;
   }

    bool isLit() {
      return this.bLit;
   }

    bool isSmouldering() {
      return this.bIsSmouldering;
   }

    void turnOn() {
      if (!this.isLit()) {
         this.setLit(true);
      }
   }

    void turnOff() {
      if (this.isLit()) {
         this.setLit(false);
      }
   }

    void toggle() {
      this.setLit(!this.isLit());
   }

    void extinguish() {
      if (this.isLit()) {
         this.setLit(false);
         if (this.hasFuel() && !this.isPropaneBBQ()) {
            this.MinutesSinceExtinguished = 0;
         }
      }
   }

    float getTemperature() {
      return this.isLit() ? 1.8F : 1.0F;
   }

    void updateSprite() {
      if (this.isPropaneBBQ()) {
         if (this.hasPropaneTank()) {
            this.sprite = this.normalSprite;
         } else {
            this.sprite = this.noTankSprite;
         }
      }
   }

    void updateHeatSource() {
      if (this.isLit()) {
         if (this.heatSource == nullptr) {
            this.heatSource = std::make_shared<IsoHeatSource>((int)this.getX(), (int)this.getY(), (int)this.getZ(), 3, 25);
            IsoWorld.instance.CurrentCell.addHeatSource(this.heatSource);
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

    std::string var1 = this.isPropaneBBQ() ? "BBQPropaneRunning" : "BBQRegularRunning";
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
    float var3 = (float)GameTime.getInstance().getWorldAgeHours();
         if (this.LastUpdateTime < 0.0F) {
            this.LastUpdateTime = var3;
         } else if (this.LastUpdateTime > var3) {
            this.LastUpdateTime = var3;
         }

         if (var3 > this.LastUpdateTime) {
            this.MinuteAccumulator = this.MinuteAccumulator + (var3 - this.LastUpdateTime) * 60.0F;
    int var4 = (int)Math.floor(this.MinuteAccumulator);
            if (var4 > 0) {
               if (this.isLit()) {
                  DebugLog.log(DebugType.Fireplace, "IsoBarbecue burned " + var4 + " minutes (" + this.getFuelAmount() + " remaining)");
                  this.useFuel(var4);
                  if (!this.hasFuel()) {
                     this.extinguish();
                  }
               } else if (this.MinutesSinceExtinguished != -1) {
    int var5 = Math.min(var4, SMOULDER_MINUTES - this.MinutesSinceExtinguished);
                  DebugLog.log(DebugType.Fireplace, "IsoBarbecue smoldered " + var5 + " minutes (" + this.getFuelAmount() + " remaining)");
                  this.MinutesSinceExtinguished += var4;
                  this.bIsSmouldering = true;
                  this.useFuel(var5);
                  if (!this.hasFuel() || this.MinutesSinceExtinguished >= SMOULDER_MINUTES) {
                     this.MinutesSinceExtinguished = -1;
                     this.bIsSmouldering = false;
                  }
               }

               this.MinuteAccumulator -= var4;
            }
         }

         this.LastUpdateTime = var3;
         if (GameServer.bServer) {
            if (var1 != this.hasFuel() || var2 != this.isLit()) {
               this.sendObjectChange("state");
            }

            return;
         }
      }

      this.updateSprite();
      this.updateHeatSource();
      if (!this.isLit() || this.AttachedAnimSprite != nullptr && !this.AttachedAnimSprite.empty()) {
         if (!this.isLit() && this.AttachedAnimSprite != nullptr && !this.AttachedAnimSprite.empty()) {
            this.RemoveAttachedAnims();
         }
      } else {
    ColorInfo var6 = std::make_shared<ColorInfo>(0.95F, 0.95F, 0.85F, 1.0F);
         this.AttachAnim("Smoke", "01", 4, IsoFireManager.SmokeAnimDelay, -14, 58, true, 0, false, 0.7F, var6);
         ((IsoSpriteInstance)this.AttachedAnimSprite.get(0)).alpha = ((IsoSpriteInstance)this.AttachedAnimSprite.get(0)).targetAlpha = 0.55F;
         ((IsoSpriteInstance)this.AttachedAnimSprite.get(0)).bCopyTargetAlpha = false;
      }

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

      this.updateSound();
   }

    void setSprite(IsoSprite var1) {
      if (isSpriteWithPropaneTank(var1)) {
    uint8_t var2 = 8;
         this.normalSprite = var1;
         this.noTankSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1, var2);
      } else if (isSpriteWithoutPropaneTank(var1)) {
    uint8_t var3 = -8;
         this.normalSprite = IsoSprite.getSprite(IsoSpriteManager.instance, var1, var3);
         this.noTankSprite = var1;
      }
   }

    void addToWorld() {
    IsoCell var1 = this.getCell();
      this.getCell().addToProcessIsoObject(this);
      this.container.addItemsToProcessItems();
   }

    void removeFromWorld() {
      if (this.heatSource != nullptr) {
         IsoWorld.instance.CurrentCell.removeHeatSource(this.heatSource);
         this.heatSource = nullptr;
      }

      super.removeFromWorld();
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.AttachedAnimSprite != nullptr) {
    int var8 = Core.TileScale;

         for (int var9 = 0; var9 < this.AttachedAnimSprite.size(); var9++) {
    IsoSprite var10 = ((IsoSpriteInstance)this.AttachedAnimSprite.get(var9)).parentSprite;
            var10.soffX = (short)(14 * var8);
            var10.soffY = (short)(-58 * var8);
            ((IsoSpriteInstance)this.AttachedAnimSprite.get(var9)).setScale(var8, var8);
         }
      }

      super.render(var1, var2, var3, var4, var5, var6, var7);
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      if ("state" == var1)) {
         var3.putInt(this.getFuelAmount());
         var3.put((byte)(this.isLit() ? 1 : 0));
         var3.put((byte)(this.hasPropaneTank() ? 1 : 0));
      }
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      if ("state" == var1)) {
         this.setFuelAmount(var2.getInt());
         this.setLit(var2.get() == 1);
         this.bHasPropaneTank = var2.get() == 1;
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
