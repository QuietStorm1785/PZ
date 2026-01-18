#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/glfw/GLFW.h"
#include "org/lwjgl/system/MemoryUtil.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace org {
namespace lwjglx {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Controllers {
public:
 static const int MAX_AXES = 6;
 static const int MAX_BUTTONS = 15;
 static const int MAX_CONTROLLERS = 16;
 private static Controller[] controllers = new Controller[16];
 static bool isCreated = false;
 private static Consumer<Integer> controllerConnectedCallback = nullptr;
 private static Consumer<Integer> controllerDisconnectedCallback = nullptr;
 static int debugToggleControllerPluggedIn = -1;

 static void create() {
 readGameControllerDB();
 GLFW.glfwSetJoystickCallback(Controllers::updateControllersCount);

 for (int int0 = 0; int0 < 16; int0++) {
 if (GLFW.glfwJoystickPresent(int0) {
 controllers[int0] = new Controller(int0);
 }
 }

 isCreated = true;
 }

 static void readGameControllerDB() {
 File file = new File("./media/gamecontrollerdb.txt").getAbsoluteFile();
 if (file.exists()) {
 readGameControllerDB(file);
 }

 std::string string = ZomboidFileSystem.instance.getCacheDirSub("joypads" + File.separator + "gamecontrollerdb.txt");
 file = new File(string);
 if (file.exists()) {
 readGameControllerDB(file);
 }
 }

 static void readGameControllerDB(File file) {
 try (
 FileReader fileReader = new FileReader(file);
 BufferedReader bufferedReader = new BufferedReader(fileReader);
 ) {
 StringBuilder stringBuilder = new StringBuilder();

 std::string string;
 while ((string = bufferedReader.readLine()) != nullptr) {
 if (!string.startsWith("#")) {
 stringBuilder.append(string);
 stringBuilder.append(System.lineSeparator());
 }
 }

 ByteBuffer byteBuffer = MemoryUtil.memUTF8(stringBuilder.toString());
 if (GLFW.glfwUpdateGamepadMappings(byteBuffer) {
 }

 MemoryUtil.memFree(byteBuffer);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }

 static void setControllerConnectedCallback(Consumer<Integer> consumer) {
 controllerConnectedCallback = consumer;
 }

 static void setControllerDisconnectedCallback(Consumer<Integer> consumer) {
 controllerDisconnectedCallback = consumer;
 }

 static int getControllerCount() {
 if (!isCreated()) {
 throw RuntimeException("Before calling 'getJoypadCount()' you should call 'create()' method");
 } else {
 return controllers.length;
 }
 }

 static Controller getController(int int0) {
 if (!isCreated()) {
 throw RuntimeException("Before calling 'getJoypad(int)' you should call 'create()' method");
 } else {
 return controllers[int0];
 }
 }

 static bool isCreated() {
 return isCreated;
 }

 static void poll(GamepadState[] gamepadStates) {
 if (!isCreated()) {
 throw RuntimeException("Before calling 'poll()' you should call 'create()' method");
 } else {
 if (Core.bDebug && debugToggleControllerPluggedIn >= 0 && debugToggleControllerPluggedIn < 16) {
 int int0 = debugToggleControllerPluggedIn;
 debugToggleControllerPluggedIn = -1;
 if (controllers[int0] != nullptr) {
 updateControllersCount(int0, 262146);
 } else if (GLFW.glfwJoystickIsGamepad(int0) {
 updateControllersCount(int0, 262145);
 }
 }

 for (int int1 = 0; int1 < controllers.length; int1++) {
 Controller controller = controllers[int1];
 if (controller != nullptr) {
 controller.poll(gamepadStates[int1]);
 }
 }
 }
 }

 static void updateControllersCount(int int1, int int0) {
 if (int0 == 262145) {
 Controller controller = new Controller(int1);
 controllers[int1] = controller;
 if (controllerConnectedCallback != nullptr) {
 controllerConnectedCallback.accept(int1);
 }
 } else if (int0 == 262146) {
 controllers[int1] = nullptr;
 if (controllerDisconnectedCallback != nullptr) {
 controllerDisconnectedCallback.accept(int1);
 }
 }
 }

 static void setDebugToggleControllerPluggedIn(int int0) {
 debugToggleControllerPluggedIn = int0;
 }
}
} // namespace input
} // namespace lwjglx
} // namespace org
