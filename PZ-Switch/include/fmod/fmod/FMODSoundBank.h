#pragma once
#include "fmod/javafmod.h"
#include "java/security/InvalidParameterException.h"
#include "zombie/audio/BaseSoundBank.h"
#include "zombie/core/Core.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FMODSoundBank : public BaseSoundBank {
public:
public
 HashMap<String, FMODVoice> voiceMap = std::make_unique<HashMap<>>();
public
 HashMap<String, FMODFootstep> footstepMap = std::make_unique<HashMap<>>();

 void check(std::string_view string) {
 if (Core.bDebug &&
 javafmod.FMOD_Studio_System_GetEvent("event:/" + string) < 0L) {
 System.out.println("MISSING in .bank " + string);
 }
 }

 void addVoice(std::string_view arg0, std::string_view arg1, float arg2) {
 FMODVoice fMODVoice = new FMODVoice(arg1, arg2);
 this->voiceMap.put(arg0, fMODVoice);
 }

 void addFootstep(std::string_view arg0, std::string_view arg1,
 std::string_view arg2, std::string_view arg3,
 std::string_view arg4) {
 FMODFootstep fMODFootstep = new FMODFootstep(arg1, arg2, arg3, arg4);
 this->footstepMap.put(arg0, fMODFootstep);
 }

 FMODVoice getVoice(std::string_view arg0) {
 return this->voiceMap.containsKey(arg0) ? this->voiceMap.get(arg0) : nullptr;
 }

 FMODFootstep getFootstep(std::string_view arg0) {
 if (this->footstepMap.containsKey(arg0) {
 return this->footstepMap.get(arg0);
 } else {
 throw InvalidParameterException("Footstep not loaded: " + arg0);
 }
 }
}
} // namespace fmod
} // namespace fmod
