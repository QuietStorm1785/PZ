#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace gameStates {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class GameState {
public:
 void enter() {
 }

 void exit() {
 }

 void render() {
 }

 GameState redirectState() {
 return nullptr;
 }

 public GameStateMachine.StateAction update() {
 return GameStateMachine.StateAction.Continue;
 }

 void yield() {
 }

 void reenter() {
 }
}
} // namespace gameStates
} // namespace zombie
