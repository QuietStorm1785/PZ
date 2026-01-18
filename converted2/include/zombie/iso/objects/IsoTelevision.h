#pragma once
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LightingJNI.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/radio/ZomboidRadio.h"
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

class IsoTelevision : public IsoWaveSignal {
public:
protected
  ArrayList<IsoSprite> screenSprites = std::make_unique<ArrayList<>>();
  bool defaultToNoise = false;
  IsoSprite cacheObjectSprite;
  IsoDirections facing = IsoDirections.Max;
  bool hasSetupScreens = false;
  bool tickIsLightUpdate = false;
private
  IsoTelevision.Screens currentScreen = IsoTelevision.Screens.OFFSCREEN;
  int spriteIndex = 0;

  std::string getObjectName() { return "Television"; }

public
  IsoTelevision(IsoCell cell) { super(cell); }

public
  IsoTelevision(IsoCell cell, IsoGridSquare sq, IsoSprite spr) {
    super(cell, sq, spr);
  }

  void init(bool boolean0) { super.init(boolean0); }

  void setupDefaultScreens() {
    this.hasSetupScreens = true;
    this.cacheObjectSprite = this.sprite;
    if (this.screenSprites.size() == 0) {
      for (byte byte0 = 16; byte0 <= 64; byte0 += 16) {
        IsoSprite sprite = IsoSprite.getSprite(IsoSpriteManager.instance,
                                               this.sprite.getName(), byte0);
        if (sprite != nullptr) {
          this.addTvScreenSprite(sprite);
        }
      }
    }

    this.facing = IsoDirections.Max;
    if (this.sprite != nullptr && this.sprite.getProperties().Is("Facing")) {
      std::string string = this.sprite.getProperties().Val("Facing");
      switch (string) {
      case "N":
        this.facing = IsoDirections.N;
        break;
      case "S":
        this.facing = IsoDirections.S;
        break;
      case "W":
        this.facing = IsoDirections.W;
        break;
      case "E":
        this.facing = IsoDirections.E;
      }
    }
  }

  void update() {
    super.update();
    if (this.cacheObjectSprite != nullptr &&
        this.cacheObjectSprite != this.sprite) {
      this.hasSetupScreens = false;
      this.screenSprites.clear();
      this.currentScreen = IsoTelevision.Screens.OFFSCREEN;
      this.nextLightUpdate = 0.0F;
    }

    if (!this.hasSetupScreens) {
      this.setupDefaultScreens();
    }

    this.updateTvScreen();
  }

  void updateLightSource() {
    this.tickIsLightUpdate = false;
    if (this.lightSource == nullptr) {
      this.lightSource = new IsoLightSource(
          this.square.getX(), this.square.getY(), this.square.getZ(), 0.0F,
          0.0F, 1.0F, this.lightSourceRadius);
      this.lightWasRemoved = true;
    }

    if (this.lightWasRemoved) {
      IsoWorld.instance.CurrentCell.addLamppost(this.lightSource);
      IsoGridSquare.RecalcLightTime = -1;
      GameTime.instance.lightSourceUpdate = 100.0F;
      this.lightWasRemoved = false;
    }

    this.lightUpdateCnt =
        this.lightUpdateCnt + GameTime.getInstance().getMultiplier();
    if (this.lightUpdateCnt >= this.nextLightUpdate) {
      float float0 = 300.0F;
      float float1 = 0.0F;
      if (!this.hasChatToDisplay()) {
        float1 = 0.6F;
        float0 = Rand.Next(200, 400);
      } else {
        float0 = Rand.Next(15, 300);
      }

      float float2 = Rand.Next(float1, 1.0F);
      this.tickIsLightUpdate = true;
      float float3 = 0.58F + 0.25F * float2;
      float float4 = Rand.Next(0.65F, 0.85F);
      int int0 = 1 + (int)((this.lightSourceRadius - 1) * float2);
      IsoGridSquare.RecalcLightTime = -1;
      GameTime.instance.lightSourceUpdate = 100.0F;
      this.lightSource.setRadius(int0);
      this.lightSource.setR(float3);
      this.lightSource.setG(float4);
      this.lightSource.setB(float4);
      if (LightingJNI.init && this.lightSource.ID != 0) {
        LightingJNI.setLightColor(this.lightSource.ID, this.lightSource.getR(),
                                  this.lightSource.getG(),
                                  this.lightSource.getB());
      }

      this.lightUpdateCnt = 0.0F;
      this.nextLightUpdate = float0;
    }
  }

  void setScreen(IsoTelevision.Screens screens) {
    if (screens == IsoTelevision.Screens.OFFSCREEN) {
      this.currentScreen = IsoTelevision.Screens.OFFSCREEN;
      if (this.overlaySprite != nullptr) {
        this.overlaySprite = nullptr;
      }
    } else {
      if (this.currentScreen != screens ||
          screens == IsoTelevision.Screens.ALTERNATESCREEN) {
        this.currentScreen = screens;
        IsoSprite sprite = null;
        switch (screens) {
        case TESTSCREEN:
          if (this.screenSprites.size() > 0) {
            sprite = this.screenSprites.get(0);
          }
          break;
        case DEFAULTSCREEN:
          if (this.screenSprites.size() > 1) {
            sprite = this.screenSprites.get(1);
          }
          break;
        case ALTERNATESCREEN:
          if (this.screenSprites.size() >= 2) {
            if (this.screenSprites.size() == 2) {
              sprite = this.screenSprites.get(1);
            } else if (this.screenSprites.size() > 2) {
              this.spriteIndex++;
              if (this.spriteIndex < 1) {
                this.spriteIndex = 1;
              }

              if (this.spriteIndex > this.screenSprites.size() - 1) {
                this.spriteIndex = 1;
              }

              sprite = this.screenSprites.get(this.spriteIndex);
            }
          }
        }

        this.overlaySprite = sprite;
      }
    }
  }

  void updateTvScreen() {
    if (this.deviceData != nullptr && this.deviceData.getIsTurnedOn() &&
        this.screenSprites.size() > 0) {
      if (!this.deviceData.isReceivingSignal() &&
          !this.deviceData.isPlayingMedia()) {
        if (ZomboidRadio.POST_RADIO_SILENCE) {
          this.setScreen(IsoTelevision.Screens.TESTSCREEN);
        } else {
          this.setScreen(IsoTelevision.Screens.DEFAULTSCREEN);
        }
      } else if (this.tickIsLightUpdate ||
                 this.currentScreen != IsoTelevision.Screens.ALTERNATESCREEN) {
        this.setScreen(IsoTelevision.Screens.ALTERNATESCREEN);
      }
    } else if (this.currentScreen != IsoTelevision.Screens.OFFSCREEN) {
      this.setScreen(IsoTelevision.Screens.OFFSCREEN);
    }
  }

  void addTvScreenSprite(IsoSprite sprite) { this.screenSprites.add(sprite); }

  void clearTvScreenSprites() { this.screenSprites.clear(); }

  void removeTvScreenSprite(IsoSprite sprite) {
    this.screenSprites.remove(sprite);
  }

  void renderlast() { super.renderlast(); }

  void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
    super.load(input, WorldVersion, IS_DEBUG_SAVE);
    this.overlaySprite = nullptr;
  }

  void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
    super.save(output, IS_DEBUG_SAVE);
  }

  bool isFacing(IsoPlayer player) {
    if (player != nullptr && player.isLocalPlayer()) {
      if (this.getObjectIndex() == -1) {
        return false;
      } else if (!this.square.isCanSee(player.PlayerIndex)) {
        return false;
      } else if (this.facing == IsoDirections.Max) {
        return false;
      } else {
        switch (this.facing) {
        case N:
          if (player.y >= this.square.y) {
            return false;
          }

          return player.dir == IsoDirections.SW ||
                 player.dir == IsoDirections.S ||
                 player.dir == IsoDirections.SE;
        case S:
          if (player.y < this.square.y + 1) {
            return false;
          }

          return player.dir == IsoDirections.NW ||
                 player.dir == IsoDirections.N ||
                 player.dir == IsoDirections.NE;
        case W:
          if (player.x >= this.square.x) {
            return false;
          }

          return player.dir == IsoDirections.SE ||
                 player.dir == IsoDirections.E ||
                 player.dir == IsoDirections.NE;
        case E:
          if (player.x < this.square.x + 1) {
            return false;
          }

          return player.dir == IsoDirections.SW ||
                 player.dir == IsoDirections.W ||
                 player.dir == IsoDirections.NW;
        default:
          return false;
        }
      }
    } else {
      return false;
    }
  }

private
  static enum Screens { OFFSCREEN, TESTSCREEN, DEFAULTSCREEN, ALTERNATESCREEN; }
}
} // namespace objects
} // namespace iso
} // namespace zombie
