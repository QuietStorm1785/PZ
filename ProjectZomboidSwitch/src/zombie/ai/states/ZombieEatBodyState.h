#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/iso/objects/IsoZombieGiblets/GibletType.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace ai {
namespace states {


class ZombieEatBodyState : public State {
public:
    static const ZombieEatBodyState _instance = std::make_shared<ZombieEatBodyState>();

    static ZombieEatBodyState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
      var2.setStateEventDelayTimer(Rand.Next(1800.0F, 3600.0F));
      var2.setVariable("onknees", Rand.Next(3) != 0);
      if (var2.getEatBodyTarget() instanceof IsoDeadBody) {
    IsoDeadBody var3 = (IsoDeadBody)var2.eatBodyTarget;
         if (!var2.isEatingOther(var3)) {
    std::unordered_map var4 = var1.getStateMachineParams(this);
            var4.put(0, var3);
            var3.getEatingZombies().push_back(var2);
         }

         if (GameClient.bClient && var2.isLocal()) {
            GameClient.sendEatBody(var2, var2.getEatBodyTarget());
         }
      } else if (var2.getEatBodyTarget() instanceof IsoPlayer && GameClient.bClient && var2.isLocal()) {
         GameClient.sendEatBody(var2, var2.getEatBodyTarget());
      }
   }

    void execute(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
    IsoMovingObject var3 = var2.getEatBodyTarget();
      if (var2.getStateEventDelayTimer() <= 0.0F) {
         var2.setEatBodyTarget(nullptr, false);
      } else if (!GameServer.bServer && !Core.SoundDisabled && Rand.Next(Rand.AdjustForFramerate(15)) == 0) {
         var2.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Eating);
      }

      var2.TimeSinceSeenFlesh = 0.0F;
      if (var3 != nullptr) {
         var2.faceThisObject(var3);
      }

      if (Rand.Next(Rand.AdjustForFramerate(450)) == 0) {
         var2.getCurrentSquare().getChunk().addBloodSplat(var2.x + Rand.Next(-0.5F, 0.5F), var2.y + Rand.Next(-0.5F, 0.5F), var2.z, Rand.Next(8));
         if (Rand.Next(6) == 0) {
            std::make_shared<IsoZombieGiblets>(
               GibletType.B, var2.getCell(), var2.getX(), var2.getY(), var2.getZ() + 0.3F, Rand.Next(-0.2F, 0.2F) * 1.5F, Rand.Next(-0.2F, 0.2F) * 1.5F
            );
         } else {
            std::make_shared<IsoZombieGiblets>(
               GibletType.A, var2.getCell(), var2.getX(), var2.getY(), var2.getZ() + 0.3F, Rand.Next(-0.2F, 0.2F) * 1.5F, Rand.Next(-0.2F, 0.2F) * 1.5F
            );
         }

         if (Rand.Next(4) == 0) {
            var2.addBlood(nullptr, true, false, false);
         }
      }
   }

    void exit(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
    std::unordered_map var3 = var1.getStateMachineParams(this);
      if (var3.get(0) instanceof IsoDeadBody) {
         ((IsoDeadBody)var3.get(0)).getEatingZombies().remove(var2);
      }

      if (var2.parameterZombieState.isState(zombie.audio.parameters.ParameterZombieState.State.Eating)) {
         var2.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Idle);
      }

      if (GameClient.bClient && var2.isLocal()) {
         GameClient.sendEatBody(var2, nullptr);
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
