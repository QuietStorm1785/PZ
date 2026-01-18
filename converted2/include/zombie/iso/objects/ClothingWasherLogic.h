#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/interfaces/IClothingWasherDryerLogic.h"
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

class ClothingWasherLogic {
public:
  const IsoObject m_object;
  bool bActivated;
  long soundInstance = -1L;
  float lastUpdate = -1.0F;
  bool cycleFinished = false;
  float startTime = 0.0F;
  float cycleLengthMinutes = 90.0F;
  bool alreadyExecuted = false;

public
  ClothingWasherLogic(IsoObject object) { this.m_object = object; }

  IsoObject getObject() { return this.m_object; }

  void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
    this.bActivated = input.get() == 1;
    this.lastUpdate = input.getFloat();
  }

  void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
    output.put((byte)(this.isActivated() ? 1 : 0));
    output.putFloat(this.lastUpdate);
  }

  void update() {
    if (this.getObject().getObjectIndex() != -1) {
      if (!this.getContainer().isPowered()) {
        this.setActivated(false);
      }

      this.updateSound();
      this.cycleFinished();
      if (GameClient.bClient) {
      }

      if (this.getObject().getWaterAmount() <= 0) {
        this.setActivated(false);
      }

      if (!this.isActivated()) {
        this.lastUpdate = -1.0F;
      } else {
        float float0 = (float)GameTime.getInstance().getWorldAgeHours();
        if (this.lastUpdate < 0.0F) {
          this.lastUpdate = float0;
        } else if (this.lastUpdate > float0) {
          this.lastUpdate = float0;
        }

        float float1 = float0 - this.lastUpdate;
        int int0 = (int)(float1 * 60.0F);
        if (int0 >= 1) {
          this.lastUpdate = float0;
          this.getObject().useWater(1 * int0);

          for (int int1 = 0; int1 < this.getContainer().getItems().size();
               int1++) {
            InventoryItem item = this.getContainer().getItems().get(int1);
            if (item instanceof Clothing clothing) {
              float float2 = clothing.getBloodlevel();
              if (float2 > 0.0F) {
                this.removeBlood(clothing, int0 * 2);
              }

              float float3 = clothing.getDirtyness();
              if (float3 > 0.0F) {
                this.removeDirt(clothing, int0 * 2);
              }

              clothing.setWetness(100.0F);
            }
          }
        }
      }
    }
  }

  void removeBlood(Clothing clothing, float float1) {
    ItemVisual itemVisual = clothing.getVisual();
    if (itemVisual != nullptr) {
      for (int int0 = 0; int0 < BloodBodyPartType.MAX.index(); int0++) {
        BloodBodyPartType bloodBodyPartType = BloodBodyPartType.FromIndex(int0);
        float float0 = itemVisual.getBlood(bloodBodyPartType);
        if (float0 > 0.0F) {
          itemVisual.setBlood(bloodBodyPartType, float0 - float1 / 100.0F);
        }
      }

      BloodClothingType.calcTotalBloodLevel(clothing);
    }
  }

  void removeDirt(Clothing clothing, float float1) {
    ItemVisual itemVisual = clothing.getVisual();
    if (itemVisual != nullptr) {
      for (int int0 = 0; int0 < BloodBodyPartType.MAX.index(); int0++) {
        BloodBodyPartType bloodBodyPartType = BloodBodyPartType.FromIndex(int0);
        float float0 = itemVisual.getDirt(bloodBodyPartType);
        if (float0 > 0.0F) {
          itemVisual.setDirt(bloodBodyPartType, float0 - float1 / 100.0F);
        }
      }

      BloodClothingType.calcTotalDirtLevel(clothing);
    }
  }

  void saveChange(const std::string &change, KahluaTable tbl, ByteBuffer bb) {
    if ("washer.state" == change)) {
            bb.put((byte)(this.isActivated() ? 1 : 0));
        }
  }

  void loadChange(const std::string &change, ByteBuffer bb) {
    if ("washer.state" == change)) {
            this.setActivated(bb.get() == 1);
        }
  }

  ItemContainer getContainer() {
    return this.getObject().getContainerByType("clothingwasher");
  }

  void updateSound() {
    if (this.isActivated()) {
      if (!GameServer.bServer) {
        if (this.getObject().emitter != nullptr &&
            this.getObject().emitter.isPlaying("ClothingWasherFinished")) {
          this.getObject().emitter.stopOrTriggerSoundByName(
              "ClothingWasherFinished");
        }

        if (this.soundInstance == -1L) {
          this.getObject().emitter = IsoWorld.instance.getFreeEmitter(
              this.getObject().getX() + 0.5F, this.getObject().getY() + 0.5F,
              (int)this.getObject().getZ());
          IsoWorld.instance.setEmitterOwner(this.getObject().emitter,
                                            this.getObject());
          this.soundInstance = this.getObject().emitter.playSoundLoopedImpl(
              "ClothingWasherRunning");
        }
      }

      if (!GameClient.bClient) {
        WorldSoundManager.instance.addSoundRepeating(
            this, this.getObject().square.x, this.getObject().square.y,
            this.getObject().square.z, 10, 10, false);
      }
    } else if (this.soundInstance != -1L) {
      this.getObject().emitter.stopOrTriggerSound(this.soundInstance);
      this.soundInstance = -1L;
      if (this.cycleFinished) {
        this.cycleFinished = false;
        this.getObject().emitter.playSoundImpl("ClothingWasherFinished",
                                               this.getObject());
      }
    }
  }

  bool isItemAllowedInContainer(ItemContainer container, InventoryItem item) {
    return container != this.getContainer() ? false : !this.isActivated();
  }

  bool isRemoveItemAllowedFromContainer(ItemContainer container,
                                        InventoryItem item) {
    return container != this.getContainer()
               ? false
               : container.isEmpty() || !this.isActivated();
  }

  bool cycleFinished() {
    if (this.isActivated()) {
      if (!this.alreadyExecuted) {
        this.startTime = (float)GameTime.getInstance().getWorldAgeHours();
        this.alreadyExecuted = true;
      }

      float float0 =
          (float)GameTime.getInstance().getWorldAgeHours() - this.startTime;
      int int0 = (int)(float0 * 60.0F);
      if (int0 < this.cycleLengthMinutes) {
        return false;
      }

      this.cycleFinished = true;
      this.setActivated(false);
    }

    return true;
  }

  bool isActivated() { return this.bActivated; }

  void setActivated(bool activated) {
    bool boolean0 = activated != this.bActivated;
    this.bActivated = activated;
    this.alreadyExecuted = false;
    if (boolean0) {
      Thread thread = Thread.currentThread();
      if (thread == GameWindow.GameThread || thread == GameServer.MainThread) {
        IsoGenerator.updateGenerator(this.getObject().getSquare());
      }
    }
  }

  void switchModeOn() {}

  void switchModeOff() {
    this.setActivated(false);
    this.updateSound();
    this.cycleFinished = false;
  }
}
} // namespace objects
} // namespace iso
} // namespace zombie
