#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/characters/IsoPlayer.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterHardOfHearing : public FMODGlobalParameter {
public:
 int m_playerIndex = -1;

 public ParameterHardOfHearing() {
 super("HardOfHearing");
 }

 float calculateCurrentValue() {
 IsoPlayer player = this->choosePlayer();
 if (player != nullptr) {
 return player.getCharacterTraits().HardOfHearing.isSet() ? 1.0F : 0.0F;
 } else {
 return 0.0F;
 }
 }

 IsoPlayer choosePlayer() {
 if (this->m_playerIndex != -1) {
 IsoPlayer player0 = IsoPlayer.players[this->m_playerIndex];
 if (player0 == nullptr) {
 this->m_playerIndex = -1;
 }
 }

 if (this->m_playerIndex != -1) {
 return IsoPlayer.players[this->m_playerIndex];
 } else {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player1 = IsoPlayer.players[int0];
 if (player1 != nullptr) {
 this->m_playerIndex = int0;
 return player1;
 }
 }

 return nullptr;
 }
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
