#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaHookManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/states/SwipeStatePlayer.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/packets/hit/AttackVars.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace characters {


class IsoLivingCharacter : public IsoGameCharacter {
public:
    float useChargeDelta = 0.0F;
    const HandWeapon bareHands;
    bool bDoShove = false;
    bool bCollidedWithPushable = false;
    IsoGameCharacter targetOnGround;

    public IsoLivingCharacter(IsoCell var1, float var2, float var3, float var4) {
      super(var1, var2, var3, var4);
      this.bareHands = (HandWeapon)InventoryItemFactory.CreateItem("Base.BareHands");
   }

    bool isCollidedWithPushableThisFrame() {
      return this.bCollidedWithPushable;
   }

    bool AttemptAttack(float var1) {
    void* var2 = nullptr;
      if (!(this.dynamic_cast<HandWeapon*>(leftHandItem) != nullptr var4)) {
         var4 = this.bareHands;
      }

      if (var4 != this.bareHands && dynamic_cast<IsoPlayer*>(this) != nullptr) {
    AttackVars var3 = std::make_shared<AttackVars>();
         SwipeStatePlayer.instance().CalcAttackVars(this, var3);
         this.setDoShove(var3.bDoShove);
         if (LuaHookManager.TriggerHook("Attack", this, var1, var4)) {
    return false;
         }
      }

      return this.DoAttack(var1);
   }

    bool DoAttack(float var1) {
      if (this.isDead()) {
    return false;
      } else {
         if (this.leftHandItem != nullptr) {
    InventoryItem var2 = this.leftHandItem;
            if (dynamic_cast<HandWeapon*>(var2) != nullptr) {
               this.useHandWeapon = (HandWeapon)var2;
               if (this.useHandWeapon.getCondition() <= 0) {
    return false;
               }

    int var3 = this.Moodles.getMoodleLevel(MoodleType.Endurance);
               if (this.useHandWeapon.isCantAttackWithLowestEndurance() && var3 == 4) {
    return false;
               }

    int var4 = 0;
               if (this.useHandWeapon.isRanged()) {
    int var5 = this.useHandWeapon.getRecoilDelay();
    float var6 = var5 * (1.0F - this.getPerkLevel(Perks.Aiming) / 30.0F);
                  this.setRecoilDelay(var6.intValue());
               }

               if (dynamic_cast<IsoSurvivor*>(this) != nullptr && this.useHandWeapon.isRanged() && var4 < this.useHandWeapon.getMaxHitCount()) {
                  for (int var13 = 0; var13 < this.getCell().getObjectList().size(); var13++) {
    IsoMovingObject var14 = (IsoMovingObject)this.getCell().getObjectList().get(var13);
                     if (var14 != this && var14.isShootable() && this.IsAttackRange(var14.getX(), var14.getY(), var14.getZ())) {
    float var7 = 1.0F;
                        if (var7 > 0.0F) {
    Vector2 var8 = std::make_shared<Vector2>(this.getX(), this.getY());
    Vector2 var9 = std::make_shared<Vector2>(var14.getX(), var14.getY());
                           var9.x = var9.x - var8.x;
                           var9.y = var9.y - var8.y;
    bool var10 = false;
                           if (var9.x == 0.0F && var9.y == 0.0F) {
                              var10 = true;
                           }

    Vector2 var11 = this.getForwardDirection();
                           this.DirectionFromVector(var11);
                           var9.normalize();
    float var12 = var9.dot(var11);
                           if (var10) {
                              var12 = 1.0F;
                           }

                           if (var12 > 1.0F) {
                              var12 = 1.0F;
                           }

                           if (var12 < -1.0F) {
                              var12 = -1.0F;
                           }

                           if (var12 >= this.useHandWeapon.getMinAngle() && var12 <= this.useHandWeapon.getMaxAngle()) {
                              var4++;
                           }

                           if (var4 >= this.useHandWeapon.getMaxHitCount()) {
                              break;
                           }
                        }
                     }
                  }
               }

               if (UIManager.getPicked() != nullptr) {
                  this.attackTargetSquare = UIManager.getPicked().square;
                  if (UIManager.getPicked().dynamic_cast<IsoMovingObject*>(tile) != nullptr) {
                     this.attackTargetSquare = ((IsoMovingObject)UIManager.getPicked().tile).getCurrentSquare();
                  }
               }

               if (this.useHandWeapon.getAmmoType() != nullptr && !this.inventory.contains(this.useHandWeapon.getAmmoType())) {
    return false;
               }

               if (this.useHandWeapon.getOtherHandRequire() == nullptr
                  || this.rightHandItem != nullptr && this.rightHandItem.getType() == this.useHandWeapon.getOtherHandRequire())) {
                  if (!this.useHandWeapon.isRanged()) {
                     this.getEmitter().playSound(this.useHandWeapon.getSwingSound(), this);
                     WorldSoundManager.instance
                        .addSound(
                           this, (int)this.getX(), (int)this.getY(), (int)this.getZ(), this.useHandWeapon.getSoundRadius(), this.useHandWeapon.getSoundVolume()
                        );
                  }

                  this.AttackWasSuperAttack = this.superAttack;
                  this.changeState(SwipeStatePlayer.instance());
                  if (this.useHandWeapon.getAmmoType() != nullptr) {
                     if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
                        IsoPlayer.getInstance().inventory.RemoveOneOf(this.useHandWeapon.getAmmoType());
                     } else {
                        this.inventory.RemoveOneOf(this.useHandWeapon.getAmmoType());
                     }
                  }

                  if (this.useHandWeapon.isUseSelf() && this.leftHandItem != nullptr) {
                     this.leftHandItem.Use();
                  }

                  if (this.useHandWeapon.isOtherHandUse() && this.rightHandItem != nullptr) {
                     this.rightHandItem.Use();
                  }

    return true;
               }

    return false;
            }
         }

    return false;
      }
   }

    bool isDoShove() {
      return this.bDoShove;
   }

    void setDoShove(bool var1) {
      this.bDoShove = var1;
   }
}
} // namespace characters
} // namespace zombie
