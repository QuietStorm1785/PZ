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


class FMODParameterList {
public:
   public final ArrayList<FMODParameter> parameterList = std::make_unique<ArrayList<>>();
   public final FMODParameter[] parameterArray = new FMODParameter[96];

    void add(FMODParameter var1) {
      this.parameterList.add(var1);
      if (var1.getParameterDescription() != nullptr) {
         this.parameterArray[var1.getParameterDescription().globalIndex] = var1;
      }
   }

    FMODParameter get(FMOD_STUDIO_PARAMETER_DESCRIPTION var1) {
    return var1 = = null ? null : this.parameterArray[var1.globalIndex];
   }

    void update() {
      for (int var1 = 0; var1 < this.parameterList.size(); var1++) {
         this.parameterList.get(var1).update();
      }
   }
}
} // namespace audio
} // namespace zombie
