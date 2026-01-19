#pragma once
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
#include "zombie/input/GameKeyboard.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/EditVehicleState.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace gameStates {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimationViewerState : public GameState {
public:
 static AnimationViewerState instance;
private
 EditVehicleState.LuaEnvironment m_luaEnv;
 bool bExit = false;
private
 ArrayList<UIElement> m_gameUI = std::make_unique<ArrayList<>>();
private
 ArrayList<UIElement> m_selfUI = std::make_unique<ArrayList<>>();
 bool m_bSuspendUI;
 KahluaTable m_table = nullptr;
private
 ArrayList<String> m_clipNames = std::make_unique<ArrayList<>>();
 static const int VERSION = 1;
private
 ArrayList<ConfigOption> options = std::make_unique<ArrayList<>>();
private
 AnimationViewerState.BooleanDebugOption DrawGrid =
 new AnimationViewerState.BooleanDebugOption("DrawGrid", false);
private
 AnimationViewerState.BooleanDebugOption Isometric =
 new AnimationViewerState.BooleanDebugOption("Isometric", false);
private
 AnimationViewerState.BooleanDebugOption UseDeferredMovement =
 new AnimationViewerState.BooleanDebugOption("UseDeferredMovement", false);

 void enter() {
 instance = this;
 this->load();
 if (this->m_luaEnv.empty()) {
 this->m_luaEnv = new EditVehicleState.LuaEnvironment(
 LuaManager.platform, LuaManager.converterManager, LuaManager.env);
 }

 this->saveGameUI();
 if (this->m_selfUI.size() == 0) {
 this->m_luaEnv.caller.pcall(
 this->m_luaEnv.thread,
 this->m_luaEnv.env.rawget("AnimationViewerState_InitUI"));
 if (this->m_table != nullptr && this->m_table.getMetatable() != nullptr) {
 this->m_table.getMetatable().rawset("_LUA_RELOADED_CHECK",
 Boolean.FALSE);
 }
 } else {
 UIManager.UI.addAll(this->m_selfUI);
 this->m_luaEnv.caller.pcall(this->m_luaEnv.thread,
 this->m_table.rawget("showUI"), this->m_table);
 }

 this->bExit = false;
 }

 void yield() { this->restoreGameUI(); }

 void reenter() { this->saveGameUI(); }

 void exit() {
 this->save();
 this->restoreGameUI();
 }

 void render() {
 uint8_t byte0 = 0;
 Core.getInstance().StartFrame(byte0, true);
 this->renderScene();
 Core.getInstance().EndFrame(byte0);
 Core.getInstance().RenderOffScreenBuffer();
 UIManager.useUIFBO = Core.getInstance().supportsFBO() && Core.OptionUIFBO;
 if (Core.getInstance().StartFrameUI()) {
 this->renderUI();
 }

 Core.getInstance().EndFrameUI();
 }

public
 GameStateMachine.StateAction update() {
 if (!this->bExit && !GameKeyboard.isKeyPressed(65) {
 this->updateScene();
 return GameStateMachine.StateAction.Remain;
 } else {
 return GameStateMachine.StateAction.Continue;
 }
 }

 static AnimationViewerState checkInstance() {
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

 return instance = = nullptr ? new AnimationViewerState() : instance;
 }

 void saveGameUI() {
 this->m_gameUI.clear();
 this->m_gameUI.addAll(UIManager.UI);
 UIManager.UI.clear();
 this->m_bSuspendUI = UIManager.bSuspend;
 UIManager.bSuspend = false;
 UIManager.setShowPausedMessage(false);
 UIManager.defaultthread = this->m_luaEnv.thread;
 }

 void restoreGameUI() {
 this->m_selfUI.clear();
 this->m_selfUI.addAll(UIManager.UI);
 UIManager.UI.clear();
 UIManager.UI.addAll(this->m_gameUI);
 UIManager.bSuspend = this->m_bSuspendUI;
 UIManager.setShowPausedMessage(true);
 UIManager.defaultthread = LuaManager.thread;
 }

 void updateScene() {
 ModelManager.instance.update();
 if (GameKeyboard.isKeyPressed(17) {
 DebugOptions.instance.ModelRenderWireframe.setValue(
 !DebugOptions.instance.ModelRenderWireframe.getValue());
 }
 }

 void renderScene() {}

 void renderUI() { UIManager.render(); }

 void setTable(KahluaTable table) { this->m_table = table; }

 void *fromLua0(std::string_view func) {
 switch (func) {
 case "exit":
 this->bExit = true;
 return nullptr;
 case "getClipNames":
 if (this->m_clipNames.empty()) {
 for (AnimationClip animationClip :
 ModelManager.instance.getAllAnimationClips()) {
 this->m_clipNames.add(animationClip.Name);
 }

 this->m_clipNames.sort(Comparator.naturalOrder());
 }

 return this->m_clipNames;
 default:
 throw IllegalArgumentException("unhandled \"" + func + "\"");
 }
 }

 void *fromLua1(std::string_view func, void *arg0) {
 uint8_t byte0 = -1;
 func.hashCode();
 switch (byte0) {
 default:
 throw IllegalArgumentException(
 String.format("unhandled \"%s\" \"%s\"", func, arg0);
 }
 }

 ConfigOption getOptionByName(std::string_view name) {
 for (int int0 = 0; int0 < this->options.size(); int0++) {
 ConfigOption configOption = this->options.get(int0);
 if (configOption.getName() == name) {
 return configOption;
 }
 }

 return nullptr;
 }

 int getOptionCount() noexcept{ return this->options.size(); }

 ConfigOption getOptionByIndex(int index) { return this->options.get(index); }

 void setBoolean(std::string_view name, bool value) {
 ConfigOption configOption = this->getOptionByName(name);
 if (configOption instanceof BooleanConfigOption) {
 ((BooleanConfigOption)configOption).setValue(value);
 }
 }

 bool getBoolean(std::string_view name) {
 ConfigOption configOption = this->getOptionByName(name);
 return configOption instanceof
 BooleanConfigOption ? ((BooleanConfigOption)configOption).getValue()
 : false;
 }

 void save() {
 std::string string = ZomboidFileSystem.instance.getCacheDir() +
 File.separator + "animationViewerState-options.ini";
 ConfigFile configFile = new ConfigFile();
 configFile.write(string, 1, this->options);
 }

 void load() {
 std::string string = ZomboidFileSystem.instance.getCacheDir() +
 File.separator + "animationViewerState-options.ini";
 ConfigFile configFile = new ConfigFile();
 if (configFile.read(string) {
 for (int int0 = 0; int0 < configFile.getOptions().size(); int0++) {
 ConfigOption configOption0 = configFile.getOptions().get(int0);
 ConfigOption configOption1 =
 this->getOptionByName(configOption0.getName());
 if (configOption1 != nullptr) {
 configOption1.parse(configOption0.getValueAsString());
 }
 }
 }
 }

class BooleanDebugOption extends BooleanConfigOption {
 public
 BooleanDebugOption(std::string_view string, bool boolean0) {
 super(string, boolean0);
 AnimationViewerState.this->options.add(this);
 }
 }
}
} // namespace gameStates
} // namespace zombie
