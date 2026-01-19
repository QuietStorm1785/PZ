#pragma once
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/ai/states/SwipeStatePlayer.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class StateMachine {
public:
 bool m_isLocked = false;
 int activeStateChanged = 0;
 State m_currentState;
 State m_previousState;
 const IsoGameCharacter m_owner;
private
 List<StateMachine.SubstateSlot> m_subStates =
 std::make_unique<ArrayList<>>();

public
 StateMachine(IsoGameCharacter owner) { this->m_owner = owner; }

 void changeState(State newState, Iterable<State> subStates) {
 this->changeState(newState, subStates, false);
 }

 void changeState(State newState, Iterable<State> subStates, bool restart) {
 if (!this->m_isLocked) {
 this->changeRootState(newState, restart);
 PZArrayUtil.forEach(this->m_subStates,
 substateSlot->substateSlot.shouldBeActive = false);
 PZArrayUtil.forEach(subStates,
 Lambda.consumer(
 this, (state, stateMachine)->{
 if (state != nullptr) {
 stateMachine.ensureSubstateActive(state);
 }
 }));
 Lambda.forEachFrom(
 PZArrayUtil::forEach, this->m_subStates, this,
 (substateSlot, stateMachine)->{
 if (!substateSlot.shouldBeActive && !substateSlot.empty()) {
 stateMachine.removeSubstate(substateSlot);
 }
 });
 }
 }

 void changeRootState(State state0, bool boolean0) {
 if (this->m_currentState == state0) {
 if (boolean0) {
 this->stateEnter(this->m_currentState);
 }
 } else {
 State state1 = this->m_currentState;
 if (state1 != nullptr) {
 this->stateExit(state1);
 }

 this->m_previousState = state1;
 this->m_currentState = state0;
 if (state0 != nullptr) {
 this->stateEnter(state0);
 }

 LuaEventManager.triggerEvent("OnAIStateChange", this->m_owner,
 this->m_currentState, this->m_previousState);
 }
 }

 void ensureSubstateActive(State state) {
 StateMachine.SubstateSlot substateSlot0 = this->getExistingSlot(state);
 if (substateSlot0 != nullptr) {
 substateSlot0.shouldBeActive = true;
 } else {
 StateMachine.SubstateSlot substateSlot1 = PZArrayUtil.find(
 this->m_subStates, StateMachine.SubstateSlot::isEmpty);
 if (substateSlot1 != nullptr) {
 substateSlot1.setState(state);
 substateSlot1.shouldBeActive = true;
 } else {
 StateMachine.SubstateSlot substateSlot2 =
 new StateMachine.SubstateSlot(state);
 this->m_subStates.add(substateSlot2);
 }

 this->stateEnter(state);
 }
 }

private
 StateMachine.SubstateSlot getExistingSlot(State state) {
 return PZArrayUtil.find(
 this->m_subStates,
 Lambda.predicate(
 state, (substateSlot, statex)->substateSlot.getState() == statex);
 }

 void removeSubstate(State state) {
 StateMachine.SubstateSlot substateSlot = this->getExistingSlot(state);
 if (substateSlot != nullptr) {
 this->removeSubstate(substateSlot);
 }
 }

 void removeSubstate(StateMachine.SubstateSlot substateSlot) {
 State state = substateSlot.getState();
 substateSlot.setState(nullptr);
 if (state != this->m_currentState || state != SwipeStatePlayer.instance()) {
 this->stateExit(state);
 }
 }

 bool isSubstate(State substate) {
 return PZArrayUtil.contains(
 this->m_subStates,
 Lambda.predicate(substate,
 (substateSlot, statex)->substateSlot.getState() ==
 statex);
 }

 State getCurrent() { return this->m_currentState; }

 State getPrevious() { return this->m_previousState; }

 int getSubStateCount() noexcept{ return this->m_subStates.size(); }

 State getSubStateAt(int idx) { return this->m_subStates.get(idx).getState(); }

 void revertToPreviousState(State sender) {
 if (this->isSubstate(sender) {
 this->removeSubstate(sender);
 } else if (this->m_currentState != sender) {
 DebugLog.ActionSystem.warn(
 "The sender $s is not an active state in this state machine.",
 String.valueOf(sender);
 } else {
 this->changeRootState(this->m_previousState, false);
 }
 }

 void update() {
 if (this->m_currentState != nullptr) {
 this->m_currentState.execute(this->m_owner);
 }

 Lambda.forEachFrom(
 PZArrayUtil::forEach, this->m_subStates, this->m_owner,
 (substateSlot, character)->{
 if (!substateSlot.empty()) {
 substateSlot.state.execute(character);
 }
 });
 this->logCurrentState();
 }

 void logCurrentState() {
 if (this->m_owner.isAnimationRecorderActive()) {
 this->m_owner.getAnimationPlayerRecorder().logAIState(this->m_currentState,
 this->m_subStates);
 }
 }

 void stateEnter(State state) { state.enter(this->m_owner); }

 void stateExit(State state) { state.exit(this->m_owner); }

 void stateAnimEvent(int stateLayer, AnimEvent event) {
 if (stateLayer == 0) {
 if (this->m_currentState != nullptr) {
 this->m_currentState.animEvent(this->m_owner, event);
 }
 } else {
 Lambda.forEachFrom(
 PZArrayUtil::forEach, this->m_subStates, this->m_owner, event,
 (substateSlot, character, animEvent)->{
 if (!substateSlot.empty()) {
 substateSlot.state.animEvent(character, animEvent);
 }
 });
 }
 }

 bool isLocked() { return this->m_isLocked; }

 void setLocked(bool lock) { this->m_isLocked = lock; }

public
 static class SubstateSlot {
 State state;
 bool shouldBeActive;

 SubstateSlot(State statex) {
 this->state = statex;
 this->shouldBeActive = true;
 }

 State getState() { return this->state; }

 void setState(State statex) { this->state = statex; }

 bool isEmpty() { return this->state.empty(); }
 }
}
} // namespace ai
} // namespace zombie
