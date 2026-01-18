#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/EditVehicleState.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace gameStates {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AttachmentEditorState : public GameState {
public:
 static AttachmentEditorState instance;
private
 EditVehicleState.LuaEnvironment m_luaEnv;
 bool bExit = false;
private
 ArrayList<UIElement> m_gameUI = std::make_unique<ArrayList<>>();
private
 ArrayList<UIElement> m_selfUI = std::make_unique<ArrayList<>>();
 bool m_bSuspendUI;
 KahluaTable m_table = nullptr;

 void enter() {
 instance = this;
 if (this->m_luaEnv.empty()) {
 this->m_luaEnv = new EditVehicleState.LuaEnvironment(
 LuaManager.platform, LuaManager.converterManager, LuaManager.env);
 }

 this->saveGameUI();
 if (this->m_selfUI.size() == 0) {
 this->m_luaEnv.caller.pcall(
 this->m_luaEnv.thread,
 this->m_luaEnv.env.rawget("AttachmentEditorState_InitUI"));
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

 void exit() { this->restoreGameUI(); }

 void render() {
 uint8_t byte0 = 0;
 Core.getInstance().StartFrame(byte0, true);
 this->renderScene();
 Core.getInstance().EndFrame(byte0);
 Core.getInstance().RenderOffScreenBuffer();
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

 static AttachmentEditorState checkInstance() {
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

 return instance = = nullptr ? new AttachmentEditorState() : instance;
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

 void *fromLua0(const std::string &func) {
 uint8_t byte0 = -1;
 switch (func.hashCode()) {
 case 3127582:
 if (func == "exit")) {
 byte0 = 0;
 }
 default:
 switch (byte0) {
 case 0:
 this->bExit = true;
 return nullptr;
 default:
 throw IllegalArgumentException("unhandled \"" + func + "\"");
 }
 }
 }

 void *fromLua1(const std::string &func, void *arg0) {
 uint8_t byte0 = -1;
 switch (func.hashCode()) {
 case 1396535690:
 if (func == "writeScript")) {
 byte0 = 0;
 }
 default:
 switch (byte0) {
 case 0:
 ModelScript modelScript =
 ScriptManager.instance.getModelScript((String)arg0);
 if (modelScript.empty()) {
 throw NullPointerException("model script \"" + arg0 +
 "\" not found");
 }

 std::vector arrayList = this->readScript(modelScript.getFileName());
 if (arrayList != nullptr) {
 this->updateScript(modelScript.getFileName(), arrayList, modelScript);
 }

 return nullptr;
 default:
 throw IllegalArgumentException(
 String.format("unhandled \"%s\" \"%s\"", func, arg0);
 }
 }
 }

private
 ArrayList<String> readScript(String string0) {
 StringBuilder stringBuilder = new StringBuilder();
 string0 = ZomboidFileSystem.instance.getString(string0);
 File file = new File(string0);

 try(FileReader fileReader = new FileReader(file);
 BufferedReader bufferedReader = new BufferedReader(fileReader);) {
 std::string string1 = System.lineSeparator();

 std::string string2;
 while ((string2 = bufferedReader.readLine()) != nullptr) {
 stringBuilder.append(string2);
 stringBuilder.append(string1);
 }
 }
 catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 return nullptr;
 }

 std::string string3 = ScriptParser.stripComments(stringBuilder.toString());
 return ScriptParser.parseTokens(string3);
 }

 void updateScript(const std::string &string0, ArrayList<String> arrayList0,
 ModelScript modelScript) {
 string0 = ZomboidFileSystem.instance.getString(string0);

 for (int int0 = arrayList0.size() - 1; int0 >= 0; int0--) {
 std::string string1 = ((String)arrayList0.get(int0).trim();
 int int1 = string1.indexOf("{");
 int int2 = string1.lastIndexOf("}");
 std::string string2 = string1.substring(0, int1);
 if (string2.startsWith("module")) {
 string2 = string1.substring(0, int1).trim();
 String[] strings = string2.split("\\s+");
 std::string string3 = strings.length > 1 ? strings[1].trim() : "";
 if (string3 == modelScript.getModule().getName())) {
 std::string string4 = string1.substring(int1 + 1, int2).trim();
 std::vector arrayList1 = ScriptParser.parseTokens(string4);

 for (int int3 = arrayList1.size() - 1; int3 >= 0; int3--) {
 std::string string5 = ((String)arrayList1.get(int3).trim();
 if (string5.startsWith("model")) {
 int1 = string5.indexOf("{");
 string2 = string5.substring(0, int1).trim();
 strings = string2.split("\\s+");
 std::string string6 =
 strings.length > 1 ? strings[1].trim() : "";
 if (string6 == modelScript.getName())) {
 string5 =
 this->modelScriptToText(modelScript, string5).trim();
 arrayList1.set(int3, string5);
 std::string string7 = System.lineSeparator();
 std::string string8 =
 String.join(string7 + "\t", arrayList1);
 string8 = "module " + string3 + string7 + "{" + string7 +
 "\t" + string8 + string7 + "}" + string7;
 arrayList0.set(int0, string8);
 this->writeScript(string0, arrayList0);
 return;
 }
 }
 }
 }
 }
 }
 }

 std::string modelScriptToText(ModelScript modelScript,
 const std::string &string0) {
 ScriptParser.Block block0 = ScriptParser.parse(string0);
 block0 = block0.children.get(0);

 for (int int0 = block0.children.size() - 1; int0 >= 0; int0--) {
 ScriptParser.Block block1 = block0.children.get(int0);
 if ("attachment" == block1.type) {
 block0.elements.remove(block1);
 block0.children.remove(int0);
 }
 }

 for (int int1 = 0; int1 < modelScript.getAttachmentCount(); int1++) {
 ModelAttachment modelAttachment = modelScript.getAttachment(int1);
 ScriptParser.Block block2 =
 block0.getBlock("attachment", modelAttachment.getId());
 if (block2.empty()) {
 block2 = new ScriptParser.Block();
 block2.type = "attachment";
 block2.id = modelAttachment.getId();
 block2.setValue("offset",
 String.format(Locale.US, "%.4f %.4f %.4f",
 modelAttachment.getOffset().x(),
 modelAttachment.getOffset().y(),
 modelAttachment.getOffset().z()));
 block2.setValue("rotate",
 String.format(Locale.US, "%.4f %.4f %.4f",
 modelAttachment.getRotate().x(),
 modelAttachment.getRotate().y(),
 modelAttachment.getRotate().z()));
 if (modelAttachment.getBone() != nullptr) {
 block2.setValue("bone", modelAttachment.getBone());
 }

 block0.elements.add(block2);
 block0.children.add(block2);
 } else {
 block2.setValue("offset",
 String.format(Locale.US, "%.4f %.4f %.4f",
 modelAttachment.getOffset().x(),
 modelAttachment.getOffset().y(),
 modelAttachment.getOffset().z()));
 block2.setValue("rotate",
 String.format(Locale.US, "%.4f %.4f %.4f",
 modelAttachment.getRotate().x(),
 modelAttachment.getRotate().y(),
 modelAttachment.getRotate().z()));
 }
 }

 StringBuilder stringBuilder = new StringBuilder();
 std::string string1 = System.lineSeparator();
 block0.prettyPrint(1, stringBuilder, string1);
 return stringBuilder.toString();
 }

 void writeScript(const std::string &string1, ArrayList<String> arrayList) {
 std::string string0 = ZomboidFileSystem.instance.getString(string1);
 File file = new File(string0);

 try(FileWriter fileWriter = new FileWriter(file);
 BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);) {
 DebugLog.General.printf("writing %s\n", string1);

 for (auto &string2 : arrayList)
 bufferedWriter.write(string2);
 }

 this->m_luaEnv.caller.pcall(this->m_luaEnv.thread,
 this->m_table.rawget("wroteScript"), this->m_table,
 string0);
 }
 catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 }
}
}
} // namespace gameStates
} // namespace zombie
