#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/iso/IsoObject.h"

namespace zombie {
namespace audio {


class ObjectAmbientEmitters {
public:
    IsoObject object;
    float parameterValue1 = Float.NaN;

   public ObjectAmbientEmitters$PerObjectLogic init(IsoObject var1) {
      this.object = var1;
    return this;
   }

    void setParameterValue1(BaseSoundEmitter var1, long var2, const std::string& var4, float var5) {
      if (var5 != this.parameterValue1) {
         this.parameterValue1 = var5;
    FMOD_STUDIO_PARAMETER_DESCRIPTION var6 = FMODManager.instance.getParameterDescription(var4);
         var1.setParameterValue(var2, var6, var5);
      }
   }

    void setParameterValue1(BaseSoundEmitter var1, long var2, FMOD_STUDIO_PARAMETER_DESCRIPTION var4, float var5) {
      if (var5 != this.parameterValue1) {
         this.parameterValue1 = var5;
         var1.setParameterValue(var2, var4, var5);
      }
   }

   public abstract boolean shouldPlaySound();

   public abstract String getSoundName();

   public abstract void startPlaying(BaseSoundEmitter var1, long var2);

   public abstract void stopPlaying(BaseSoundEmitter var1, long var2);

   public abstract void checkParameters(BaseSoundEmitter var1, long var2);
}
} // namespace audio
} // namespace zombie
