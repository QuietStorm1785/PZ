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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Animation : public OptionGroup {
public:
 const BooleanDebugOption Debug = newDebugOnlyOption(this->Group, "Debug", false);
 const BooleanDebugOption AllowEarlyTransitionOut = newDebugOnlyOption(this->Group, "AllowEarlyTransitionOut", true);
 public Animation.AnimLayerOG AnimLayer = new Animation.AnimLayerOG(this->Group);
 public Animation.SharedSkelesOG SharedSkeles = new Animation.SharedSkelesOG(this->Group);
 const BooleanDebugOption AnimRenderPicker = newDebugOnlyOption(this->Group, "Render.Picker", false);
 const BooleanDebugOption BlendUseFbx = newDebugOnlyOption(this->Group, "BlendUseFbx", false);

 public Animation() {
 super("Animation");
 }

 public static class AnimLayerOG extends OptionGroup {
 const BooleanDebugOption LogStateChanges = newDebugOnlyOption(this->Group, "Debug.LogStateChanges", false);
 const BooleanDebugOption AllowAnimNodeOverride = newDebugOnlyOption(this->Group, "Debug.AllowAnimNodeOverride", false);

 AnimLayerOG(IDebugOptionGroup iDebugOptionGroup) {
 super(iDebugOptionGroup, "AnimLayer");
 }
 }

 public static class SharedSkelesOG extends OptionGroup {
 const BooleanDebugOption Enabled = newDebugOnlyOption(this->Group, "Enabled", true);
 const BooleanDebugOption AllowLerping = newDebugOnlyOption(this->Group, "AllowLerping", true);

 SharedSkelesOG(IDebugOptionGroup iDebugOptionGroup) {
 super(iDebugOptionGroup, "SharedSkeles");
 }
 }
}
} // namespace options
} // namespace debug
} // namespace zombie
