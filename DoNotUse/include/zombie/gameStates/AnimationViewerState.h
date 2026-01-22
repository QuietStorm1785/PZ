#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/gameStates/AnimationViewerState/BooleanDebugOption.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/EditVehicleState/LuaEnvironment.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace gameStates {


class AnimationViewerState : public GameState {
public:
    static AnimationViewerState instance;
    LuaEnvironment m_luaEnv;
    bool bExit = false;
   private const std::vector<UIElement> m_gameUI = std::make_unique<std::vector<>>();
   private const std::vector<UIElement> m_selfUI = std::make_unique<std::vector<>>();
    bool m_bSuspendUI;
    KahluaTable m_table = nullptr;
   private const std::vector<std::string> m_clipNames = std::make_unique<std::vector<>>();
    static const int VERSION = 1;
   private const std::vector<ConfigOption> options = std::make_unique<std::vector<>>();
    BooleanDebugOption DrawGrid = std::make_shared<BooleanDebugOption>(this, "DrawGrid", false);
    BooleanDebugOption Isometric = std::make_shared<BooleanDebugOption>(this, "Isometric", false);
    BooleanDebugOption UseDeferredMovement = std::make_shared<BooleanDebugOption>(this, "UseDeferredMovement", false);

    void enter() {
      instance = this;
      this.load();
      if (this.m_luaEnv == nullptr) {
         this.m_luaEnv = std::make_shared<LuaEnvironment>(LuaManager.platform, LuaManager.converterManager, LuaManager.env);
      }

      this.saveGameUI();
      if (this.m_selfUI.size() == 0) {
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_luaEnv.env.rawget("AnimationViewerState_InitUI"), new Object[0]);
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

    static AnimationViewerState checkInstance() {
      if (instance != nullptr) {
         if (instance.m_table != nullptr && instance.m_table.getMetatable() != nullptr) {
            if (instance.m_table.getMetatable().rawget("_LUA_RELOADED_CHECK") == nullptr) {
               instance = nullptr;
            }
         } else {
            instance = nullptr;
         }
      }

    return instance = = nullptr ? std::make_shared<AnimationViewerState>() : instance;
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
      ModelManager.instance.update();
      if (GameKeyboard.isKeyPressed(17)) {
         DebugOptions.instance.ModelRenderWireframe.setValue(!DebugOptions.instance.ModelRenderWireframe.getValue());
      }
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
      switch (var1) {
         case "exit":
            this.bExit = true;
    return nullptr;
         case "getClipNames":
            if (this.m_clipNames.empty()) {
               for (AnimationClip var6 : ModelManager.instance.getAllAnimationClips()) {
                  this.m_clipNames.push_back(var6.Name);
               }

               this.m_clipNames.sort(Comparator.naturalOrder());
            }

            return this.m_clipNames;
         default:
            throw IllegalArgumentException("unhandled \"" + var1 + "\"");
      }
   }

    void* fromLua1(const std::string& var1, void* var2) {
    uint8_t var4 = -1;
      var1.hashCode();
      switch (var4) {
         default:
            throw IllegalArgumentException(std::string.format("unhandled \"%s\" \"%s\"", var1, var2));
      }
   }

    ConfigOption getOptionByName(const std::string& var1) {
      for (int var2 = 0; var2 < this.options.size(); var2++) {
    ConfigOption var3 = this.options.get(var2);
         if (var3.getName() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    int getOptionCount() {
      return this.options.size();
   }

    ConfigOption getOptionByIndex(int var1) {
      return this.options.get(var1);
   }

    void setBoolean(const std::string& var1, bool var2) {
    ConfigOption var3 = this.getOptionByName(var1);
      if (dynamic_cast<BooleanConfigOption*>(var3) != nullptr) {
         ((BooleanConfigOption)var3).setValue(var2);
      }
   }

    bool getBoolean(const std::string& var1) {
    ConfigOption var2 = this.getOptionByName(var1);
      return dynamic_cast<BooleanConfigOption*>(var2) != nullptr ? ((BooleanConfigOption)var2).getValue() : false;
   }

    void save() {
    std::string var1 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "animationViewerState-options.ini";
    ConfigFile var2 = std::make_shared<ConfigFile>();
      var2.write(var1, 1, this.options);
   }

    void load() {
    std::string var1 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "animationViewerState-options.ini";
    ConfigFile var2 = std::make_shared<ConfigFile>();
      if (var2.read(var1)) {
         for (int var3 = 0; var3 < var2.getOptions().size(); var3++) {
    ConfigOption var4 = (ConfigOption)var2.getOptions().get(var3);
    ConfigOption var5 = this.getOptionByName(var4.getName());
            if (var5 != nullptr) {
               var5.parse(var4.getValueAsString());
            }
         }
      }
   }
}
} // namespace gameStates
} // namespace zombie
