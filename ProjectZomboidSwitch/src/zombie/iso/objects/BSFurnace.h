#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class BSFurnace : public IsoObject {
public:
    float heat = 0.0F;
    float heatDecrease = 0.005F;
    float heatIncrease = 0.001F;
    float fuelAmount = 0.0F;
    float fuelDecrease = 0.001F;
    bool fireStarted = false;
    IsoLightSource LightSource;
    std::string sSprite;
    std::string sLitSprite;

    public BSFurnace(IsoCell var1) {
      super(var1);
   }

    public BSFurnace(IsoCell var1, IsoGridSquare var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, IsoSpriteManager.instance.getSprite(var3));
      this.sSprite = var3;
      this.sLitSprite = var4;
      this.sprite = IsoSpriteManager.instance.getSprite(var3);
      this.square = var2;
      this.container = std::make_unique<ItemContainer>();
      this.container.setType("stonefurnace");
      this.container.setParent(this);
      var2.AddSpecialObject(this);
   }

    void update() {
      this.updateHeat();
      if (!GameClient.bClient) {
    DrainableComboItem var1 = nullptr;
    InventoryItem var2 = nullptr;

         for (int var3 = 0; var3 < this.getContainer().getItems().size(); var3++) {
    InventoryItem var4 = (InventoryItem)this.getContainer().getItems().get(var3);
            if (var4.getType() == "IronIngot") && ((DrainableComboItem)var4).getUsedDelta() < 1.0F) {
               var1 = (DrainableComboItem)var4;
            }

            if (var4.getMetalValue() > 0.0F) {
               if (this.getHeat() > 15.0F) {
                  if (var4.getItemHeat() < 2.0F) {
                     var4.setItemHeat(var4.getItemHeat() + 0.001F * (this.getHeat() / 100.0F) * GameTime.instance.getMultiplier());
                  } else {
                     var4.setMeltingTime(
                        var4.getMeltingTime()
                           + 0.1F * (this.getHeat() / 100.0F) * (1.0F + this.getMeltingSkill(var4) * 3 / 100.0F) * GameTime.instance.getMultiplier()
                     );
                  }

                  if (var4.getMeltingTime() == 100.0F) {
                     var2 = var4;
                  }
               } else {
                  var4.setItemHeat(var4.getItemHeat() - 0.001F * (this.getHeat() / 100.0F) * GameTime.instance.getMultiplier());
                  var4.setMeltingTime(var4.getMeltingTime() - 0.1F * (this.getHeat() / 100.0F) * GameTime.instance.getMultiplier());
               }
            }
         }

         if (var2 != nullptr) {
            if (var2.getWorker() != nullptr && !var2.getWorker().empty()) {
               for (int var6 = 0; var6 < IsoPlayer.numPlayers; var6++) {
    IsoPlayer var8 = IsoPlayer.players[var6];
                  if (var8 != nullptr && !var8.isDead() && var2.getWorker() == var8.getFullName())) {
                     break;
                  }
               }
            }

    float var7 = var2.getMetalValue() + (var2.getMetalValue() * (1.0F + this.getMeltingSkill(var2) * 3 / 100.0F) - var2.getMetalValue());
            if (var1 != nullptr) {
               if (var7 + var1.getUsedDelta() / var1.getUseDelta() > 1.0F / var1.getUseDelta()) {
                  var7 -= 1.0F / var1.getUseDelta() - var1.getUsedDelta() / var1.getUseDelta();
                  var1.setUsedDelta(1.0F);
                  var1 = (DrainableComboItem)InventoryItemFactory.CreateItem("Base.IronIngot");
                  var1.setUsedDelta(0.0F);
                  this.getContainer().addItem(var1);
               }
            } else {
               var1 = (DrainableComboItem)InventoryItemFactory.CreateItem("Base.IronIngot");
               var1.setUsedDelta(0.0F);
               this.getContainer().addItem(var1);
            }

    float var9 = 0.0F;
    float var5 = var7;

            while (var9 < var5) {
               if (var1.getUsedDelta() + var7 * var1.getUseDelta() <= 1.0F) {
                  var1.setUsedDelta(var1.getUsedDelta() + var7 * var1.getUseDelta());
                  var9 += var7;
               } else {
                  var7 -= 1.0F / var1.getUseDelta();
                  var9 += 1.0F / var1.getUseDelta();
                  var1.setUsedDelta(1.0F);
                  var1 = (DrainableComboItem)InventoryItemFactory.CreateItem("Base.IronIngot");
                  var1.setUsedDelta(0.0F);
                  this.getContainer().addItem(var1);
               }
            }

            this.getContainer().Remove(var2);
         }
      }
   }

    void updateHeat() {
      if (!this.isFireStarted()) {
         this.heat = this.heat - this.heatDecrease * GameTime.instance.getMultiplier();
      } else if (this.getFuelAmount() == 0.0F) {
         this.setFireStarted(false);
      } else {
         this.fuelAmount = this.fuelAmount - this.fuelDecrease * (0.2F + this.heatIncrease / 80.0F) * GameTime.instance.getMultiplier();
         if (this.getHeat() < 20.0F) {
            this.heat = this.heat + this.heatIncrease * GameTime.instance.getMultiplier();
         }

         this.heat = this.heat - this.heatDecrease * 0.05F * GameTime.instance.getMultiplier();
      }

      if (this.heat < 0.0F) {
         this.heat = 0.0F;
      }

      if (this.fuelAmount < 0.0F) {
         this.fuelAmount = 0.0F;
      }
   }

    int getMeltingSkill(InventoryItem var1) {
      if (var1.getWorker() != nullptr && !var1.getWorker().empty()) {
         for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
            if (var3 != nullptr && !var3.isDead() && var1.getWorker() == var3.getFullName())) {
               return var3.getPerkLevel(Perks.Melting);
            }
         }
      }

    return 0;
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.fireStarted = var1.get() == 1;
      this.heat = var1.getFloat();
      this.fuelAmount = var1.getFloat();
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.put((byte)(this.isFireStarted() ? 1 : 0));
      var1.putFloat(this.getHeat());
      var1.putFloat(this.getFuelAmount());
   }

    std::string getObjectName() {
      return "StoneFurnace";
   }

    float getHeat() {
      return this.heat;
   }

    void setHeat(float var1) {
      if (var1 > 100.0F) {
         var1 = 100.0F;
      }

      if (var1 < 0.0F) {
         var1 = 0.0F;
      }

      this.heat = var1;
   }

    bool isFireStarted() {
      return this.fireStarted;
   }

    void updateLight() {
      if (this.fireStarted && this.LightSource == nullptr) {
         this.LightSource = std::make_shared<IsoLightSource>(this.square.getX(), this.square.getY(), this.square.getZ(), 0.61F, 0.165F, 0.0F, 7);
         IsoWorld.instance.CurrentCell.addLamppost(this.LightSource);
      } else if (this.LightSource != nullptr) {
         IsoWorld.instance.CurrentCell.removeLamppost(this.LightSource);
         this.LightSource = nullptr;
      }
   }

    void setFireStarted(bool var1) {
      this.fireStarted = var1;
      this.updateLight();
      this.syncFurnace();
   }

    void syncFurnace() {
      if (GameServer.bServer) {
         GameServer.sendFuranceChange(this, nullptr);
      } else if (GameClient.bClient) {
         GameClient.sendFurnaceChange(this);
      }
   }

    float getFuelAmount() {
      return this.fuelAmount;
   }

    void setFuelAmount(float var1) {
      if (var1 > 100.0F) {
         var1 = 100.0F;
      }

      if (var1 < 0.0F) {
         var1 = 0.0F;
      }

      this.fuelAmount = var1;
   }

    void addFuel(float var1) {
      this.setFuelAmount(this.getFuelAmount() + var1);
   }

    void addToWorld() {
      IsoWorld.instance.getCell().addToProcessIsoObject(this);
   }

    void removeFromWorld() {
      if (this.emitter != nullptr) {
         this.emitter.stopAll();
         IsoWorld.instance.returnOwnershipOfEmitter(this.emitter);
         this.emitter = nullptr;
      }

      super.removeFromWorld();
   }

    float getFuelDecrease() {
      return this.fuelDecrease;
   }

    void setFuelDecrease(float var1) {
      this.fuelDecrease = var1;
   }

    float getHeatDecrease() {
      return this.heatDecrease;
   }

    void setHeatDecrease(float var1) {
      this.heatDecrease = var1;
   }

    float getHeatIncrease() {
      return this.heatIncrease;
   }

    void setHeatIncrease(float var1) {
      this.heatIncrease = var1;
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
