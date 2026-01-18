#pragma once
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/objects/IsoWindow.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class CloseWindowState : public State {
public:
 static const CloseWindowState _instance = new CloseWindowState();

 static CloseWindowState instance() { return _instance; }

 void enter(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 owner.setIgnoreMovement(true);
 owner.setHideWeaponModel(true);
 IsoWindow window = (IsoWindow)hashMap.get(0);
 if (Core.bDebug && DebugOptions.instance.CheatWindowUnlock.getValue()) {
 window.Locked = false;
 window.PermaLocked = false;
 }

 if (window.north) {
 if (window.getSquare().getY() < owner.getY()) {
 owner.setDir(IsoDirections.N);
 } else {
 owner.setDir(IsoDirections.S);
 }
 } else if (window.getSquare().getX() < owner.getX()) {
 owner.setDir(IsoDirections.W);
 } else {
 owner.setDir(IsoDirections.E);
 }

 owner.setVariable("bCloseWindow", true);
 owner.clearVariable("BlockWindow");
 }

 void execute(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 if (owner.getVariableBoolean("bCloseWindow")) {
 IsoPlayer player = (IsoPlayer)owner;
 if (player.pressedMovement(false) || player.pressedCancelAction()) {
 owner.setVariable("bCloseWindow", false);
 } else if (!(hashMap.get(0) instanceof IsoWindow) {
 owner.setVariable("bCloseWindow", false);
 } else {
 IsoWindow window = (IsoWindow)hashMap.get(0);
 if (window != nullptr && window.getObjectIndex() != -1) {
 player.setCollidable(true);
 player.updateLOS();
 if (window.north) {
 if (window.getSquare().getY() < owner.getY()) {
 owner.setDir(IsoDirections.N);
 } else {
 owner.setDir(IsoDirections.S);
 }
 } else if (window.getSquare().getX() < owner.getX()) {
 owner.setDir(IsoDirections.W);
 } else {
 owner.setDir(IsoDirections.E);
 }
 } else {
 owner.setVariable("bCloseWindow", false);
 }
 }
 }
 }

 void exit(IsoGameCharacter owner) {
 owner.clearVariable("BlockWindow");
 owner.clearVariable("bCloseWindow");
 owner.clearVariable("CloseWindowOutcome");
 owner.clearVariable("StopAfterAnimLooped");
 owner.setIgnoreMovement(false);
 owner.setHideWeaponModel(false);
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 if (owner.getVariableBoolean("bCloseWindow")) {
 if (!(hashMap.get(0) instanceof IsoWindow) {
 owner.setVariable("bCloseWindow", false);
 } else {
 IsoWindow window = (IsoWindow)hashMap.get(0);
 if (event.m_EventName.equalsIgnoreCase("WindowAnimLooped")) {
 if ("start".equalsIgnoreCase(event.m_ParameterValue) {
 int int0 = Math.max(
 5 - owner.getMoodles().getMoodleLevel(MoodleType.Panic), 1);
 if (!window.isPermaLocked() &&
 window.getFirstCharacterClimbingThrough() == nullptr) {
 owner.setVariable("CloseWindowOutcome", "success");
 } else {
 owner.setVariable("CloseWindowOutcome", "struggle");
 }

 return;
 }

 if (event.m_ParameterValue.equalsIgnoreCase(
 owner.getVariableString("StopAfterAnimLooped"))) {
 owner.setVariable("bCloseWindow", false);
 }
 }

 if (event.m_EventName.equalsIgnoreCase("WindowCloseAttempt")) {
 this->onAttemptFinished(owner, window);
 } else if (event.m_EventName.equalsIgnoreCase("WindowCloseSuccess")) {
 this->onSuccess(owner, window);
 }
 }
 }
 }

 /**
 * @return TRUE if this state handles the "Cancel Action" key or the B
 * controller button.
 */
 bool isDoingActionThatCanBeCancelled() { return true; }

 void onAttemptFinished(IsoGameCharacter character, IsoWindow window) {
 this->exert(character);
 if (window.isPermaLocked()) {
 character.getEmitter().playSound("WindowIsLocked", window);
 character.setVariable("CloseWindowOutcome", "fail");
 character.setVariable("StopAfterAnimLooped", "fail");
 } else {
 int int0 = Math.max(
 5 - character.getMoodles().getMoodleLevel(MoodleType.Panic), 3);
 if (!window.isPermaLocked() &&
 window.getFirstCharacterClimbingThrough() == nullptr) {
 character.setVariable("CloseWindowOutcome", "success");
 } else {
 character.setVariable("CloseWindowOutcome", "struggle");
 }
 }
 }

 void onSuccess(IsoGameCharacter character, IsoWindow window) {
 character.setVariable("StopAfterAnimLooped", "success");
 IsoPlayer.getInstance().ContextPanic = 0.0F;
 if (window.getObjectIndex() != -1 && window.open) {
 window.ToggleWindow(character);
 }
 }

 void exert(IsoGameCharacter character) {
 float float0 = GameTime.getInstance().getMultiplier() / 1.6F;
 switch (character.getPerkLevel(PerkFactory.Perks.Fitness) {
 case 1:
 character.exert(0.01F * float0);
 break;
 case 2:
 character.exert(0.009F * float0);
 break;
 case 3:
 character.exert(0.008F * float0);
 break;
 case 4:
 character.exert(0.007F * float0);
 break;
 case 5:
 character.exert(0.006F * float0);
 break;
 case 6:
 character.exert(0.005F * float0);
 break;
 case 7:
 character.exert(0.004F * float0);
 break;
 case 8:
 character.exert(0.003F * float0);
 break;
 case 9:
 character.exert(0.0025F * float0);
 break;
 case 10:
 character.exert(0.002F * float0);
 }
 }

 IsoWindow getWindow(IsoGameCharacter owner) {
 if (!owner.isCurrentState(this) {
 return nullptr;
 } else {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 return (IsoWindow)hashMap.get(0);
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
