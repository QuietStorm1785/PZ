#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"
#include "zombie/debug/options/Animation/AnimLayerOG.h"
#include "zombie/debug/options/Animation/SharedSkelesOG.h"

namespace zombie {
namespace debug {
namespace options {


class Animation : public OptionGroup {
public:
    const BooleanDebugOption Debug = newDebugOnlyOption(this.Group, "Debug", false);
    const BooleanDebugOption AllowEarlyTransitionOut = newDebugOnlyOption(this.Group, "AllowEarlyTransitionOut", true);
    const AnimLayerOG AnimLayer = std::make_shared<AnimLayerOG>(this.Group);
    const SharedSkelesOG SharedSkeles = std::make_shared<SharedSkelesOG>(this.Group);
    const BooleanDebugOption AnimRenderPicker = newDebugOnlyOption(this.Group, "Render.Picker", false);
    const BooleanDebugOption BlendUseFbx = newDebugOnlyOption(this.Group, "BlendUseFbx", false);

    public Animation() {
      super("Animation");
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
