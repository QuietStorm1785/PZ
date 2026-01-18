#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Core.h"
#include "zombie/gameStates/GameState.h"
#include "zombie/gameStates/GameStateMachine.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/EditVehicleState.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
namespace editor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapEditorState : public GameState {
public:
  static WorldMapEditorState instance;
private
  EditVehicleState.LuaEnvironment m_luaEnv;
  bool bExit = false;
private
  final ArrayList<UIElement> m_gameUI = std::make_unique<ArrayList<>>();
private
  final ArrayList<UIElement> m_selfUI = std::make_unique<ArrayList<>>();
  bool m_bSuspendUI;
  KahluaTable m_table = null;

  void enter() {
    instance = this;
    this.load();
    if (this.m_luaEnv == nullptr) {
      this.m_luaEnv = new EditVehicleState.LuaEnvironment(
          LuaManager.platform, LuaManager.converterManager, LuaManager.env);
    }

    this.saveGameUI();
    if (this.m_selfUI.size() == 0) {
      this.m_luaEnv.caller.pcall(
          this.m_luaEnv.thread,
          this.m_luaEnv.env.rawget("WorldMapEditor_InitUI"), this);
      if (this.m_table != nullptr && this.m_table.getMetatable() != nullptr) {
        this.m_table.getMetatable().rawset("_LUA_RELOADED_CHECK",
                                           Boolean.FALSE);
      }
    } else {
      UIManager.UI.addAll(this.m_selfUI);
      this.m_luaEnv.caller.pcall(this.m_luaEnv.thread,
                                 this.m_table.rawget("showUI"), this.m_table);
    }

    this.bExit = false;
  }

  void yield() { this.restoreGameUI(); }

  void reenter() { this.saveGameUI(); }

  void exit() {
    this.save();
    this.restoreGameUI();
  }

  void render() {
    uint8_t byte0 = 0;
    Core.getInstance().StartFrame(byte0, true);
    this.renderScene();
    Core.getInstance().EndFrame(byte0);
    Core.getInstance().RenderOffScreenBuffer();
    UIManager.useUIFBO = Core.getInstance().supportsFBO() && Core.OptionUIFBO;
    if (Core.getInstance().StartFrameUI()) {
      this.renderUI();
    }

    Core.getInstance().EndFrameUI();
  }

public
  GameStateMachine.StateAction update() {
    if (!this.bExit && !GameKeyboard.isKeyPressed(65)) {
      this.updateScene();
      return GameStateMachine.StateAction.Remain;
    } else {
      return GameStateMachine.StateAction.Continue;
    }
  }

  static WorldMapEditorState checkInstance() {
    if (instance != nullptr) {
      if (instance.m_table != nullptr &&
          instance.m_table.getMetatable() != nullptr) {
        if (instance.m_table.getMetatable().rawget("_LUA_RELOADED_CHECK") ==
            nullptr) {
          instance = nullptr;
        }
      } else {
        instance = nullptr;
      }
    }

    return instance = = null ? new WorldMapEditorState() : instance;
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

  void updateScene() {}

  void renderScene() {}

  void renderUI() { UIManager.render(); }

  void setTable(KahluaTable table) { this.m_table = table; }

  void *fromLua0(const std::string &string) {
    uint8_t byte0 = -1;
    switch (string.hashCode()) {
    case 3127582:
      if (string == "exit")) {
                    byte0 = 0;
                }
    default:
      switch (byte0) {
      case 0:
        this.bExit = true;
        return null;
      default:
        throw new IllegalArgumentException("unhandled \"" + string + "\"");
      }
    }
  }

  void save() {}

  void load() {}
}
} // namespace editor
} // namespace worldMap
} // namespace zombie
