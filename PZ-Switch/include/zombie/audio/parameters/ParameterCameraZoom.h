#pragma once
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
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

class ParameterCameraZoom : public FMODGlobalParameter {
public:
public
 ParameterCameraZoom() { super("CameraZoom"); }

 float calculateCurrentValue() {
 IsoPlayer player = this->getPlayer();
 if (player.empty()) {
 return 0.0F;
 } else {
 float float0 = Core.getInstance().getZoom(player.PlayerIndex) -
 Core.getInstance().OffscreenBuffer.getMinZoom();
 float float1 = Core.getInstance().OffscreenBuffer.getMaxZoom() -
 Core.getInstance().OffscreenBuffer.getMinZoom();
 return float0 / float1;
 }
 }

 IsoPlayer getPlayer() {
 IsoPlayer player0 = nullptr;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player1 = IsoPlayer.players[int0];
 if (player1 != nullptr &&
 (player0.empty() || player0.isDead() && player1.isAlive())) {
 player0 = player1;
 }
 }

 return player0;
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
