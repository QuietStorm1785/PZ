#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"

namespace zombie {
namespace debug {
namespace options {


class char {
public:
    const BooleanDebugOption AimCone = newDebugOnlyOption(this.Group, "AimCone", false);
    const BooleanDebugOption Angle = newDebugOnlyOption(this.Group, "Angle", false);
    const BooleanDebugOption TestDotSide = newDebugOnlyOption(this.Group, "TestDotSide", false);
    const BooleanDebugOption DeferredMovement = newDebugOnlyOption(this.Group, "DeferredMovement", false);
    const BooleanDebugOption DeferredAngles = newDebugOnlyOption(this.Group, "DeferredRotation", false);
    const BooleanDebugOption TranslationData = newDebugOnlyOption(this.Group, "Translation_Data", false);
    const BooleanDebugOption Bip01 = newDebugOnlyOption(this.Group, "Bip01", false);
    const BooleanDebugOption PrimaryHandBone = newDebugOnlyOption(this.Group, "HandBones.Primary", false);
    const BooleanDebugOption SecondaryHandBone = newDebugOnlyOption(this.Group, "HandBones.Secondary", false);
    const BooleanDebugOption SkipCharacters = newDebugOnlyOption(this.Group, "SkipCharacters", false);
    const BooleanDebugOption Vision = newDebugOnlyOption(this.Group, "Vision", false);
    const BooleanDebugOption DisplayRoomAndZombiesZone = newDebugOnlyOption(this.Group, "DisplayRoomAndZombiesZone", false);
    const BooleanDebugOption FMODRoomType = newDebugOnlyOption(this.Group, "FMODRoomType", false);

   public char$DebugOG$RenderOG(IDebugOptionGroup var1) {
      super(var1, "Render");
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
