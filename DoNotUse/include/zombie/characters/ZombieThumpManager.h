#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace characters {


class ZombieThumpManager : public BaseZombieSoundManager {
public:
    static const ZombieThumpManager instance = std::make_shared<ZombieThumpManager>();

    public ZombieThumpManager() {
      super(40, 100);
   }

    void playSound(IsoZombie var1) {
    long var2 = 0L;
      if (var1.thumpFlag == 1) {
         var2 = var1.getEmitter().playSoundImpl("ZombieThumpGeneric", nullptr);
      } else if (var1.thumpFlag == 2) {
         var1.getEmitter().playSoundImpl("ZombieThumpGeneric", nullptr);
         var2 = var1.getEmitter().playSoundImpl("ZombieThumpWindow", nullptr);
      } else if (var1.thumpFlag == 3) {
         var2 = var1.getEmitter().playSoundImpl("ZombieThumpWindow", nullptr);
      } else if (var1.thumpFlag == 4) {
         var2 = var1.getEmitter().playSoundImpl("ZombieThumpMetal", nullptr);
      } else if (var1.thumpFlag == 5) {
         var2 = var1.getEmitter().playSoundImpl("ZombieThumpGarageDoor", nullptr);
      }

    FMOD_STUDIO_PARAMETER_DESCRIPTION var4 = FMODManager.instance.getParameterDescription("ObjectCondition");
      var1.getEmitter().setParameterValue(var2, var4, PZMath.ceil(var1.getThumpCondition() * 100.0F));
   }

    void postUpdate() {
      for (int var1 = 0; var1 < this.characters.size(); var1++) {
         ((IsoZombie)this.characters.get(var1)).setThumpFlag(0);
      }
   }
}
} // namespace characters
} // namespace zombie
