#pragma once
#include "zombie/audio/FMODLocalParameter.h"
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

class ParameterPlayerHealth : public FMODLocalParameter {
public:
 const IsoPlayer player;

public
 ParameterPlayerHealth(IsoPlayer _player) {
 super("PlayerHealth");
 this->player = _player;
 }

 float calculateCurrentValue() {
 return PZMath.clamp(this->player.getHealth() / 100.0F, 0.0F, 1.0F);
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
