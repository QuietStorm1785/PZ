#pragma once
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoPlayer.h"
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

class ParameterLocalPlayer : public FMODLocalParameter {
public:
 const IsoPlayer player;

public
 ParameterLocalPlayer(IsoPlayer _player) {
 super("LocalPlayer");
 this->player = _player;
 }

 float calculateCurrentValue() {
 return this->player.isLocalPlayer() ? 1.0F : 0.0F;
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
