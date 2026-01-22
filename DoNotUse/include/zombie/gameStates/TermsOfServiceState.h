#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/Core.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace gameStates {


class TermsOfServiceState : public GameState {
public:
    bool bExit = false;
    bool bCreated = false;

    void enter() {
      LuaEventManager.triggerEvent("OnGameStateEnter", this);
      if (!this.bCreated) {
         this.bExit = true;
      }
   }

    void exit() {
      UIManager.clearArrays();
   }

    StateAction update() {
      return this.bExit ? StateAction.Continue : StateAction.Remain;
   }

    void render() {
      Core.getInstance().StartFrame();
      Core.getInstance().EndFrame();
      if (Core.getInstance().StartFrameUI()) {
         UIManager.render();
      }

      Core.getInstance().EndFrameUI();
   }

    void* fromLua0(const std::string& var1) {
      switch (var1) {
         case "created":
            this.bCreated = true;
    return nullptr;
         case "exit":
            this.bExit = true;
    return nullptr;
         default:
            throw IllegalArgumentException("unhandled \"" + var1 + "\"");
      }
   }
}
} // namespace gameStates
} // namespace zombie
