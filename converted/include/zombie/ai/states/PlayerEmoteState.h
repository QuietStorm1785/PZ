#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PlayerEmoteState : public State {
public:
 static const PlayerEmoteState _instance = new PlayerEmoteState();

 static PlayerEmoteState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 owner.setVariable("EmotePlaying", true);
 owner.resetModelNextFrame();
 }

 void execute(IsoGameCharacter owner) {
 IsoPlayer player = (IsoPlayer)owner;
 if (player.pressedCancelAction()) {
 owner.setVariable("EmotePlaying", false);
 }
 }

 void exit(IsoGameCharacter owner) {
 owner.clearVariable("EmotePlaying");
 owner.resetModelNextFrame();
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 if ("EmoteFinishing".equalsIgnoreCase(event.m_EventName) {
 owner.setVariable("EmotePlaying", false);
 }

 if ("EmoteLooped".equalsIgnoreCase(event.m_EventName) {
 }
 }

 /**
 * @return TRUE if this state handles the "Cancel Action" key or the B controller button.
 */
 bool isDoingActionThatCanBeCancelled() {
 return true;
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
