#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"

namespace zombie {
namespace audio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FMODParameterList {
public:
 public ArrayList<FMODParameter> parameterList = std::make_unique<ArrayList<>>();
 public FMODParameter[] parameterArray = new FMODParameter[96];

 void add(FMODParameter parameter) {
 this->parameterList.add(parameter);
 if (parameter.getParameterDescription() != nullptr) {
 this->parameterArray[parameter.getParameterDescription().globalIndex] = parameter;
 }
 }

 FMODParameter get(FMOD_STUDIO_PARAMETER_DESCRIPTION pdesc) {
 return pdesc = = nullptr ? nullptr : this->parameterArray[pdesc.globalIndex];
 }

 void update() {
 for (int int0 = 0; int0 < this->parameterList.size(); int0++) {
 this->parameterList.get(int0).update();
 }
 }
}
} // namespace audio
} // namespace zombie
