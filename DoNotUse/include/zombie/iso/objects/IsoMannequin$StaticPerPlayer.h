#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/inventory/types/Moveable.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoMannequin {
public:
    const int playerIndex;
    Moveable _moveable = nullptr;
    Moveable _failedItem = nullptr;
    IsoMannequin _mannequin = nullptr;

   IsoMannequin$StaticPerPlayer(int var1) {
      this.playerIndex = var1;
   }

    void renderMoveableItem(Moveable var1, int var2, int var3, int var4, IsoDirections var5) {
      if (this.checkItem(var1)) {
         if (this._moveable != var1) {
            this._moveable = var1;

            try {
               this._mannequin.getCustomSettingsFromItem(this._moveable);
            } catch (IOException var7) {
            }

            this._mannequin.initOutfit();
            this._mannequin.validateSkinTexture();
            this._mannequin.validatePose();
            this._mannequin.syncModel();
            this._mannequin.perPlayer[this.playerIndex].atlasTex = nullptr;
         }

         this._mannequin.square = IsoWorld.instance.CurrentCell.getGridSquare(var2, var3, var4);
         if (this._mannequin.square != nullptr) {
            this._mannequin.perPlayer[this.playerIndex].renderDirection = var5;
            IsoMannequin.inf.set(1.0F, 1.0F, 1.0F, 1.0F);
            this._mannequin.render(var2, var3, var4, IsoMannequin.inf, false, false, nullptr);
         }
      }
   }

    IsoDirections getDirectionFromItem(Moveable var1) {
      if (!this.checkItem(var1)) {
         return IsoDirections.S;
      } else {
         this._moveable = nullptr;

         try {
            this._mannequin.getCustomSettingsFromItem(var1);
            return this._mannequin.getDir();
         } catch (Exception var3) {
            return IsoDirections.S;
         }
      }
   }

    bool checkItem(Moveable var1) {
      if (var1 == nullptr) {
    return false;
      } else {
    std::string var2 = var1.getWorldSprite();
    IsoSprite var3 = IsoSpriteManager.instance.getSprite(var2);
         if (var3 == nullptr || !IsoMannequin.isMannequinSprite(var3)) {
    return false;
         } else if (var1.getByteData() == nullptr) {
    Thread var4 = Thread.currentThread();
            if (var4 != GameWindow.GameThread && var4 != GameLoadingState.loader && var4 == GameServer.MainThread) {
    return false;
            } else {
               if (this._mannequin == nullptr || this._mannequin.getCell() != IsoWorld.instance.CurrentCell) {
                  this._mannequin = std::make_shared<IsoMannequin>(IsoWorld.instance.CurrentCell);
               }

               if (this._failedItem == var1) {
    return false;
               } else {
                  try {
                     this._mannequin.resetMannequin();
                     this._mannequin.sprite = var3;
                     this._mannequin.initOutfit();
                     this._mannequin.validateSkinTexture();
                     this._mannequin.validatePose();
                     this._mannequin.syncModel();
                     this._mannequin.setCustomSettingsToItem(var1);
    return true;
                  } catch (IOException var6) {
                     this._failedItem = var1;
    return false;
                  }
               }
            }
         } else {
            if (this._mannequin == nullptr || this._mannequin.getCell() != IsoWorld.instance.CurrentCell) {
               this._mannequin = std::make_shared<IsoMannequin>(IsoWorld.instance.CurrentCell);
            }

    return true;
         }
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
