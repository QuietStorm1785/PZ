#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/javafmod.h"

namespace zombie {
namespace audio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FMODGlobalParameter : public FMODParameter {
public:
 public FMODGlobalParameter(const std::string& string) {
 super(string);
 if (this->getParameterDescription() != nullptr && !this->getParameterDescription().isGlobal()) {
 bool boolean0 = true;
 }
 }

 void setCurrentValue(float float0) {
 javafmod.FMOD_Studio_System_SetParameterByID(this->getParameterID(), float0, false);
 }

 void startEventInstance(long var1) {
 }

 void stopEventInstance(long var1) {
 }
}
} // namespace audio
} // namespace zombie
