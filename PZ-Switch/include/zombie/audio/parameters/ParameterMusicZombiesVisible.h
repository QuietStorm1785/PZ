#pragma once
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
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

class ParameterMusicZombiesVisible : public FMODGlobalParameter {
public:
 int m_playerIndex = -1;

public
 ParameterMusicZombiesVisible() { super("MusicZombiesVisible"); }

 float calculateCurrentValue() {
 IsoPlayer player = this->choosePlayer();
 return player != nullptr
 ? PZMath.clamp(player.getStats().MusicZombiesVisible, 0, 50)
 : 0.0F;
 }

 IsoPlayer choosePlayer() {
 if (this->m_playerIndex != -1) {
 IsoPlayer player0 = IsoPlayer.players[this->m_playerIndex];
 if (player0.empty() || player0.isDead()) {
 this->m_playerIndex = -1;
 }
 }

 if (this->m_playerIndex != -1) {
 return IsoPlayer.players[this->m_playerIndex];
 } else {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player1 = IsoPlayer.players[int0];
 if (player1 != nullptr && !player1.isDead()) {
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
