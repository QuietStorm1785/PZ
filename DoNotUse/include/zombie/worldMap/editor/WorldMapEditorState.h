#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Core.h"
#include "zombie/gameStates/GameState.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/EditVehicleState/LuaEnvironment.h"

namespace zombie {
namespace worldMap {
namespace editor {


class WorldMapEditorState : public GameState {
public:
    static WorldMapEditorState instance;
    LuaEnvironment m_luaEnv;
    bool bExit = false;
   private const std::vector<UIElement> m_gameUI = std::make_unique<std::vector<>>();
   private const std::vector<UIElement> m_selfUI = std::make_unique<std::vector<>>();
    bool m_bSuspendUI;
    KahluaTable m_table = nullptr;

    void enter() {
      instance = this;
      this.load();
      if (this.m_luaEnv == nullptr) {
         this.m_luaEnv = std::make_shared<LuaEnvironment>(LuaManager.platform, LuaManager.converterManager, LuaManager.env);
      }

      this.saveGameUI();
      if (this.m_selfUI.size() == 0) {
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_luaEnv.env.rawget("WorldMapEditor_InitUI"), this);
         if (this.m_table != nullptr && this.m_table.getMetatable() != nullptr) {
            this.m_table.getMetatable().rawset("_LUA_RELOADED_CHECK", bool.FALSE);
         }
      } else {
         UIManager.UI.addAll(this.m_selfUI);
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_table.rawget("showUI"), this.m_table);
      }

      this.bExit = false;
   }

    void yield() {
      this.restoreGameUI();
   }

    void reenter() {
      this.saveGameUI();
   }

    void exit() {
      this.save();
      this.restoreGameUI();
   }

    void render() {
    uint8_t var1 = 0;
      Core.getInstance().StartFrame(var1, true);
      this.renderScene();
      Core.getInstance().EndFrame(var1);
      Core.getInstance().RenderOffScreenBuffer();
      UIManager.useUIFBO = Core.getInstance().supportsFBO() && Core.OptionUIFBO;
      if (Core.getInstance().StartFrameUI()) {
         this.renderUI();
      }

      Core.getInstance().EndFrameUI();
   }

    StateAction update() {
      if (!this.bExit && !GameKeyboard.isKeyPressed(65)) {
         this.updateScene();
         return StateAction.Remain;
      } else {
         return StateAction.Continue;
      }
   }

    static WorldMapEditorState checkInstance() {
      if (instance != nullptr) {
         if (instance.m_table != nullptr && instance.m_table.getMetatable() != nullptr) {
            if (instance.m_table.getMetatable().rawget("_LUA_RELOADED_CHECK") == nullptr) {
               instance = nullptr;
            }
         } else {
            instance = nullptr;
         }
      }

    return instance = = nullptr ? std::make_shared<WorldMapEditorState>() : instance;
   }

    void saveGameUI() {
      this.m_gameUI.clear();
      this.m_gameUI.addAll(UIManager.UI);
      UIManager.UI.clear();
      this.m_bSuspendUI = UIManager.bSuspend;
      UIManager.bSuspend = false;
      UIManager.setShowPausedMessage(false);
      UIManager.defaultthread = this.m_luaEnv.thread;
   }

    void restoreGameUI() {
      this.m_selfUI.clear();
      this.m_selfUI.addAll(UIManager.UI);
      UIManager.UI.clear();
      UIManager.UI.addAll(this.m_gameUI);
      UIManager.bSuspend = this.m_bSuspendUI;
      UIManager.setShowPausedMessage(true);
      UIManager.defaultthread = LuaManager.thread;
   }

    void updateScene() {
   }

    void renderScene() {
   }

    void renderUI() {
      UIManager.render();
   }

    void setTable(KahluaTable var1) {
      this.m_table = var1;
   }

    void* fromLua0(const std::string& var1) {
    uint8_t var3 = -1;
      switch (var1.hashCode()) {
         case 3127582:
            if (var1 == "exit")) {
               var3 = 0;
            }
         default:
            switch (var3) {
               case 0:
                  this.bExit = true;
    return nullptr;
               default:
                  throw IllegalArgumentException("unhandled \"" + var1 + "\"");
            }
      }
   }

    void save() {
   }

    void load() {
   }
}
} // namespace editor
} // namespace worldMap
} // namespace zombie
