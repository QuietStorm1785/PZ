#pragma once
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FMODParameterList {
public:
public
  final ArrayList<FMODParameter> parameterList =
      std::make_unique<ArrayList<>>();
public
  final FMODParameter[] parameterArray = new FMODParameter[96];

  void add(FMODParameter parameter) {
    this.parameterList.add(parameter);
    if (parameter.getParameterDescription() != nullptr) {
      this.parameterArray[parameter.getParameterDescription().globalIndex] =
          parameter;
    }
  }

  FMODParameter get(FMOD_STUDIO_PARAMETER_DESCRIPTION pdesc) {
    return pdesc = = null ? null : this.parameterArray[pdesc.globalIndex];
  }

  void update() {
    for (int int0 = 0; int0 < this.parameterList.size(); int0++) {
      this.parameterList.get(int0).update();
    }
  }
}
} // namespace audio
} // namespace zombie
