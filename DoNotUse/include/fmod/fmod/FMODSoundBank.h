#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/javafmod.h"
#include "java/security/InvalidParameterException.h"
#include "zombie/audio/BaseSoundBank.h"
#include "zombie/core/Core.h"

namespace fmod {
namespace fmod {


class FMODSoundBank : public BaseSoundBank {
public:
   public std::unordered_map<std::string, FMODVoice> voiceMap = std::make_unique<std::unordered_map<>>();
   public std::unordered_map<std::string, FMODFootstep> footstepMap = std::make_unique<std::unordered_map<>>();

    void check(const std::string& var1) {
      if (Core.bDebug && javafmod.FMOD_Studio_System_GetEvent("event:/" + var1) < 0L) {
         System.out.println("MISSING in .bank " + var1);
      }
   }

    void addVoice(const std::string& var1, const std::string& var2, float var3) {
    FMODVoice var4 = std::make_shared<FMODVoice>(var2, var3);
      this.voiceMap.put(var1, var4);
   }

    void addFootstep(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5) {
    FMODFootstep var6 = std::make_shared<FMODFootstep>(var2, var3, var4, var5);
      this.footstepMap.put(var1, var6);
   }

    FMODVoice getVoice(const std::string& var1) {
      return this.voiceMap.containsKey(var1) ? this.voiceMap.get(var1) : nullptr;
   }

    FMODFootstep getFootstep(const std::string& var1) {
      if (this.footstepMap.containsKey(var1)) {
         return this.footstepMap.get(var1);
      } else {
         throw InvalidParameterException("Footstep not loaded: " + var1);
      }
   }
}
} // namespace fmod
} // namespace fmod
