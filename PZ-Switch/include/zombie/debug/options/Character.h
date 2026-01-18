#pragma once
#include "zombie/debug/BooleanDebugOption.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace debug {
namespace options {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Character : public OptionGroup {
public:
 const BooleanDebugOption CreateAllOutfits =
 newOption(this->Group, "Create.AllOutfits", false);
public
 Character.DebugOG Debug = new Character.DebugOG(this->Group);

public
 Character() { super("Character"); }

public
 static class DebugOG extends OptionGroup {
 public
 Character.DebugOG.RenderOG Render =
 new Character.DebugOG.RenderOG(this->Group);
 public
 Character.DebugOG.AnimateOG Animate =
 new Character.DebugOG.AnimateOG(this->Group);
 const BooleanDebugOption RegisterDebugVariables =
 newDebugOnlyOption(this->Group, "DebugVariables", false);
 const BooleanDebugOption AlwaysTripOverFence =
 newDebugOnlyOption(this->Group, "AlwaysTripOverFence", false);
 const BooleanDebugOption PlaySoundWhenInvisible =
 newDebugOnlyOption(this->Group, "PlaySoundWhenInvisible", false);
 const BooleanDebugOption UpdateAlpha =
 newDebugOnlyOption(this->Group, "UpdateAlpha", true);
 const BooleanDebugOption UpdateAlphaEighthSpeed =
 newDebugOnlyOption(this->Group, "UpdateAlphaEighthSpeed", false);

 public
 DebugOG(IDebugOptionGroup parentGroup) { super(parentGroup, "Debug"); }

 public
 static class AnimateOG extends OptionGroup {
 const BooleanDebugOption DeferredRotationOnly =
 newDebugOnlyOption(this->Group, "DeferredRotationsOnly", false);
 const BooleanDebugOption NoBoneMasks =
 newDebugOnlyOption(this->Group, "NoBoneMasks", false);
 const BooleanDebugOption NoBoneTwists =
 newDebugOnlyOption(this->Group, "NoBoneTwists", false);
 const BooleanDebugOption ZeroCounterRotationBone =
 newDebugOnlyOption(this->Group, "ZeroCounterRotation", false);

 public
 AnimateOG(IDebugOptionGroup parentGroup) {
 super(parentGroup, "Animate");
 }
 }

 public static class RenderOG extends OptionGroup {
 const BooleanDebugOption AimCone =
 newDebugOnlyOption(this->Group, "AimCone", false);
 const BooleanDebugOption Angle =
 newDebugOnlyOption(this->Group, "Angle", false);
 const BooleanDebugOption TestDotSide =
 newDebugOnlyOption(this->Group, "TestDotSide", false);
 const BooleanDebugOption DeferredMovement =
 newDebugOnlyOption(this->Group, "DeferredMovement", false);
 const BooleanDebugOption DeferredAngles =
 newDebugOnlyOption(this->Group, "DeferredRotation", false);
 const BooleanDebugOption TranslationData =
 newDebugOnlyOption(this->Group, "Translation_Data", false);
 const BooleanDebugOption Bip01 =
 newDebugOnlyOption(this->Group, "Bip01", false);
 const BooleanDebugOption PrimaryHandBone =
 newDebugOnlyOption(this->Group, "HandBones.Primary", false);
 const BooleanDebugOption SecondaryHandBone =
 newDebugOnlyOption(this->Group, "HandBones.Secondary", false);
 const BooleanDebugOption SkipCharacters =
 newDebugOnlyOption(this->Group, "SkipCharacters", false);
 const BooleanDebugOption Vision =
 newDebugOnlyOption(this->Group, "Vision", false);
 const BooleanDebugOption DisplayRoomAndZombiesZone =
 newDebugOnlyOption(this->Group, "DisplayRoomAndZombiesZone", false);
 const BooleanDebugOption FMODRoomType =
 newDebugOnlyOption(this->Group, "FMODRoomType", false);

 public
 RenderOG(IDebugOptionGroup parentGroup) { super(parentGroup, "Render"); }
 }
 }
}
} // namespace options
} // namespace debug
} // namespace zombie
