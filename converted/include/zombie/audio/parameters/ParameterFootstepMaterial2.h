#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/objects/IsoBrokenGlass.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterFootstepMaterial2 : public FMODLocalParameter {
public:
 const IsoGameCharacter character;

 public ParameterFootstepMaterial2(IsoGameCharacter _character) {
 super("FootstepMaterial2");
 this->character = _character;
 }

 float calculateCurrentValue() {
 return this->getMaterial().label;
 }

 private ParameterFootstepMaterial2.FootstepMaterial2 getMaterial() {
 if (this->character.getCurrentSquare() == nullptr) {
 return ParameterFootstepMaterial2.FootstepMaterial2.None;
 } else {
 IsoBrokenGlass brokenGlass = this->character.getCurrentSquare().getBrokenGlass();
 if (brokenGlass != nullptr) {
 return ParameterFootstepMaterial2.FootstepMaterial2.BrokenGlass;
 } else {
 float float0 = this->character.getCurrentSquare().getPuddlesInGround();
 if (float0 > 0.5F) {
 return ParameterFootstepMaterial2.FootstepMaterial2.PuddleDeep;
 } else {
 return float0 > 0.1F ? ParameterFootstepMaterial2.FootstepMaterial2.PuddleShallow : ParameterFootstepMaterial2.FootstepMaterial2.None;
 }
 }
 }
 }

 static enum FootstepMaterial2 {
 None(0),
 BrokenGlass(1),
 PuddleShallow(2),
 PuddleDeep(3);

 const int label;

 private FootstepMaterial2(int int1) {
 this->label = int1;
 }
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
