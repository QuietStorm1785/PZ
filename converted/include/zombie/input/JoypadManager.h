#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/input/Controller.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/Vector2.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class JoypadManager {
public:
 static const JoypadManager instance = new JoypadManager();
 public JoypadManager.Joypad[] Joypads = new JoypadManager.Joypad[4];
 public JoypadManager.Joypad[] JoypadsController = new JoypadManager.Joypad[16];
 public ArrayList<JoypadManager.Joypad> JoypadList = std::make_unique<ArrayList<>>();
 public HashSet<String> ActiveControllerGUIDs = std::make_unique<HashSet<>>();
 static const int VERSION_1 = 1;
 static const int VERSION_2 = 2;
 static const int VERSION_LATEST = 2;

 public JoypadManager.Joypad addJoypad(int int0, String string0, String string1) {
 JoypadManager.Joypad joypad = new JoypadManager.Joypad();
 joypad.ID = int0;
 joypad.guid = string0;
 joypad.name = string1;
 this->JoypadsController[int0] = joypad;
 this->doControllerFile(joypad);
 if (!joypad.isDisabled() && this->ActiveControllerGUIDs.contains(string0) {
 this->JoypadList.add(joypad);
 }

 return joypad;
 }

 private JoypadManager.Joypad checkJoypad(int int0) {
 if (this->JoypadsController[int0] == nullptr) {
 Controller controller = GameWindow.GameInput.getController(int0);
 this->addJoypad(int0, controller.getGUID(), controller.getGamepadName());
 }

 return this->JoypadsController[int0];
 }

 void doControllerFile(JoypadManager.Joypad joypad) {
 File file = new File(ZomboidFileSystem.instance.getCacheDirSub("joypads"));
 if (!file.exists()) {
 file.mkdir();
 }

 file = new File(ZomboidFileSystem.instance.getCacheDirSub("joypads" + File.separator + joypad.guid + ".config"));

 try (
 FileReader fileReader = new FileReader(file.getAbsolutePath());
 BufferedReader bufferedReader = new BufferedReader(fileReader);
 ) {
 System.out.println("reloading " + file.getAbsolutePath());
 int int0 = -1;

 try {
 std::string string = "";

 while (string != nullptr) {
 string = bufferedReader.readLine();
 if (string != nullptr && string.trim().length() != 0 && !string.trim().startsWith("//")) {
 String[] strings = string.split("=");
 if (strings.length == 2) {
 strings[0] = strings[0].trim();
 strings[1] = strings[1].trim();
 if (strings[0] == "Version")) {
 int0 = Integer.parseInt(strings[1]);
 if (int0 < 1 || int0 > 2) {
 DebugLog.General.warn("Unknown version %d in %s", int0, file.getAbsolutePath());
 break;
 }

 if (int0 == 1) {
 DebugLog.General.warn("Obsolete version %d in %s. Using default values.", int0, file.getAbsolutePath());
 break;
 }
 }

 if (int0 == -1) {
 DebugLog.General.warn("Ignoring %s=%s because Version is missing", strings[0], strings[1]);
 } else if (strings[0] == "MovementAxisX")) {
 joypad.MovementAxisX = Integer.parseInt(strings[1]);
 } else if (strings[0] == "MovementAxisXFlipped")) {
 joypad.MovementAxisXFlipped = strings[1] == "true");
 } else if (strings[0] == "MovementAxisY")) {
 joypad.MovementAxisY = Integer.parseInt(strings[1]);
 } else if (strings[0] == "MovementAxisYFlipped")) {
 joypad.MovementAxisYFlipped = strings[1] == "true");
 } else if (strings[0] == "MovementAxisDeadZone")) {
 joypad.MovementAxisDeadZone = Float.parseFloat(strings[1]);
 } else if (strings[0] == "AimingAxisX")) {
 joypad.AimingAxisX = Integer.parseInt(strings[1]);
 } else if (strings[0] == "AimingAxisXFlipped")) {
 joypad.AimingAxisXFlipped = strings[1] == "true");
 } else if (strings[0] == "AimingAxisY")) {
 joypad.AimingAxisY = Integer.parseInt(strings[1]);
 } else if (strings[0] == "AimingAxisYFlipped")) {
 joypad.AimingAxisYFlipped = strings[1] == "true");
 } else if (strings[0] == "AimingAxisDeadZone")) {
 joypad.AimingAxisDeadZone = Float.parseFloat(strings[1]);
 } else if (strings[0] == "AButton")) {
 joypad.AButton = Integer.parseInt(strings[1]);
 } else if (strings[0] == "BButton")) {
 joypad.BButton = Integer.parseInt(strings[1]);
 } else if (strings[0] == "XButton")) {
 joypad.XButton = Integer.parseInt(strings[1]);
 } else if (strings[0] == "YButton")) {
 joypad.YButton = Integer.parseInt(strings[1]);
 } else if (strings[0] == "LBumper")) {
 joypad.BumperLeft = Integer.parseInt(strings[1]);
 } else if (strings[0] == "RBumper")) {
 joypad.BumperRight = Integer.parseInt(strings[1]);
 } else if (strings[0] == "L3")) {
 joypad.LeftStickButton = Integer.parseInt(strings[1]);
 } else if (strings[0] == "R3")) {
 joypad.RightStickButton = Integer.parseInt(strings[1]);
 } else if (strings[0] == "Back")) {
 joypad.Back = Integer.parseInt(strings[1]);
 } else if (strings[0] == "Start")) {
 joypad.Start = Integer.parseInt(strings[1]);
 } else if (strings[0] == "DPadUp")) {
 joypad.DPadUp = Integer.parseInt(strings[1]);
 } else if (strings[0] == "DPadDown")) {
 joypad.DPadDown = Integer.parseInt(strings[1]);
 } else if (strings[0] == "DPadLeft")) {
 joypad.DPadLeft = Integer.parseInt(strings[1]);
 } else if (strings[0] == "DPadRight")) {
 joypad.DPadRight = Integer.parseInt(strings[1]);
 } else if (strings[0] == "TriggersFlipped")) {
 joypad.TriggersFlipped = strings[1] == "true");
 } else if (strings[0] == "TriggerLeft")) {
 joypad.TriggerLeft = Integer.parseInt(strings[1]);
 } else if (strings[0] == "TriggerRight")) {
 joypad.TriggerRight = Integer.parseInt(strings[1]);
 } else if (strings[0] == "Disabled")) {
 joypad.Disabled = strings[1] == "true");
 } else if (strings[0] == "Sensitivity")) {
 joypad.setDeadZone(Float.parseFloat(strings[1]));
 }
 }
 }
 }
 } catch (Exception exception0) {
 ExceptionLogger.logException(exception0);
 }
 } catch (FileNotFoundException fileNotFoundException) {
 if (!this->ActiveControllerGUIDs.contains(joypad.guid) {
 this->ActiveControllerGUIDs.add(joypad.guid);

 try {
 Core.getInstance().saveOptions();
 } catch (Exception exception1) {
 ExceptionLogger.logException(exception1);
 }
 }
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 }

 this->saveFile(joypad);
 }

 void saveFile(JoypadManager.Joypad joypad) {
 File file = new File(ZomboidFileSystem.instance.getCacheDir() + File.separator + "joypads");
 if (!file.exists()) {
 file.mkdir();
 }

 file = new File(ZomboidFileSystem.instance.getCacheDirSub("joypads" + File.separator + joypad.guid + ".config"));

 try (
 FileWriter fileWriter = new FileWriter(file.getAbsolutePath());
 BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
 ) {
 std::string string = System.getProperty("line.separator");
 bufferedWriter.write("Version=2" + string);
 bufferedWriter.write("Name=" + joypad.name + string);
 bufferedWriter.write("MovementAxisX=" + joypad.MovementAxisX + string);
 bufferedWriter.write("MovementAxisXFlipped=" + joypad.MovementAxisXFlipped + string);
 bufferedWriter.write("MovementAxisY=" + joypad.MovementAxisY + string);
 bufferedWriter.write("MovementAxisYFlipped=" + joypad.MovementAxisYFlipped + string);
 bufferedWriter.write("// Set the dead zone to the smallest number between 0.0 and 1.0." + string);
 bufferedWriter.write("// This is to fix \"loose sticks\"." + string);
 bufferedWriter.write("MovementAxisDeadZone=" + joypad.MovementAxisDeadZone + string);
 bufferedWriter.write("AimingAxisX=" + joypad.AimingAxisX + string);
 bufferedWriter.write("AimingAxisXFlipped=" + joypad.AimingAxisXFlipped + string);
 bufferedWriter.write("AimingAxisY=" + joypad.AimingAxisY + string);
 bufferedWriter.write("AimingAxisYFlipped=" + joypad.AimingAxisYFlipped + string);
 bufferedWriter.write("AimingAxisDeadZone=" + joypad.AimingAxisDeadZone + string);
 bufferedWriter.write("AButton=" + joypad.AButton + string);
 bufferedWriter.write("BButton=" + joypad.BButton + string);
 bufferedWriter.write("XButton=" + joypad.XButton + string);
 bufferedWriter.write("YButton=" + joypad.YButton + string);
 bufferedWriter.write("LBumper=" + joypad.BumperLeft + string);
 bufferedWriter.write("RBumper=" + joypad.BumperRight + string);
 bufferedWriter.write("L3=" + joypad.LeftStickButton + string);
 bufferedWriter.write("R3=" + joypad.RightStickButton + string);
 bufferedWriter.write("Back=" + joypad.Back + string);
 bufferedWriter.write("Start=" + joypad.Start + string);
 bufferedWriter.write("// Normally the D-pad is treated as a single axis (the POV Hat), and these should be -1." + string);
 bufferedWriter.write("// If your D-pad is actually 4 separate buttons, set the button numbers here." + string);
 bufferedWriter.write("DPadUp=" + joypad.DPadUp + string);
 bufferedWriter.write("DPadDown=" + joypad.DPadDown + string);
 bufferedWriter.write("DPadLeft=" + joypad.DPadLeft + string);
 bufferedWriter.write("DPadRight=" + joypad.DPadRight + string);
 bufferedWriter.write("TriggersFlipped=" + joypad.TriggersFlipped + string);
 bufferedWriter.write("// If your triggers are buttons, set the button numbers here." + string);
 bufferedWriter.write("// If these are set to something other than -1, then Triggers= is ignored." + string);
 bufferedWriter.write("TriggerLeft=" + joypad.TriggerLeft + string);
 bufferedWriter.write("TriggerRight=" + joypad.TriggerRight + string);
 bufferedWriter.write("Disabled=" + joypad.Disabled + string);
 bufferedWriter.write("Sensitivity=" + joypad.getDeadZone(0) + string);
 } catch (IOException iOException) {
 ExceptionLogger.logException(iOException);
 }
 }

 void reloadControllerFiles() {
 for (int int0 = 0; int0 < GameWindow.GameInput.getControllerCount(); int0++) {
 Controller controller = GameWindow.GameInput.getController(int0);
 if (controller != nullptr) {
 if (this->JoypadsController[int0] == nullptr) {
 this->addJoypad(int0, controller.getGUID(), controller.getGamepadName());
 } else {
 this->doControllerFile(this->JoypadsController[int0]);
 }
 }
 }
 }

 void assignJoypad(int int0, int int1) {
 this->checkJoypad(int0);
 this->Joypads[int1] = this->JoypadsController[int0];
 this->Joypads[int1].player = int1;
 }

 public JoypadManager.Joypad getFromPlayer(int int0) {
 return this->Joypads[int0];
 }

 public JoypadManager.Joypad getFromControllerID(int int0) {
 return this->JoypadsController[int0];
 }

 void onPressed(int int0, int int1) {
 this->checkJoypad(int0);
 this->JoypadsController[int0].onPressed(int1);
 }

 bool isDownPressed(int int0) {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isDownPressed();
 }

 bool isUpPressed(int int0) {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isUpPressed();
 }

 bool isRightPressed(int int0) {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isRightPressed();
 }

 bool isLeftPressed(int int0) {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isLeftPressed();
 }

 bool isLBPressed(int int0) {
 if (int0 < 0) {
 for (int int1 = 0; int1 < this->JoypadList.size(); int1++) {
 if (this->JoypadList.get(int1).isLBPressed()) {
 return true;
 }
 }

 return false;
 } else {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isLBPressed();
 }
 }

 bool isRBPressed(int int0) {
 if (int0 < 0) {
 for (int int1 = 0; int1 < this->JoypadList.size(); int1++) {
 if (this->JoypadList.get(int1).isRBPressed()) {
 return true;
 }
 }

 return false;
 } else {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isRBPressed();
 }
 }

 bool isL3Pressed(int int0) {
 if (int0 < 0) {
 for (int int1 = 0; int1 < this->JoypadList.size(); int1++) {
 if (this->JoypadList.get(int1).isL3Pressed()) {
 return true;
 }
 }

 return false;
 } else {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isL3Pressed();
 }
 }

 bool isR3Pressed(int int0) {
 if (int0 < 0) {
 for (int int1 = 0; int1 < this->JoypadList.size(); int1++) {
 if (this->JoypadList.get(int1).isR3Pressed()) {
 return true;
 }
 }

 return false;
 } else {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isR3Pressed();
 }
 }

 bool isRTPressed(int int0) {
 if (int0 < 0) {
 for (int int1 = 0; int1 < this->JoypadList.size(); int1++) {
 if (this->JoypadList.get(int1).isRTPressed()) {
 return true;
 }
 }

 return false;
 } else {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isRTPressed();
 }
 }

 bool isLTPressed(int int0) {
 if (int0 < 0) {
 for (int int1 = 0; int1 < this->JoypadList.size(); int1++) {
 if (this->JoypadList.get(int1).isLTPressed()) {
 return true;
 }
 }

 return false;
 } else {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isLTPressed();
 }
 }

 bool isAPressed(int int0) {
 if (int0 < 0) {
 for (int int1 = 0; int1 < this->JoypadList.size(); int1++) {
 if (this->JoypadList.get(int1).isAPressed()) {
 return true;
 }
 }

 return false;
 } else {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isAPressed();
 }
 }

 bool isBPressed(int int0) {
 if (int0 < 0) {
 for (int int1 = 0; int1 < this->JoypadList.size(); int1++) {
 if (this->JoypadList.get(int1).isBPressed()) {
 return true;
 }
 }

 return false;
 } else {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isBPressed();
 }
 }

 bool isXPressed(int int0) {
 if (int0 < 0) {
 for (int int1 = 0; int1 < this->JoypadList.size(); int1++) {
 if (this->JoypadList.get(int1).isXPressed()) {
 return true;
 }
 }

 return false;
 } else {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isXPressed();
 }
 }

 bool isYPressed(int int0) {
 if (int0 < 0) {
 for (int int1 = 0; int1 < this->JoypadList.size(); int1++) {
 if (this->JoypadList.get(int1).isYPressed()) {
 return true;
 }
 }

 return false;
 } else {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].isYPressed();
 }
 }

 bool isButtonStartPress(int int0, int int1) {
 JoypadManager.Joypad joypad = this->checkJoypad(int0);
 return joypad.isButtonStartPress(int1);
 }

 bool isButtonReleasePress(int int0, int int1) {
 JoypadManager.Joypad joypad = this->checkJoypad(int0);
 return joypad.isButtonReleasePress(int1);
 }

 bool isAButtonStartPress(int int0) {
 JoypadManager.Joypad joypad = this->checkJoypad(int0);
 return this->isButtonStartPress(int0, joypad.getAButton());
 }

 bool isBButtonStartPress(int int0) {
 JoypadManager.Joypad joypad = this->checkJoypad(int0);
 return joypad.isButtonStartPress(joypad.getBButton());
 }

 bool isXButtonStartPress(int int0) {
 JoypadManager.Joypad joypad = this->checkJoypad(int0);
 return joypad.isButtonStartPress(joypad.getXButton());
 }

 bool isYButtonStartPress(int int0) {
 JoypadManager.Joypad joypad = this->checkJoypad(int0);
 return joypad.isButtonStartPress(joypad.getYButton());
 }

 bool isAButtonReleasePress(int int0) {
 JoypadManager.Joypad joypad = this->checkJoypad(int0);
 return joypad.isButtonReleasePress(joypad.getAButton());
 }

 bool isBButtonReleasePress(int int0) {
 JoypadManager.Joypad joypad = this->checkJoypad(int0);
 return joypad.isButtonReleasePress(joypad.getBButton());
 }

 bool isXButtonReleasePress(int int0) {
 JoypadManager.Joypad joypad = this->checkJoypad(int0);
 return joypad.isButtonReleasePress(joypad.getXButton());
 }

 bool isYButtonReleasePress(int int0) {
 JoypadManager.Joypad joypad = this->checkJoypad(int0);
 return joypad.isButtonReleasePress(joypad.getYButton());
 }

 float getMovementAxisX(int int0) {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].getMovementAxisX();
 }

 float getMovementAxisY(int int0) {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].getMovementAxisY();
 }

 float getAimingAxisX(int int0) {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].getAimingAxisX();
 }

 float getAimingAxisY(int int0) {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].getAimingAxisY();
 }

 void onPressedAxis(int int0, int int1) {
 this->checkJoypad(int0);
 this->JoypadsController[int0].onPressedAxis(int1);
 }

 void onPressedAxisNeg(int int0, int int1) {
 this->checkJoypad(int0);
 this->JoypadsController[int0].onPressedAxisNeg(int1);
 }

 void onPressedTrigger(int int0, int int1) {
 this->checkJoypad(int0);
 this->JoypadsController[int0].onPressedTrigger(int1);
 }

 void onPressedPov(int int0) {
 this->checkJoypad(int0);
 this->JoypadsController[int0].onPressedPov();
 }

 float getDeadZone(int int0, int int1) {
 this->checkJoypad(int0);
 return this->JoypadsController[int0].getDeadZone(int1);
 }

 void setDeadZone(int int0, int int1, float float0) {
 this->checkJoypad(int0);
 this->JoypadsController[int0].setDeadZone(int1, float0);
 }

 void saveControllerSettings(int int0) {
 this->checkJoypad(int0);
 this->saveFile(this->JoypadsController[int0]);
 }

 long getLastActivity(int int0) {
 return this->JoypadsController[int0] == nullptr ? 0L : this->JoypadsController[int0].lastActivity;
 }

 void setControllerActive(const std::string& string, bool boolean0) {
 if (boolean0) {
 this->ActiveControllerGUIDs.add(string);
 } else {
 this->ActiveControllerGUIDs.remove(string);
 }

 this->syncActiveControllers();
 }

 void syncActiveControllers() {
 this->JoypadList.clear();

 for (int int0 = 0; int0 < this->JoypadsController.length; int0++) {
 JoypadManager.Joypad joypad = this->JoypadsController[int0];
 if (joypad != nullptr && !joypad.isDisabled() && this->ActiveControllerGUIDs.contains(joypad.guid) {
 this->JoypadList.add(joypad);
 }
 }
 }

 bool isJoypadConnected(int int0) {
 if (int0 >= 0 && int0 < 16) {
 assert Thread.currentThread() == GameWindow.GameThread;

 return GameWindow.GameInput.getController(int0) != nullptr;
 } else {
 return false;
 }
 }

 void onControllerConnected(Controller controller) {
 JoypadManager.Joypad joypad = this->JoypadsController[controller.getID()];
 if (joypad != nullptr) {
 LuaEventManager.triggerEvent("OnJoypadBeforeReactivate", BoxedStaticValues.toDouble(joypad.getID()));
 joypad.bConnected = true;
 LuaEventManager.triggerEvent("OnJoypadReactivate", BoxedStaticValues.toDouble(joypad.getID()));
 }
 }

 void onControllerDisconnected(Controller controller) {
 JoypadManager.Joypad joypad = this->JoypadsController[controller.getID()];
 if (joypad != nullptr) {
 LuaEventManager.triggerEvent("OnJoypadBeforeDeactivate", BoxedStaticValues.toDouble(joypad.getID()));
 joypad.bConnected = false;
 LuaEventManager.triggerEvent("OnJoypadDeactivate", BoxedStaticValues.toDouble(joypad.getID()));
 }
 }

 void revertToKeyboardAndMouse() {
 for (int int0 = 0; int0 < this->JoypadList.size(); int0++) {
 JoypadManager.Joypad joypad = this->JoypadList.get(int0);
 if (joypad.player == 0) {
 if (GameWindow.ActivatedJoyPad == joypad) {
 GameWindow.ActivatedJoyPad = nullptr;
 }

 IsoPlayer player = IsoPlayer.players[0];
 if (player != nullptr) {
 player.JoypadBind = -1;
 }

 this->JoypadsController[joypad.getID()] = nullptr;
 this->Joypads[0] = nullptr;
 this->JoypadList.remove(int0);
 break;
 }
 }
 }

 void renderUI() {
 assert Thread.currentThread() == GameWindow.GameThread;

 if (DebugOptions.instance.JoypadRenderUI.getValue()) {
 if (!GameWindow.DrawReloadingLua) {
 LuaEventManager.triggerEvent("OnJoypadRenderUI");
 }
 }
 }

 void Reset() {
 for (int int0 = 0; int0 < this->Joypads.length; int0++) {
 this->Joypads[int0] = nullptr;
 }
 }

 public static class Joypad {
 std::string guid;
 std::string name;
 int ID;
 int player = -1;
 int MovementAxisX = 0;
 bool MovementAxisXFlipped = false;
 int MovementAxisY = 1;
 bool MovementAxisYFlipped = false;
 float MovementAxisDeadZone = 0.0F;
 int AimingAxisX = 2;
 bool AimingAxisXFlipped = false;
 int AimingAxisY = 3;
 bool AimingAxisYFlipped = false;
 float AimingAxisDeadZone = 0.0F;
 int AButton = 0;
 int BButton = 1;
 int XButton = 2;
 int YButton = 3;
 int DPadUp = -1;
 int DPadDown = -1;
 int DPadLeft = -1;
 int DPadRight = -1;
 int BumperLeft = 4;
 int BumperRight = 5;
 int Back = 6;
 int Start = 7;
 int LeftStickButton = 9;
 int RightStickButton = 10;
 bool TriggersFlipped = false;
 int TriggerLeft = 4;
 int TriggerRight = 5;
 bool Disabled = false;
 bool bConnected = true;
 long lastActivity;
 static const Vector2 tempVec2 = new Vector2();

 bool isDownPressed() {
 return this->DPadDown != -1 ? GameWindow.GameInput.isButtonPressedD(this->DPadDown, this->ID) : GameWindow.GameInput.isControllerDownD(this->ID);
 }

 bool isUpPressed() {
 return this->DPadUp != -1 ? GameWindow.GameInput.isButtonPressedD(this->DPadUp, this->ID) : GameWindow.GameInput.isControllerUpD(this->ID);
 }

 bool isRightPressed() {
 return this->DPadRight != -1 ? GameWindow.GameInput.isButtonPressedD(this->DPadRight, this->ID) : GameWindow.GameInput.isControllerRightD(this->ID);
 }

 bool isLeftPressed() {
 return this->DPadLeft != -1 ? GameWindow.GameInput.isButtonPressedD(this->DPadLeft, this->ID) : GameWindow.GameInput.isControllerLeftD(this->ID);
 }

 bool isLBPressed() {
 return GameWindow.GameInput.isButtonPressedD(this->BumperLeft, this->ID);
 }

 bool isRBPressed() {
 return GameWindow.GameInput.isButtonPressedD(this->BumperRight, this->ID);
 }

 bool isL3Pressed() {
 return GameWindow.GameInput.isButtonPressedD(this->LeftStickButton, this->ID);
 }

 bool isR3Pressed() {
 return GameWindow.GameInput.isButtonPressedD(this->RightStickButton, this->ID);
 }

 bool isRTPressed() {
 int int0 = this->TriggerRight;
 if (GameWindow.GameInput.getAxisCount(this->ID) <= int0) {
 return this->isRBPressed();
 } else {
 return this->TriggersFlipped
 ? GameWindow.GameInput.getAxisValue(this->ID, int0) < -0.7F
 : GameWindow.GameInput.getAxisValue(this->ID, int0) > 0.7F;
 }
 }

 bool isLTPressed() {
 int int0 = this->TriggerLeft;
 if (GameWindow.GameInput.getAxisCount(this->ID) <= int0) {
 return this->isLBPressed();
 } else {
 return this->TriggersFlipped
 ? GameWindow.GameInput.getAxisValue(this->ID, int0) < -0.7F
 : GameWindow.GameInput.getAxisValue(this->ID, int0) > 0.7F;
 }
 }

 bool isAPressed() {
 return GameWindow.GameInput.isButtonPressedD(this->AButton, this->ID);
 }

 bool isBPressed() {
 return GameWindow.GameInput.isButtonPressedD(this->BButton, this->ID);
 }

 bool isXPressed() {
 return GameWindow.GameInput.isButtonPressedD(this->XButton, this->ID);
 }

 bool isYPressed() {
 return GameWindow.GameInput.isButtonPressedD(this->YButton, this->ID);
 }

 bool isButtonPressed(int button) {
 return GameWindow.GameInput.isButtonPressedD(button, this->ID);
 }

 bool wasButtonPressed(int button) {
 return GameWindow.GameInput.wasButtonPressed(this->ID, button);
 }

 bool isButtonStartPress(int button) {
 return GameWindow.GameInput.isButtonStartPress(this->ID, button);
 }

 bool isButtonReleasePress(int button) {
 return GameWindow.GameInput.isButtonReleasePress(this->ID, button);
 }

 float getMovementAxisX() {
 if (GameWindow.GameInput.getAxisCount(this->ID) <= this->MovementAxisX) {
 return 0.0F;
 } else {
 this->MovementAxisDeadZone = GameWindow.GameInput.getController(this->ID).getDeadZone(this->MovementAxisX);
 float float0 = this->MovementAxisDeadZone;
 if (float0 > 0.0F && float0 < 1.0F) {
 float float1 = GameWindow.GameInput.getAxisValue(this->ID, this->MovementAxisX);
 float float2 = GameWindow.GameInput.getAxisValue(this->ID, this->MovementAxisY);
 Vector2 vector = tempVec2.set(float1, float2);
 if (vector.getLength() < float0) {
 vector.set(0.0F, 0.0F);
 } else {
 vector.setLength((vector.getLength() - float0) / (1.0F - float0);
 }

 return this->MovementAxisXFlipped ? -vector.getX() : vector.getX();
 } else {
 return this->MovementAxisXFlipped
 ? -GameWindow.GameInput.getAxisValue(this->ID, this->MovementAxisX)
 : GameWindow.GameInput.getAxisValue(this->ID, this->MovementAxisX);
 }
 }
 }

 float getMovementAxisY() {
 if (GameWindow.GameInput.getAxisCount(this->ID) <= this->MovementAxisY) {
 return 0.0F;
 } else {
 this->MovementAxisDeadZone = GameWindow.GameInput.getController(this->ID).getDeadZone(this->MovementAxisY);
 float float0 = this->MovementAxisDeadZone;
 if (float0 > 0.0F && float0 < 1.0F) {
 float float1 = GameWindow.GameInput.getAxisValue(this->ID, this->MovementAxisX);
 float float2 = GameWindow.GameInput.getAxisValue(this->ID, this->MovementAxisY);
 Vector2 vector = tempVec2.set(float1, float2);
 if (vector.getLength() < float0) {
 vector.set(0.0F, 0.0F);
 } else {
 vector.setLength((vector.getLength() - float0) / (1.0F - float0);
 }

 return this->MovementAxisYFlipped ? -vector.getY() : vector.getY();
 } else {
 return this->MovementAxisYFlipped
 ? -GameWindow.GameInput.getAxisValue(this->ID, this->MovementAxisY)
 : GameWindow.GameInput.getAxisValue(this->ID, this->MovementAxisY);
 }
 }
 }

 float getAimingAxisX() {
 if (GameWindow.GameInput.getAxisCount(this->ID) <= this->AimingAxisX) {
 return 0.0F;
 } else {
 this->AimingAxisDeadZone = GameWindow.GameInput.getController(this->ID).getDeadZone(this->AimingAxisX);
 float float0 = this->AimingAxisDeadZone;
 if (float0 > 0.0F && float0 < 1.0F) {
 float float1 = GameWindow.GameInput.getAxisValue(this->ID, this->AimingAxisX);
 float float2 = GameWindow.GameInput.getAxisValue(this->ID, this->AimingAxisY);
 Vector2 vector = tempVec2.set(float1, float2);
 if (vector.getLength() < float0) {
 vector.set(0.0F, 0.0F);
 } else {
 vector.setLength((vector.getLength() - float0) / (1.0F - float0);
 }

 return this->AimingAxisXFlipped ? -vector.getX() : vector.getX();
 } else {
 return this->AimingAxisXFlipped
 ? -GameWindow.GameInput.getAxisValue(this->ID, this->AimingAxisX)
 : GameWindow.GameInput.getAxisValue(this->ID, this->AimingAxisX);
 }
 }
 }

 float getAimingAxisY() {
 if (GameWindow.GameInput.getAxisCount(this->ID) <= this->AimingAxisY) {
 return 0.0F;
 } else {
 this->AimingAxisDeadZone = GameWindow.GameInput.getController(this->ID).getDeadZone(this->AimingAxisY);
 float float0 = this->AimingAxisDeadZone;
 if (float0 > 0.0F && float0 < 1.0F) {
 float float1 = GameWindow.GameInput.getAxisValue(this->ID, this->AimingAxisX);
 float float2 = GameWindow.GameInput.getAxisValue(this->ID, this->AimingAxisY);
 Vector2 vector = tempVec2.set(float1, float2);
 if (vector.getLength() < float0) {
 vector.set(0.0F, 0.0F);
 } else {
 vector.setLength((vector.getLength() - float0) / (1.0F - float0);
 }

 return this->AimingAxisYFlipped ? -vector.getY() : vector.getY();
 } else {
 return this->AimingAxisYFlipped
 ? -GameWindow.GameInput.getAxisValue(this->ID, this->AimingAxisY)
 : GameWindow.GameInput.getAxisValue(this->ID, this->AimingAxisY);
 }
 }
 }

 void onPressed(int i) {
 this->lastActivity = System.currentTimeMillis();
 }

 void onPressedAxis(int i) {
 this->lastActivity = System.currentTimeMillis();
 }

 void onPressedAxisNeg(int i) {
 this->lastActivity = System.currentTimeMillis();
 }

 void onPressedTrigger(int i) {
 this->lastActivity = System.currentTimeMillis();
 }

 void onPressedPov() {
 this->lastActivity = System.currentTimeMillis();
 }

 float getDeadZone(int axis) {
 if (axis >= 0 && axis < GameWindow.GameInput.getAxisCount(this->ID) {
 float float0 = GameWindow.GameInput.getController(this->ID).getDeadZone(axis);
 float float1 = 0.0F;
 if ((axis == this->MovementAxisX || axis == this->MovementAxisY) && this->MovementAxisDeadZone > 0.0F && this->MovementAxisDeadZone < 1.0F) {
 float1 = this->MovementAxisDeadZone;
 }

 if ((axis == this->AimingAxisX || axis == this->AimingAxisY) && this->AimingAxisDeadZone > 0.0F && this->AimingAxisDeadZone < 1.0F) {
 float1 = this->AimingAxisDeadZone;
 }

 return Math.max(float0, float1);
 } else {
 return 0.0F;
 }
 }

 void setDeadZone(int axis, float value) {
 if (axis >= 0 && axis < GameWindow.GameInput.getAxisCount(this->ID) {
 GameWindow.GameInput.getController(this->ID).setDeadZone(axis, value);
 }
 }

 void setDeadZone(float value) {
 for (int int0 = 0; int0 < GameWindow.GameInput.getAxisCount(this->ID); int0++) {
 GameWindow.GameInput.getController(this->ID).setDeadZone(int0, value);
 }
 }

 int getID() {
 return this->ID;
 }

 bool isDisabled() {
 return this->Disabled;
 }

 int getAButton() {
 return this->AButton;
 }

 int getBButton() {
 return this->BButton;
 }

 int getXButton() {
 return this->XButton;
 }

 int getYButton() {
 return this->YButton;
 }

 int getLBumper() {
 return this->BumperLeft;
 }

 int getRBumper() {
 return this->BumperRight;
 }

 int getL3() {
 return this->LeftStickButton;
 }

 int getR3() {
 return this->RightStickButton;
 }

 int getBackButton() {
 return this->Back;
 }

 int getStartButton() {
 return this->Start;
 }
 }
}
} // namespace input
} // namespace zombie
