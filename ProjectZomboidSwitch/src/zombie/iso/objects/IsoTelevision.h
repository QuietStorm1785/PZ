#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LightingJNI.h"
#include "zombie/iso/objects/IsoTelevision/1.h"
#include "zombie/iso/objects/IsoTelevision/Screens.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/radio/ZomboidRadio.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoTelevision : public IsoWaveSignal {
public:
   protected std::vector<IsoSprite> screenSprites = std::make_unique<std::vector<>>();
    bool defaultToNoise = false;
    IsoSprite cacheObjectSprite;
    IsoDirections facing = IsoDirections.Max;
    bool hasSetupScreens = false;
    bool tickIsLightUpdate = false;
    Screens currentScreen = Screens.OFFSCREEN;
    int spriteIndex = 0;

    std::string getObjectName() {
      return "Television";
   }

    public IsoTelevision(IsoCell var1) {
      super(var1);
   }

    public IsoTelevision(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      super(var1, var2, var3);
   }

    void init(bool var1) {
      super.init(var1);
   }

    void setupDefaultScreens() {
      this.hasSetupScreens = true;
      this.cacheObjectSprite = this.sprite;
      if (this.screenSprites.size() == 0) {
         for (byte var1 = 16; var1 <= 64; var1 += 16) {
    IsoSprite var2 = IsoSprite.getSprite(IsoSpriteManager.instance, this.sprite.getName(), var1);
            if (var2 != nullptr) {
               this.addTvScreenSprite(var2);
            }
         }
      }

      this.facing = IsoDirections.Max;
      if (this.sprite != nullptr && this.sprite.getProperties().Is("Facing")) {
    std::string var4 = this.sprite.getProperties().Val("Facing");
         switch (var4) {
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
      if (this.cacheObjectSprite != nullptr && this.cacheObjectSprite != this.sprite) {
         this.hasSetupScreens = false;
         this.screenSprites.clear();
         this.currentScreen = Screens.OFFSCREEN;
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
         this.lightSource = std::make_shared<IsoLightSource>(this.square.getX(), this.square.getY(), this.square.getZ(), 0.0F, 0.0F, 1.0F, this.lightSourceRadius);
         this.lightWasRemoved = true;
      }

      if (this.lightWasRemoved) {
         IsoWorld.instance.CurrentCell.addLamppost(this.lightSource);
         IsoGridSquare.RecalcLightTime = -1;
         GameTime.instance.lightSourceUpdate = 100.0F;
         this.lightWasRemoved = false;
      }

      this.lightUpdateCnt = this.lightUpdateCnt + GameTime.getInstance().getMultiplier();
      if (this.lightUpdateCnt >= this.nextLightUpdate) {
    float var1 = 300.0F;
    float var2 = 0.0F;
         if (!this.hasChatToDisplay()) {
            var2 = 0.6F;
            var1 = Rand.Next(200, 400);
         } else {
            var1 = Rand.Next(15, 300);
         }

    float var3 = Rand.Next(var2, 1.0F);
         this.tickIsLightUpdate = true;
    float var4 = 0.58F + 0.25F * var3;
    float var5 = Rand.Next(0.65F, 0.85F);
    int var6 = 1 + (int)((this.lightSourceRadius - 1) * var3);
         IsoGridSquare.RecalcLightTime = -1;
         GameTime.instance.lightSourceUpdate = 100.0F;
         this.lightSource.setRadius(var6);
         this.lightSource.setR(var4);
         this.lightSource.setG(var5);
         this.lightSource.setB(var5);
         if (LightingJNI.init && this.lightSource.ID != 0) {
            LightingJNI.setLightColor(this.lightSource.ID, this.lightSource.getR(), this.lightSource.getG(), this.lightSource.getB());
         }

         this.lightUpdateCnt = 0.0F;
         this.nextLightUpdate = var1;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void setScreen(Screens var1) {
      if (var1 == Screens.OFFSCREEN) {
         this.currentScreen = Screens.OFFSCREEN;
         if (this.overlaySprite != nullptr) {
            this.overlaySprite = nullptr;
         }
      } else {
         if (this.currentScreen != var1 || var1 == Screens.ALTERNATESCREEN) {
            this.currentScreen = var1;
    IsoSprite var2 = nullptr;
            switch (1.$SwitchMap$zombie$iso$objects$IsoTelevision$Screens[var1.ordinal()]) {
               case 1:
                  if (this.screenSprites.size() > 0) {
                     var2 = this.screenSprites.get(0);
                  }
                  break;
               case 2:
                  if (this.screenSprites.size() > 1) {
                     var2 = this.screenSprites.get(1);
                  }
                  break;
               case 3:
                  if (this.screenSprites.size() >= 2) {
                     if (this.screenSprites.size() == 2) {
                        var2 = this.screenSprites.get(1);
                     } else if (this.screenSprites.size() > 2) {
                        this.spriteIndex++;
                        if (this.spriteIndex < 1) {
                           this.spriteIndex = 1;
                        }

                        if (this.spriteIndex > this.screenSprites.size() - 1) {
                           this.spriteIndex = 1;
                        }

                        var2 = this.screenSprites.get(this.spriteIndex);
                     }
                  }
            }

            this.overlaySprite = var2;
         }
      }
   }

    void updateTvScreen() {
      if (this.deviceData != nullptr && this.deviceData.getIsTurnedOn() && this.screenSprites.size() > 0) {
         if (!this.deviceData.isReceivingSignal() && !this.deviceData.isPlayingMedia()) {
            if (ZomboidRadio.POST_RADIO_SILENCE) {
               this.setScreen(Screens.TESTSCREEN);
            } else {
               this.setScreen(Screens.DEFAULTSCREEN);
            }
         } else if (this.tickIsLightUpdate || this.currentScreen != Screens.ALTERNATESCREEN) {
            this.setScreen(Screens.ALTERNATESCREEN);
         }
      } else if (this.currentScreen != Screens.OFFSCREEN) {
         this.setScreen(Screens.OFFSCREEN);
      }
   }

    void addTvScreenSprite(IsoSprite var1) {
      this.screenSprites.push_back(var1);
   }

    void clearTvScreenSprites() {
      this.screenSprites.clear();
   }

    void removeTvScreenSprite(IsoSprite var1) {
      this.screenSprites.remove(var1);
   }

    void renderlast() {
      super.renderlast();
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.overlaySprite = nullptr;
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool isFacing(IsoPlayer var1) {
      if (var1 != nullptr && var1.isLocalPlayer()) {
         if (this.getObjectIndex() == -1) {
    return false;
         } else if (!this.square.isCanSee(var1.PlayerIndex)) {
    return false;
         } else if (this.facing == IsoDirections.Max) {
    return false;
         } else {
            switch (1.$SwitchMap$zombie$iso$IsoDirections[this.facing.ordinal()]) {
               case 1:
                  if (var1.y >= this.square.y) {
    return false;
                  }

                  return var1.dir == IsoDirections.SW || var1.dir == IsoDirections.S || var1.dir == IsoDirections.SE;
               case 2:
                  if (var1.y < this.square.y + 1) {
    return false;
                  }

                  return var1.dir == IsoDirections.NW || var1.dir == IsoDirections.N || var1.dir == IsoDirections.NE;
               case 3:
                  if (var1.x >= this.square.x) {
    return false;
                  }

                  return var1.dir == IsoDirections.SE || var1.dir == IsoDirections.E || var1.dir == IsoDirections.NE;
               case 4:
                  if (var1.x < this.square.x + 1) {
    return false;
                  }

                  return var1.dir == IsoDirections.SW || var1.dir == IsoDirections.W || var1.dir == IsoDirections.NW;
               default:
    return false;
            }
         }
      } else {
    return false;
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
