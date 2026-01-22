#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/iso/Vector3.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"

namespace zombie {
namespace ai {
namespace states {


class ZombieOnGroundState : public State {
public:
    static const ZombieOnGroundState _instance = std::make_shared<ZombieOnGroundState>();
    static Vector3 tempVector = std::make_shared<Vector3>();
    static Vector3 tempVectorBonePos = std::make_shared<Vector3>();

    static ZombieOnGroundState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
      var1.setCollidable(false);
      if (!var1.isDead()) {
         var1.setOnFloor(true);
      }

      if (var1.isDead() || var2.isFakeDead()) {
         var1.die();
      } else if (!var2.isBecomeCrawler()) {
         if (!"Tutorial" == Core.GameMode)) {
            var1.setReanimateTimer(Rand.Next(60) + 30);
         }

         if (GameClient.bClient && var2.isReanimatedPlayer()) {
            IsoDeadBody.removeDeadBody(var2.networkAI.reanimatedBodyID);
         }

         var2.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Idle);
      }
   }

    void execute(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
      if (var1.isDead() || var2.isFakeDead()) {
         var1.die();
      } else if (var2.isBecomeCrawler()) {
         if (!var2.isBeingSteppedOn() && !var2.isUnderVehicle()) {
            var2.setCrawler(true);
            var2.setCanWalk(false);
            var2.setReanimate(true);
            var2.setBecomeCrawler(false);
         }
      } else {
         if (var1.hasAnimationPlayer()) {
            var1.getAnimationPlayer().setTargetToAngle();
         }

         var1.setReanimateTimer(var1.getReanimateTimer() - GameTime.getInstance().getMultiplier() / 1.6F);
         if (var1.getReanimateTimer() <= 2.0F) {
            if (GameClient.bClient) {
               if (var1.isBeingSteppedOn() && !var2.isReanimatedPlayer()) {
                  var1.setReanimateTimer(Rand.Next(60) + 30);
               }
            } else if (var1.isBeingSteppedOn() && var2.getReanimatedPlayer() == nullptr) {
               var1.setReanimateTimer(Rand.Next(60) + 30);
            }
         }
      }
   }

    static bool isCharacterStandingOnOther(IsoGameCharacter var0, IsoGameCharacter var1) {
    AnimationPlayer var2 = var1.getAnimationPlayer();
    int var3 = DoCollisionBoneCheck(var0, var1, var2.getSkinningBoneIndex("Bip01_Spine", -1), 0.32F);
      if (var3 == -1) {
         var3 = DoCollisionBoneCheck(var0, var1, var2.getSkinningBoneIndex("Bip01_L_Calf", -1), 0.18F);
      }

      if (var3 == -1) {
         var3 = DoCollisionBoneCheck(var0, var1, var2.getSkinningBoneIndex("Bip01_R_Calf", -1), 0.18F);
      }

      if (var3 == -1) {
         var3 = DoCollisionBoneCheck(var0, var1, var2.getSkinningBoneIndex("Bip01_Head", -1), 0.28F);
      }

      return var3 > -1;
   }

    static int DoCollisionBoneCheck(IsoGameCharacter var0, IsoGameCharacter var1, int var2, float var3) {
    float var5 = 0.3F;
      Model.BoneToWorldCoords(var1, var2, tempVectorBonePos);

      for (int var6 = 1; var6 <= 10; var6++) {
    float var7 = var6 / 10.0F;
         tempVector.x = var0.x;
         tempVector.y = var0.y;
         tempVector.z = var0.z;
         tempVector.x = tempVector.x + var0.getForwardDirection().x * var5 * var7;
         tempVector.y = tempVector.y + var0.getForwardDirection().y * var5 * var7;
         tempVector.x = tempVectorBonePos.x - tempVector.x;
         tempVector.y = tempVectorBonePos.y - tempVector.y;
         tempVector.z = 0.0F;
    bool var8 = tempVector.getLength() < var3;
         if (var8) {
    return var2;
         }
      }

      return -1;
   }

    void exit(IsoGameCharacter var1) {
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
