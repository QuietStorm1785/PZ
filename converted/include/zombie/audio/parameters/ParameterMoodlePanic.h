#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Moodles/MoodleType.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterMoodlePanic : public FMODGlobalParameter {
public:
 public ParameterMoodlePanic() {
 super("MoodlePanic");
 }

 float calculateCurrentValue() {
 IsoGameCharacter character = this->getCharacter();
 return character = = nullptr ? 0.0F : character.getMoodles().getMoodleLevel(MoodleType.Panic) / 4.0F;
 }

 IsoGameCharacter getCharacter() {
 IsoPlayer player0 = nullptr;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player1 = IsoPlayer.players[int0];
 if (player1 != nullptr && (player0 == nullptr || player0.isDead() && player1.isAlive() || player0.Traits.Deaf.isSet() && !player1.Traits.Deaf.isSet())) {
 player0 = player1;
 }
 }

 return player0;
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
