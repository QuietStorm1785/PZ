#pragma once
#include "fmod/javafmod.h"
#include "gnu/trove/list/array/TLongArrayList.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FMODLocalParameter : public FMODParameter {
public:
 const TLongArrayList m_instances = new TLongArrayList();

public
 FMODLocalParameter(std::string_view string) {
 super(string);
 if (this->getParameterDescription() != nullptr &&
 this->getParameterDescription().isGlobal()) {
 bool boolean0 = true;
 }
 }

 float calculateCurrentValue() { return 0.0F; }

 void setCurrentValue(float float0) {
 for (int int0 = 0; int0 < this->m_instances.size(); int0++) {
 long long0 = this->m_instances.get(int0);
 javafmod.FMOD_Studio_EventInstance_SetParameterByID(
 long0, this->getParameterID(), float0, false);
 }
 }

 void startEventInstance(long long0) {
 this->m_instances.add(long0);
 javafmod.FMOD_Studio_EventInstance_SetParameterByID(
 long0, this->getParameterID(), this->getCurrentValue(), false);
 }

 void stopEventInstance(long long0) { this->m_instances.remove(long0); }
}
} // namespace audio
} // namespace zombie
