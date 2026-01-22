#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/objects/IsoCurtain.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWaveSignal.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace iso {


class IsoObjectPicker {
public:
    int height;
    IsoGridSquare square;
    IsoObject tile;
    int width;
    int x;
    int y;
    int lx;
    int ly;
    float scaleX;
    float scaleY;
    bool flip;
    int score;

    int calculateScore() {
    float var1 = 1.0F;
    IsoPlayer var2 = IsoPlayer.getInstance();
    IsoGridSquare var3 = var2.getCurrentSquare();
      IsoObjectPicker.tempo.x = this.square.getX() + 0.5F;
      IsoObjectPicker.tempo.y = this.square.getY() + 0.5F;
      IsoObjectPicker.tempo.x = IsoObjectPicker.tempo.x - var2.getX();
      IsoObjectPicker.tempo.y = IsoObjectPicker.tempo.y - var2.getY();
      IsoObjectPicker.tempo.normalize();
    Vector2 var4 = var2.getVectorFromDirection(IsoObjectPicker.tempo2);
    float var5 = var4.dot(IsoObjectPicker.tempo);
      var1 += Math.abs(var5 * 4.0F);
    IsoGridSquare var6 = this.square;
    IsoObject var7 = this.tile;
    IsoSprite var8 = var7.sprite;
    IsoDoor var9 = (IsoDoor)Type.tryCastTo(var7, IsoDoor.class);
    IsoThumpable var10 = (IsoThumpable)Type.tryCastTo(var7, IsoThumpable.class);
      if (var9 == nullptr && (var10 == nullptr || !var10.isDoor())) {
         if (dynamic_cast<IsoWindow*>(var7) != nullptr) {
            var1 += 4.0F;
            if (var2.getZ() > var6.getZ()) {
               var1 -= 1000.0F;
            }
         } else {
            if (var3 != nullptr && var6.getRoom() == var3.getRoom()) {
               var1++;
            } else {
               var1 -= 100000.0F;
            }

            if (var2.getZ() > var6.getZ()) {
               var1 -= 1000.0F;
            }

            if (dynamic_cast<IsoPlayer*>(var7) != nullptr) {
               var1 -= 100000.0F;
            } else if (dynamic_cast<IsoThumpable*>(var7) != nullptr && var7.getTargetAlpha() < 0.99F && (var7.getTargetAlpha() < 0.5F || var7.getContainer() == nullptr)) {
               var1 -= 100000.0F;
            }

            if (dynamic_cast<IsoCurtain*>(var7) != nullptr) {
               var1 += 3.0F;
            } else if (dynamic_cast<IsoLightSwitch*>(var7) != nullptr) {
               var1 += 20.0F;
            } else if (var8.Properties.Is(IsoFlagType.bed)) {
               var1 += 2.0F;
            } else if (var7.container != nullptr) {
               var1 += 10.0F;
            } else if (dynamic_cast<IsoWaveSignal*>(var7) != nullptr) {
               var1 += 20.0F;
            } else if (var10 != nullptr && var10.getLightSource() != nullptr) {
               var1 += 3.0F;
            } else if (var8.Properties.Is(IsoFlagType.waterPiped)) {
               var1 += 3.0F;
            } else if (var8.Properties.Is(IsoFlagType.solidfloor)) {
               var1 -= 100.0F;
            } else if (var8.getType() == IsoObjectType.WestRoofB) {
               var1 -= 100.0F;
            } else if (var8.getType() == IsoObjectType.WestRoofM) {
               var1 -= 100.0F;
            } else if (var8.getType() == IsoObjectType.WestRoofT) {
               var1 -= 100.0F;
            } else if (var8.Properties.Is(IsoFlagType.cutW) || var8.Properties.Is(IsoFlagType.cutN)) {
               var1 -= 2.0F;
            }
         }
      } else {
         var1 += 6.0F;
         if (var9 != nullptr && var9.isAdjacentToSquare(var3) || var10 != nullptr && var10.isAdjacentToSquare(var3)) {
            var1++;
         }

         if (var2.getZ() > var6.getZ()) {
            var1 -= 1000.0F;
         }
      }

    float var11 = IsoUtils.DistanceManhatten(var6.getX() + 0.5F, var6.getY() + 0.5F, var2.getX(), var2.getY());
      var1 -= var11 / 2.0F;
      return (int)var1;
   }

    int getScore() {
      return this.score;
   }
}
} // namespace iso
} // namespace zombie
