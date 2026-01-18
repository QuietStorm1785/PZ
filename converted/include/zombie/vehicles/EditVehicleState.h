#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "org/joml/Vector3f.h"
#include "se/krka/kahlua/converter/KahluaConverterManager.h"
#include "se/krka/kahlua/integration/LuaCaller.h"
#include "se/krka/kahlua/j2se/J2SEPlatform.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaThread.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/gameStates/GameState.h"
#include "zombie/gameStates/GameStateMachine.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class EditVehicleState : public GameState {
public:
 static EditVehicleState instance;
 private EditVehicleState.LuaEnvironment m_luaEnv;
 bool bExit = false;
 std::string m_initialScript = nullptr;
 private ArrayList<UIElement> m_gameUI = std::make_unique<ArrayList<>>();
 private ArrayList<UIElement> m_selfUI = std::make_unique<ArrayList<>>();
 bool m_bSuspendUI;
 KahluaTable m_table = nullptr;

 public EditVehicleState() {
 instance = this;
 }

 void enter() {
 instance = this;
 if (this->m_luaEnv == nullptr) {
 this->m_luaEnv = new EditVehicleState.LuaEnvironment(LuaManager.platform, LuaManager.converterManager, LuaManager.env);
 }

 this->saveGameUI();
 if (this->m_selfUI.size() == 0) {
 this->m_luaEnv.caller.pcall(this->m_luaEnv.thread, this->m_luaEnv.env.rawget("EditVehicleState_InitUI"));
 if (this->m_table != nullptr && this->m_table.getMetatable() != nullptr) {
 this->m_table.getMetatable().rawset("_LUA_RELOADED_CHECK", Boolean.FALSE);
 }
 } else {
 UIManager.UI.addAll(this->m_selfUI);
 this->m_luaEnv.caller.pcall(this->m_luaEnv.thread, this->m_table.rawget("showUI"), this->m_table);
 }

 this->bExit = false;
 }

 void yield() {
 this->restoreGameUI();
 }

 void reenter() {
 this->saveGameUI();
 }

 void exit() {
 this->restoreGameUI();
 }

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

 public GameStateMachine.StateAction update() {
 if (!this->bExit && !GameKeyboard.isKeyPressed(65) {
 this->updateScene();
 return GameStateMachine.StateAction.Remain;
 } else {
 return GameStateMachine.StateAction.Continue;
 }
 }

 static EditVehicleState checkInstance() {
 if (instance != nullptr) {
 if (instance.m_table != nullptr && instance.m_table.getMetatable() != nullptr) {
 if (instance.m_table.getMetatable().rawget("_LUA_RELOADED_CHECK") == nullptr) {
 instance = nullptr;
 }
 } else {
 instance = nullptr;
 }
 }

 return instance = = nullptr ? new EditVehicleState() : instance;
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
 DebugOptions.instance.ModelRenderWireframe.setValue(!DebugOptions.instance.ModelRenderWireframe.getValue());
 }
 }

 void renderScene() {
 }

 void renderUI() {
 UIManager.render();
 }

 void setTable(KahluaTable table) {
 this->m_table = table;
 }

 void setScript(const std::string& scriptName) {
 if (this->m_table == nullptr) {
 this->m_initialScript = scriptName;
 } else {
 this->m_luaEnv.caller.pcall(this->m_luaEnv.thread, this->m_table.rawget("setScript"), this->m_table, scriptName);
 }
 }

 void* fromLua0(const std::string& func) {
 switch (func) {
 case "exit":
 this->bExit = true;
 return nullptr;
 case "getInitialScript":
 return this->m_initialScript;
 default:
 throw IllegalArgumentException("unhandled \"" + func + "\"");
 }
 }

 void* fromLua1(const std::string& func, void* arg0) {
 uint8_t byte0 = -1;
 switch (func.hashCode()) {
 case 1396535690:
 if (func == "writeScript")) {
 byte0 = 0;
 }
 default:
 switch (byte0) {
 case 0:
 VehicleScript vehicleScript = ScriptManager.instance.getVehicle((String)arg0);
 if (vehicleScript == nullptr) {
 throw NullPointerException("vehicle script \"" + arg0 + "\" not found");
 }

 std::vector arrayList = this->readScript(vehicleScript.getFileName());
 if (arrayList != nullptr) {
 this->updateScript(vehicleScript.getFileName(), arrayList, vehicleScript);
 }

 return nullptr;
 default:
 throw IllegalArgumentException(String.format("unhandled \"%s\" \"%s\"", func, arg0);
 }
 }
 }

 private ArrayList<String> readScript(String string0) {
 StringBuilder stringBuilder = new StringBuilder();
 string0 = ZomboidFileSystem.instance.getString(string0);
 File file = new File(string0);

 try (
 FileReader fileReader = new FileReader(file);
 BufferedReader bufferedReader = new BufferedReader(fileReader);
 ) {
 std::string string1 = System.lineSeparator();

 std::string string2;
 while ((string2 = bufferedReader.readLine()) != nullptr) {
 stringBuilder.append(string2);
 stringBuilder.append(string1);
 }
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 return nullptr;
 }

 std::string string3 = ScriptParser.stripComments(stringBuilder.toString());
 return ScriptParser.parseTokens(string3);
 }

 void updateScript(const std::string& string0, ArrayList<String> arrayList0, VehicleScript vehicleScript) {
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
 if (string3 == vehicleScript.getModule().getName())) {
 std::string string4 = string1.substring(int1 + 1, int2).trim();
 std::vector arrayList1 = ScriptParser.parseTokens(string4);

 for (int int3 = arrayList1.size() - 1; int3 >= 0; int3--) {
 std::string string5 = ((String)arrayList1.get(int3).trim();
 if (string5.startsWith("vehicle")) {
 int1 = string5.indexOf("{");
 string2 = string5.substring(0, int1).trim();
 strings = string2.split("\\s+");
 std::string string6 = strings.length > 1 ? strings[1].trim() : "";
 if (string6 == vehicleScript.getName())) {
 string5 = this->vehicleScriptToText(vehicleScript, string5).trim();
 arrayList1.set(int3, string5);
 std::string string7 = System.lineSeparator();
 std::string string8 = String.join(string7 + "\t", arrayList1);
 string8 = "module " + string3 + string7 + "{" + string7 + "\t" + string8 + string7 + "}" + string7;
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

 std::string vehicleScriptToText(VehicleScript vehicleScript, const std::string& string0) {
 float float0 = vehicleScript.getModelScale();
 ScriptParser.Block block0 = ScriptParser.parse(string0);
 block0 = block0.children.get(0);
 VehicleScript.Model model = vehicleScript.getModel();
 ScriptParser.Block block1 = block0.getBlock("model", nullptr);
 if (model != nullptr && block1 != nullptr) {
 float float1 = vehicleScript.getModelScale();
 block1.setValue("scale", String.format(Locale.US, "%.4f", float1);
 Vector3f vector3f0 = vehicleScript.getModel().getOffset();
 block1.setValue("offset", String.format(Locale.US, "%.4f %.4f %.4f", vector3f0.x / float0, vector3f0.y / float0, vector3f0.z / float0);
 }

 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < block0.children.size(); int0++) {
 ScriptParser.Block block2 = block0.children.get(int0);
 if ("physics" == block2.type) {
 if (arrayList.size() == vehicleScript.getPhysicsShapeCount()) {
 block0.elements.remove(block2);
 block0.children.remove(int0);
 int0--;
 } else {
 arrayList.add(block2);
 }
 }
 }

 for (int int1 = 0; int1 < vehicleScript.getPhysicsShapeCount(); int1++) {
 VehicleScript.PhysicsShape physicsShape = vehicleScript.getPhysicsShape(int1);
 bool boolean0 = int1 < arrayList.size();
 ScriptParser.Block block3 = boolean0 ? (ScriptParser.Block)arrayList.get(int1) : new ScriptParser.Block();
 block3.type = "physics";
 block3.id = physicsShape.getTypeString();
 if (boolean0) {
 block3.elements.clear();
 block3.children.clear();
 block3.values.clear();
 }

 block3.setValue(
 "offset",
 String.format(
 Locale.US,
 "%.4f %.4f %.4f",
 physicsShape.getOffset().x() / float0,
 physicsShape.getOffset().y() / float0,
 physicsShape.getOffset().z() / float0
 )
 );
 if (physicsShape.type == 1) {
 block3.setValue(
 "extents",
 String.format(
 Locale.US,
 "%.4f %.4f %.4f",
 physicsShape.getExtents().x() / float0,
 physicsShape.getExtents().y() / float0,
 physicsShape.getExtents().z() / float0
 )
 );
 block3.setValue(
 "rotate",
 String.format(Locale.US, "%.4f %.4f %.4f", physicsShape.getRotate().x(), physicsShape.getRotate().y(), physicsShape.getRotate().z())
 );
 }

 if (physicsShape.type == 2) {
 block3.setValue("radius", String.format(Locale.US, "%.4f", physicsShape.getRadius() / float0);
 }

 if (!boolean0) {
 block0.elements.add(block3);
 block0.children.add(block3);
 }
 }

 for (int int2 = block0.children.size() - 1; int2 >= 0; int2--) {
 ScriptParser.Block block4 = block0.children.get(int2);
 if ("attachment" == block4.type) {
 block0.elements.remove(block4);
 block0.children.remove(int2);
 }
 }

 for (int int3 = 0; int3 < vehicleScript.getAttachmentCount(); int3++) {
 ModelAttachment modelAttachment = vehicleScript.getAttachment(int3);
 ScriptParser.Block block5 = block0.getBlock("attachment", modelAttachment.getId());
 if (block5 == nullptr) {
 block5 = new ScriptParser.Block();
 block5.type = "attachment";
 block5.id = modelAttachment.getId();
 block0.elements.add(block5);
 block0.children.add(block5);
 }

 block5.setValue(
 "offset",
 String.format(
 Locale.US,
 "%.4f %.4f %.4f",
 modelAttachment.getOffset().x() / float0,
 modelAttachment.getOffset().y() / float0,
 modelAttachment.getOffset().z() / float0
 )
 );
 block5.setValue(
 "rotate",
 String.format(Locale.US, "%.4f %.4f %.4f", modelAttachment.getRotate().x(), modelAttachment.getRotate().y(), modelAttachment.getRotate().z())
 );
 if (modelAttachment.getBone() != nullptr) {
 block5.setValue("bone", modelAttachment.getBone());
 }

 if (modelAttachment.getCanAttach() != nullptr) {
 block5.setValue("canAttach", PZArrayUtil.arrayToString(modelAttachment.getCanAttach(), "", "", ","));
 }

 if (modelAttachment.getZOffset() != 0.0F) {
 block5.setValue("zoffset", String.format(Locale.US, "%.4f", modelAttachment.getZOffset()));
 }

 if (!modelAttachment.isUpdateConstraint()) {
 block5.setValue("updateconstraint", "false");
 }
 }

 Vector3f vector3f1 = vehicleScript.getExtents();
 block0.setValue("extents", String.format(Locale.US, "%.4f %.4f %.4f", vector3f1.x / float0, vector3f1.y / float0, vector3f1.z / float0);
 Vector3f vector3f2 = vehicleScript.getPhysicsChassisShape();
 block0.setValue("physicsChassisShape", String.format(Locale.US, "%.4f %.4f %.4f", vector3f2.x / float0, vector3f2.y / float0, vector3f2.z / float0);
 Vector3f vector3f3 = vehicleScript.getCenterOfMassOffset();
 block0.setValue("centerOfMassOffset", String.format(Locale.US, "%.4f %.4f %.4f", vector3f3.x / float0, vector3f3.y / float0, vector3f3.z / float0);
 Vector2f vector2f0 = vehicleScript.getShadowExtents();
 bool boolean1 = block0.getValue("shadowExtents") != nullptr;
 block0.setValue("shadowExtents", String.format(Locale.US, "%.4f %.4f", vector2f0.x / float0, vector2f0.y / float0);
 if (!boolean1) {
 block0.moveValueAfter("shadowExtents", "centerOfMassOffset");
 }

 Vector2f vector2f1 = vehicleScript.getShadowOffset();
 boolean1 = block0.getValue("shadowOffset") != nullptr;
 block0.setValue("shadowOffset", String.format(Locale.US, "%.4f %.4f", vector2f1.x / float0, vector2f1.y / float0);
 if (!boolean1) {
 block0.moveValueAfter("shadowOffset", "shadowExtents");
 }

 for (int int4 = 0; int4 < vehicleScript.getAreaCount(); int4++) {
 VehicleScript.Area area = vehicleScript.getArea(int4);
 ScriptParser.Block block6 = block0.getBlock("area", area.getId());
 if (block6 != nullptr) {
 block6.setValue(
 "xywh",
 String.format(Locale.US, "%.4f %.4f %.4f %.4f", area.getX() / float0, area.getY() / float0, area.getW() / float0, area.getH() / float0)
 );
 }
 }

 for (int int5 = 0; int5 < vehicleScript.getPassengerCount(); int5++) {
 VehicleScript.Passenger passenger = vehicleScript.getPassenger(int5);
 ScriptParser.Block block7 = block0.getBlock("passenger", passenger.getId());
 if (block7 != nullptr) {
 for (VehicleScript.Position position : passenger.positions) {
 ScriptParser.Block block8 = block7.getBlock("position", position.id);
 if (block8 != nullptr) {
 block8.setValue(
 "offset",
 String.format(Locale.US, "%.4f %.4f %.4f", position.offset.x / float0, position.offset.y / float0, position.offset.z / float0)
 );
 block8.setValue(
 "rotate",
 String.format(Locale.US, "%.4f %.4f %.4f", position.rotate.x / float0, position.rotate.y / float0, position.rotate.z / float0)
 );
 }
 }
 }
 }

 for (int int6 = 0; int6 < vehicleScript.getWheelCount(); int6++) {
 VehicleScript.Wheel wheel = vehicleScript.getWheel(int6);
 ScriptParser.Block block9 = block0.getBlock("wheel", wheel.getId());
 if (block9 != nullptr) {
 block9.setValue("offset", String.format(Locale.US, "%.4f %.4f %.4f", wheel.offset.x / float0, wheel.offset.y / float0, wheel.offset.z / float0);
 }
 }

 StringBuilder stringBuilder = new StringBuilder();
 std::string string1 = System.lineSeparator();
 block0.prettyPrint(1, stringBuilder, string1);
 return stringBuilder.toString();
 }

 void writeScript(const std::string& string1, ArrayList<String> arrayList) {
 std::string string0 = ZomboidFileSystem.instance.getString(string1);
 File file = new File(string0);

 try (
 FileWriter fileWriter = new FileWriter(file);
 BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
 ) {
 DebugLog.General.printf("writing %s\n", string1);

 for (auto& string2 : arrayList) bufferedWriter.write(string2);
 }

 this->m_luaEnv.caller.pcall(this->m_luaEnv.thread, this->m_table.rawget("wroteScript"), this->m_table, string0);
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 }
 }

 public static class LuaEnvironment {
 J2SEPlatform platform;
 KahluaTable env;
 KahluaThread thread;
 LuaCaller caller;

 public LuaEnvironment(J2SEPlatform _platform, KahluaConverterManager converterManager, KahluaTable _env) {
 this->platform = _platform;
 this->env = _env;
 this->thread = LuaManager.thread;
 this->caller = LuaManager.caller;
 }
 }
}
} // namespace vehicles
} // namespace zombie
