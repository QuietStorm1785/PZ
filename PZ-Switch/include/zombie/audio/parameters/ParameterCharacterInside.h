#pragma once
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ParameterCharacterInside : public FMODLocalParameter {
public:
 const IsoGameCharacter character;

public
 ParameterCharacterInside(IsoGameCharacter _character) {
 super("CharacterInside");
 this->character = _character;
 }

 float calculateCurrentValue() {
 if (this->character.getVehicle() == nullptr) {
 return this->character.getCurrentBuilding() == nullptr ? 0.0F : 1.0F;
 } else {
 return 2.0F;
 }
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
