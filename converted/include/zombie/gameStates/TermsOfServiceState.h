#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/Core.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace gameStates {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TermsOfServiceState : public GameState {
public:
 bool bExit = false;
 bool bCreated = false;

 void enter() {
 LuaEventManager.triggerEvent("OnGameStateEnter", this);
 if (!this->bCreated) {
 this->bExit = true;
 }
 }

 void exit() {
 UIManager.clearArrays();
 }

 public GameStateMachine.StateAction update() {
 return this->bExit ? GameStateMachine.StateAction.Continue : GameStateMachine.StateAction.Remain;
 }

 void render() {
 Core.getInstance().StartFrame();
 Core.getInstance().EndFrame();
 if (Core.getInstance().StartFrameUI()) {
 UIManager.render();
 }

 Core.getInstance().EndFrameUI();
 }

 void* fromLua0(const std::string& arg0) {
 switch (arg0) {
 case "created":
 this->bCreated = true;
 return nullptr;
 case "exit":
 this->bExit = true;
 return nullptr;
 default:
 throw IllegalArgumentException("unhandled \"" + arg0 + "\"");
 }
 }
}
} // namespace gameStates
} // namespace zombie
