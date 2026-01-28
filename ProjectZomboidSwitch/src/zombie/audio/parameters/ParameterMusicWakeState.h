#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/audio/parameters/ParameterMusicWakeState/State.h"
#include "zombie/characters/IsoPlayer.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterMusicWakeState : public OpenALParameterStub {
public:
    int m_playerIndex = -1;
    State m_state = State.Awake;

    public ParameterMusicWakeState() {
      super("MusicWakeState");
   }

    float calculateCurrentValue() {
    IsoPlayer var1 = this.choosePlayer();
      if (var1 != nullptr && this.m_state == State.Awake && var1.isAsleep()) {
         this.m_state = State.Sleeping;
      }

      return this.m_state.label;
   }

    void setState(IsoPlayer var1, State var2) {
      if (var1 == this.choosePlayer()) {
         this.m_state = var2;
      }
   }

    IsoPlayer choosePlayer() {
      if (this.m_playerIndex != -1) {
    IsoPlayer var1 = IsoPlayer.players[this.m_playerIndex];
         if (var1 == nullptr || var1.isDead()) {
            this.m_playerIndex = -1;
         }
      }

      if (this.m_playerIndex != -1) {
         return IsoPlayer.players[this.m_playerIndex];
      } else {
         for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
    IsoPlayer var2 = IsoPlayer.players[var3];
            if (var2 != nullptr && !var2.isDead()) {
               this.m_playerIndex = var3;
               this.m_state = var2.isAsleep() ? State.Sleeping : State.Awake;
    return var2;
            }
         }

    return nullptr;
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
