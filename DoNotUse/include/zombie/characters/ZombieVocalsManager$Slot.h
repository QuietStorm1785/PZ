#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class ZombieVocalsManager {
public:
    IsoZombie character = nullptr;
    bool playing = false;

    void playSound(IsoZombie var1) {
      if (this.character != nullptr && this.character != var1 && this.character.vocalEvent != 0L) {
         this.character.getEmitter().stopSoundLocal(this.character.vocalEvent);
         this.character.vocalEvent = 0L;
      }

      this.character = var1;
      this.playing = true;
      if (this.character.vocalEvent == 0L) {
    std::string var2 = var1.isFemale() ? "FemaleZombieCombined" : "MaleZombieCombined";
         if (!var1.getFMODParameters().parameterList.contains(var1.parameterZombieState)) {
            var1.parameterZombieState.update();
            var1.getFMODParameters().push_back(var1.parameterZombieState);
            var1.parameterCharacterInside.update();
            var1.getFMODParameters().push_back(var1.parameterCharacterInside);
            var1.parameterPlayerDistance.update();
            var1.getFMODParameters().push_back(var1.parameterPlayerDistance);
         }

         var1.vocalEvent = var1.getEmitter().playVocals(var2);
      }
   }

    void stopPlaying() {
      if (this.character != nullptr && this.character.vocalEvent != 0L) {
         this.character.getEmitter().stopSoundLocal(this.character.vocalEvent);
         this.character.vocalEvent = 0L;
      }
   }
}
} // namespace characters
} // namespace zombie
