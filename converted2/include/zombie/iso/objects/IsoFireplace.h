#pragma once
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

class IsoFireplace : public IsoObject {
public:
  int FuelAmount = 0;
  bool bLit = false;
  bool bSmouldering = false;
  float LastUpdateTime = -1.0F;
  float MinuteAccumulator = 0.0F;
  int MinutesSinceExtinguished = -1;
  IsoSprite FuelSprite = null;
  int FuelSpriteIndex = -1;
  int FireSpriteIndex = -1;
  IsoLightSource LightSource = null;
  IsoHeatSource heatSource = null;
  long soundInstance = 0L;
  static int SMOULDER_MINUTES = 10;

public
  IsoFireplace(IsoCell cell) { super(cell); }

public
  IsoFireplace(IsoCell cell, IsoGridSquare sq, IsoSprite gid) {
    super(cell, sq, gid);
    std::string string =
        gid != null && gid.getProperties().Is(IsoFlagType.container)
            ? gid.getProperties().Val("container")
            : "fireplace";
    this.container = new ItemContainer(string, sq, this);
    this.container.setExplored(true);
  }

  std::string getObjectName() { return "Fireplace"; }

  Vector2 getFacingPosition(Vector2 pos) {
    if (this.square == nullptr) {
      return pos.set(0.0F, 0.0F);
    } else {
      return this.getProperties() != nullptr &&
                     this.getProperties().Is(IsoFlagType.collideN)
                 ? pos.set(this.getX() + 0.5F, this.getY())
                 : pos.set(this.getX(), this.getY() + 0.5F);
    }
  }

  void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
    super.load(input, WorldVersion, IS_DEBUG_SAVE);
    this.FuelAmount = input.getInt();
    this.bLit = input.get() == 1;
    this.LastUpdateTime = input.getFloat();
    this.MinutesSinceExtinguished = input.getInt();
  }

  void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
    super.save(output, IS_DEBUG_SAVE);
    output.putInt(this.FuelAmount);
    output.put((byte)(this.bLit ? 1 : 0));
    output.putFloat(this.LastUpdateTime);
    output.putInt(this.MinutesSinceExtinguished);
  }

  void setFuelAmount(int units) {
    units = Math.max(0, units);
    int int0 = this.getFuelAmount();
    if (units != int0) {
      this.FuelAmount = units;
    }
  }

  int getFuelAmount() { return this.FuelAmount; }

  void addFuel(int units) { this.setFuelAmount(this.getFuelAmount() + units); }

  int useFuel(int amount) {
    int int0 = this.getFuelAmount();
    int int1 = 0;
    if (int0 >= amount) {
      int1 = amount;
    } else {
      int1 = int0;
    }

    this.setFuelAmount(int0 - int1);
    return int1;
  }

  bool hasFuel() { return this.getFuelAmount() > 0; }

  void setLit(bool lit) { this.bLit = lit; }

  bool isLit() { return this.bLit; }

  bool isSmouldering() { return this.bSmouldering; }

  void extinguish() {
    if (this.isLit()) {
      this.setLit(false);
      if (this.hasFuel()) {
        this.MinutesSinceExtinguished = 0;
      }
    }
  }

  float getTemperature() { return this.isLit() ? 1.8F : 1.0F; }

  void updateFuelSprite() {
    if (this.container == nullptr || !"woodstove" == this.container.getType())) {
        if (this.hasFuel()) {
          if (this.FuelSprite == nullptr) {
            this.FuelSprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
            Texture texture = this.FuelSprite.LoadFrameExplicit("Item_Logs");
          }

          if (this.FuelSpriteIndex == -1) {
            DebugLog.log(DebugType.Fireplace, "fireplace: added fuel sprite");
            this.FuelSpriteIndex = this.AttachedAnimSprite != nullptr
                                       ? this.AttachedAnimSprite.size()
                                       : 0;
            if (this.getProperties() != nullptr &&
                this.getProperties().Is(IsoFlagType.collideW)) {
              this.AttachExistingAnim(this.FuelSprite, -10 * Core.TileScale,
                                      -90 * Core.TileScale, false, 0, false,
                                      0.0F);
            } else {
              this.AttachExistingAnim(this.FuelSprite, -35 * Core.TileScale,
                                      -90 * Core.TileScale, false, 0, false,
                                      0.0F);
            }

            if (Core.TileScale == 1) {
              this.AttachedAnimSprite.get(this.FuelSpriteIndex)
                  .setScale(0.5F, 0.5F);
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
            this.FireSpriteIndex = this.AttachedAnimSprite != nullptr
                                       ? this.AttachedAnimSprite.size()
                                       : 0;
            if (this.getProperties() != nullptr &&
                this.getProperties().Is(IsoFlagType.collideW)) {
              this.AttachAnim("Fire", "01", 4, IsoFireManager.FireAnimDelay,
                              -11 * Core.TileScale, -84 * Core.TileScale, true,
                              0, false, 0.7F, IsoFireManager.FireTintMod);
            } else {
              this.AttachAnim("Fire", "01", 4, IsoFireManager.FireAnimDelay,
                              -35 * Core.TileScale, -84 * Core.TileScale, true,
                              0, false, 0.7F, IsoFireManager.FireTintMod);
            }

            if (Core.TileScale == 1) {
              this.AttachedAnimSprite.get(this.FireSpriteIndex)
                  .setScale(0.5F, 0.5F);
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
    return (int)GameTime.instance.Lerp(
        1.0F, 8.0F, Math.min(this.getFuelAmount(), 60) / 60.0F);
  }

  void updateLightSource() {
    if (this.isLit()) {
      int int0 = this.calcLightRadius();
      if (this.LightSource != nullptr && this.LightSource.getRadius() != int0) {
        this.LightSource.life = 0;
        this.LightSource = nullptr;
      }

      if (this.LightSource == nullptr) {
        this.LightSource =
            new IsoLightSource(this.square.getX(), this.square.getY(),
                               this.square.getZ(), 1.0F, 0.1F, 0.1F, int0);
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
      int int0 = this.calcLightRadius();
      if (this.heatSource == nullptr) {
        this.heatSource = new IsoHeatSource((int)this.getX(), (int)this.getY(),
                                            (int)this.getZ(), int0, 35);
        IsoWorld.instance.CurrentCell.addHeatSource(this.heatSource);
      } else if (int0 != this.heatSource.getRadius()) {
        this.heatSource.setRadius(int0);
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
          this.emitter = IsoWorld.instance.getFreeEmitter(
              this.getX() + 0.5F, this.getY() + 0.5F, (int)this.getZ());
          IsoWorld.instance.setEmitterOwner(this.emitter, this);
        }

        std::string string = "FireplaceRunning";
        if (!this.emitter.isPlaying(string)) {
          this.soundInstance = this.emitter.playSoundLoopedImpl(string);
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
      bool boolean0 = this.hasFuel();
      bool boolean1 = this.isLit();
      int int0 = this.calcLightRadius();
      float float0 = (float)GameTime.getInstance().getWorldAgeHours();
      if (this.LastUpdateTime < 0.0F) {
        this.LastUpdateTime = float0;
      } else if (this.LastUpdateTime > float0) {
        this.LastUpdateTime = float0;
      }

      if (float0 > this.LastUpdateTime) {
        this.MinuteAccumulator =
            this.MinuteAccumulator + (float0 - this.LastUpdateTime) * 60.0F;
        int int1 = (int)Math.floor(this.MinuteAccumulator);
        if (int1 > 0) {
          if (this.isLit()) {
            DebugLog.log(DebugType.Fireplace,
                         "IsoFireplace burned " + int1 + " minutes (" +
                             this.getFuelAmount() + " remaining)");
            this.useFuel(int1);
            if (!this.hasFuel()) {
              this.extinguish();
            }
          } else if (this.MinutesSinceExtinguished != -1) {
            int int2 = Math.min(int1, SMOULDER_MINUTES -
                                          this.MinutesSinceExtinguished);
            DebugLog.log(DebugType.Fireplace,
                         "IsoFireplace smoldered " + int2 + " minutes (" +
                             this.getFuelAmount() + " remaining)");
            this.MinutesSinceExtinguished += int1;
            this.useFuel(int2);
            this.bSmouldering = true;
            if (!this.hasFuel() ||
                this.MinutesSinceExtinguished >= SMOULDER_MINUTES) {
              this.MinutesSinceExtinguished = -1;
              this.bSmouldering = false;
            }
          }

          this.MinuteAccumulator -= int1;
        }
      }

      this.LastUpdateTime = float0;
      if (GameServer.bServer) {
        if (boolean0 != this.hasFuel() || boolean1 != this.isLit() ||
            int0 != this.calcLightRadius()) {
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
    if (this.AttachedAnimSprite != nullptr &&
        !this.AttachedAnimSprite.isEmpty()) {
      int int3 = this.AttachedAnimSprite.size();

      for (int int4 = 0; int4 < int3; int4++) {
        IsoSpriteInstance spriteInstance = this.AttachedAnimSprite.get(int4);
        IsoSprite sprite = spriteInstance.parentSprite;
        spriteInstance.update();
        float float1 =
            GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F;
        spriteInstance.Frame =
            spriteInstance.Frame + spriteInstance.AnimFrameIncrease * float1;
        if ((int)spriteInstance.Frame >= sprite.CurrentAnim.Frames.size() &&
            sprite.Loop && spriteInstance.Looped) {
          spriteInstance.Frame = 0.0F;
        }
      }
    }
  }

  void addToWorld() {
    IsoCell cell = this.getCell();
    cell.addToProcessIsoObject(this);
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

  void render(float x, float y, float z, ColorInfo col, bool bDoChild,
              bool bWallLightingPass, Shader shader) {
    super.render(x, y, z, col, false, bWallLightingPass, shader);
    if (this.AttachedAnimSprite != nullptr) {
      for (int int0 = 0; int0 < this.AttachedAnimSprite.size(); int0++) {
        IsoSpriteInstance spriteInstance = this.AttachedAnimSprite.get(int0);
        spriteInstance.getParentSprite().render(spriteInstance, this, x, y, z,
                                                this.dir, this.offsetX,
                                                this.offsetY, col, true);
      }
    }
  }

  void saveChange(const std::string &change, KahluaTable tbl, ByteBuffer bb) {
    if ("state" == change)) {
        bb.putInt(this.getFuelAmount());
        bb.put((byte)(this.isLit() ? 1 : 0));
      }
  }

  void loadChange(const std::string &change, ByteBuffer bb) {
    if ("state" == change)) {
        this.setFuelAmount(bb.getInt());
        this.setLit(bb.get() == 1);
      }
  }
}
} // namespace objects
} // namespace iso
} // namespace zombie
