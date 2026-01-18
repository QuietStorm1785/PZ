#pragma once
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/skills/PerkFactory.h"
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
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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

public
  BSFurnace(IsoCell cell) { super(cell); }

public
  BSFurnace(IsoCell cell, IsoGridSquare square, const std::string &string0,
            const std::string &string1) {
    super(cell, square, IsoSpriteManager.instance.getSprite(string0));
    this.sSprite = string0;
    this.sLitSprite = string1;
    this.sprite = IsoSpriteManager.instance.getSprite(string0);
    this.square = square;
    this.container = std::make_unique<ItemContainer>();
    this.container.setType("stonefurnace");
    this.container.setParent(this);
    square.AddSpecialObject(this);
  }

  void update() {
    this.updateHeat();
    if (!GameClient.bClient) {
      DrainableComboItem drainableComboItem = null;
      InventoryItem item0 = null;

      for (int int0 = 0; int0 < this.getContainer().getItems().size(); int0++) {
        InventoryItem item1 = this.getContainer().getItems().get(int0);
        if (item1.getType() == "IronIngot") && ((DrainableComboItem)item1).getUsedDelta() < 1.0F) {
            drainableComboItem = (DrainableComboItem)item1;
          }

        if (item1.getMetalValue() > 0.0F) {
          if (this.getHeat() > 15.0F) {
            if (item1.getItemHeat() < 2.0F) {
              item1.setItemHeat(item1.getItemHeat() +
                                0.001F * (this.getHeat() / 100.0F) *
                                    GameTime.instance.getMultiplier());
            } else {
              item1.setMeltingTime(
                  item1.getMeltingTime() +
                  0.1F * (this.getHeat() / 100.0F) *
                      (1.0F + this.getMeltingSkill(item1) * 3 / 100.0F) *
                      GameTime.instance.getMultiplier());
            }

            if (item1.getMeltingTime() == 100.0F) {
              item0 = item1;
            }
          } else {
            item1.setItemHeat(item1.getItemHeat() -
                              0.001F * (this.getHeat() / 100.0F) *
                                  GameTime.instance.getMultiplier());
            item1.setMeltingTime(item1.getMeltingTime() -
                                 0.1F * (this.getHeat() / 100.0F) *
                                     GameTime.instance.getMultiplier());
          }
        }
      }

      if (item0 != nullptr) {
        if (item0.getWorker() != nullptr && !item0.getWorker().isEmpty()) {
          for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
            IsoPlayer player = IsoPlayer.players[int1];
            if (player != nullptr && !player.isDead() &&
                item0.getWorker() == player.getFullName())) {
                            break;
                        }
          }
        }

        float float0 = item0.getMetalValue() +
                       (item0.getMetalValue() *
                            (1.0F + this.getMeltingSkill(item0) * 3 / 100.0F) -
                        item0.getMetalValue());
        if (drainableComboItem != nullptr) {
          if (float0 + drainableComboItem.getUsedDelta() /
                           drainableComboItem.getUseDelta() >
              1.0F / drainableComboItem.getUseDelta()) {
            float0 -= 1.0F / drainableComboItem.getUseDelta() -
                      drainableComboItem.getUsedDelta() /
                          drainableComboItem.getUseDelta();
            drainableComboItem.setUsedDelta(1.0F);
            drainableComboItem =
                (DrainableComboItem)InventoryItemFactory.CreateItem(
                    "Base.IronIngot");
            drainableComboItem.setUsedDelta(0.0F);
            this.getContainer().addItem(drainableComboItem);
          }
        } else {
          drainableComboItem =
              (DrainableComboItem)InventoryItemFactory.CreateItem(
                  "Base.IronIngot");
          drainableComboItem.setUsedDelta(0.0F);
          this.getContainer().addItem(drainableComboItem);
        }

        float float1 = 0.0F;
        float float2 = float0;

        while (float1 < float2) {
          if (drainableComboItem.getUsedDelta() +
                  float0 * drainableComboItem.getUseDelta() <=
              1.0F) {
            drainableComboItem.setUsedDelta(
                drainableComboItem.getUsedDelta() +
                float0 * drainableComboItem.getUseDelta());
            float1 += float0;
          } else {
            float0 -= 1.0F / drainableComboItem.getUseDelta();
            float1 += 1.0F / drainableComboItem.getUseDelta();
            drainableComboItem.setUsedDelta(1.0F);
            drainableComboItem =
                (DrainableComboItem)InventoryItemFactory.CreateItem(
                    "Base.IronIngot");
            drainableComboItem.setUsedDelta(0.0F);
            this.getContainer().addItem(drainableComboItem);
          }
        }

        this.getContainer().Remove(item0);
      }
    }
  }

  void updateHeat() {
    if (!this.isFireStarted()) {
      this.heat =
          this.heat - this.heatDecrease * GameTime.instance.getMultiplier();
    } else if (this.getFuelAmount() == 0.0F) {
      this.setFireStarted(false);
    } else {
      this.fuelAmount = this.fuelAmount -
                        this.fuelDecrease * (0.2F + this.heatIncrease / 80.0F) *
                            GameTime.instance.getMultiplier();
      if (this.getHeat() < 20.0F) {
        this.heat =
            this.heat + this.heatIncrease * GameTime.instance.getMultiplier();
      }

      this.heat = this.heat -
                  this.heatDecrease * 0.05F * GameTime.instance.getMultiplier();
    }

    if (this.heat < 0.0F) {
      this.heat = 0.0F;
    }

    if (this.fuelAmount < 0.0F) {
      this.fuelAmount = 0.0F;
    }
  }

  int getMeltingSkill(InventoryItem item) {
    if (item.getWorker() != nullptr && !item.getWorker().isEmpty()) {
      for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
        IsoPlayer player = IsoPlayer.players[int0];
        if (player != nullptr && !player.isDead() &&
            item.getWorker() == player.getFullName())) {
                    return player.getPerkLevel(PerkFactory.Perks.Melting);
                }
      }
    }

    return 0;
  }

  void load(ByteBuffer byteBuffer, int int0, bool boolean0) {
    super.load(byteBuffer, int0, boolean0);
    this.fireStarted = byteBuffer.get() == 1;
    this.heat = byteBuffer.getFloat();
    this.fuelAmount = byteBuffer.getFloat();
  }

  void save(ByteBuffer byteBuffer, bool boolean0) {
    super.save(byteBuffer, boolean0);
    byteBuffer.put((byte)(this.isFireStarted() ? 1 : 0));
    byteBuffer.putFloat(this.getHeat());
    byteBuffer.putFloat(this.getFuelAmount());
  }

  std::string getObjectName() { return "StoneFurnace"; }

  float getHeat() { return this.heat; }

  void setHeat(float float0) {
    if (float0 > 100.0F) {
      float0 = 100.0F;
    }

    if (float0 < 0.0F) {
      float0 = 0.0F;
    }

    this.heat = float0;
  }

  bool isFireStarted() { return this.fireStarted; }

  void updateLight() {
    if (this.fireStarted && this.LightSource == nullptr) {
      this.LightSource =
          new IsoLightSource(this.square.getX(), this.square.getY(),
                             this.square.getZ(), 0.61F, 0.165F, 0.0F, 7);
      IsoWorld.instance.CurrentCell.addLamppost(this.LightSource);
    } else if (this.LightSource != nullptr) {
      IsoWorld.instance.CurrentCell.removeLamppost(this.LightSource);
      this.LightSource = nullptr;
    }
  }

  void setFireStarted(bool boolean0) {
    this.fireStarted = boolean0;
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

  float getFuelAmount() { return this.fuelAmount; }

  void setFuelAmount(float float0) {
    if (float0 > 100.0F) {
      float0 = 100.0F;
    }

    if (float0 < 0.0F) {
      float0 = 0.0F;
    }

    this.fuelAmount = float0;
  }

  void addFuel(float float0) {
    this.setFuelAmount(this.getFuelAmount() + float0);
  }

  void addToWorld() { IsoWorld.instance.getCell().addToProcessIsoObject(this); }

  void removeFromWorld() {
    if (this.emitter != nullptr) {
      this.emitter.stopAll();
      IsoWorld.instance.returnOwnershipOfEmitter(this.emitter);
      this.emitter = nullptr;
    }

    super.removeFromWorld();
  }

  float getFuelDecrease() { return this.fuelDecrease; }

  void setFuelDecrease(float float0) { this.fuelDecrease = float0; }

  float getHeatDecrease() { return this.heatDecrease; }

  void setHeatDecrease(float float0) { this.heatDecrease = float0; }

  float getHeatIncrease() { return this.heatIncrease; }

  void setHeatIncrease(float float0) { this.heatIncrease = float0; }
}
} // namespace objects
} // namespace iso
} // namespace zombie
