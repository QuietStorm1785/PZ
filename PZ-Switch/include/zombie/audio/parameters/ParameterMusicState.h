#pragma once
#include "zombie/audio/FMODGlobalParameter.h"
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

class ParameterMusicState : public FMODGlobalParameter {
public:
private
 ParameterMusicState.State state = ParameterMusicState.State.MainMenu;

public
 ParameterMusicState() { super("MusicState"); }

 float calculateCurrentValue() { return this->state.label; }

 void setState(ParameterMusicState.State _state) { this->state = _state; }

public
 static enum State {
 MainMenu(0), Loading(1), InGame(2), PauseMenu(3), Tutorial(4);

 const int label;

 private State(int int1){this->label = int1;}
}
} // namespace parameters
} // namespace audio
} // namespace zombie
} // namespace zombie
