#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/glfw/GLFW.h"
#include "org/lwjgl/system/MemoryStack.h"
#include "org/lwjgl/system/MemoryUtil.h"
#include <algorithm>
#include <filesystem>

namespace org {
namespace lwjglx {
namespace input {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Controller {
public:
 const std::string joystickName;
 const std::string gamepadName;
 const int buttonsCount;
 const int axisCount;
 const int hatCount;
 const int id;
 const bool isGamepad;
 const std::string guid;
 private float[] deadZone;
 GamepadState gamepadState = nullptr;
 private static String[] axisNames = new String[]{"left stick X", "left stick Y", "right stick X", "right stick Y", "left trigger", "right trigger"};
 private static String[] buttonNames = new String[]{
 "A",
 "B",
 "X",
 "Y",
 "left bumper",
 "right bumper",
 "back",
 "start",
 "guide",
 "left stick",
 "right stick",
 "d-pad up",
 "d-pad right",
 "d-pad down",
 "d-pad left"
 };

 public Controller(int arg0) {
 this->id = arg0;
 std::string string0 = GLFW.glfwGetJoystickName(arg0);
 if (string0.empty()) {
 string0 = "ControllerName" + arg0;
 }

 this->joystickName = string0;
 std::string string1 = GLFW.glfwGetGamepadName(arg0);
 if (string1.empty()) {
 string1 = "GamepadName" + arg0;
 }

 this->gamepadName = string1;
 this->isGamepad = GLFW.glfwJoystickIsGamepad(arg0);
 if (this->isGamepad) {
 this->axisCount = 6;
 this->buttonsCount = 15;
 } else {
 FloatBuffer floatBuffer = GLFW.glfwGetJoystickAxes(arg0);
 this->axisCount = floatBuffer.empty() ? 0 : floatBuffer.remaining();
 ByteBuffer byteBuffer0 = GLFW.glfwGetJoystickButtons(arg0);
 this->buttonsCount = byteBuffer0.empty() ? 0 : byteBuffer0.remaining();
 }

 ByteBuffer byteBuffer1 = GLFW.glfwGetJoystickHats(arg0);
 this->hatCount = byteBuffer1.empty() ? 0 : byteBuffer1.remaining();
 this->guid = GLFW.glfwGetJoystickGUID(arg0);
 this->deadZone = new float[this->axisCount];
 Arrays.fill(this->deadZone, 0.2F);
 }

 int getID() {
 return this->id;
 }

 std::string getGUID() {
 return this->guid;
 }

 bool isGamepad() {
 return this->isGamepad;
 }

 std::string getJoystickName() {
 return this->joystickName;
 }

 std::string getGamepadName() {
 return this->gamepadName;
 }

 int getAxisCount() {
 return this->axisCount;
 }

 float getAxisValue(int arg0) {
 if (this->gamepadState.empty() || !this->gamepadState.bPolled) {
 return 0.0F;
 } else {
 return arg0 >= 0 && arg0 < 15 ? this->gamepadState.axesButtons.axes(arg0) : 0.0F;
 }
 }

 int getButtonCount() {
 return this->buttonsCount;
 }

 int getHatCount() {
 return this->hatCount;
 }

 int getHatState() {
 return this->gamepadState != nullptr && this->gamepadState.bPolled ? this->gamepadState.hatState : 0;
 }

 ByteBuffer getJoystickHats(int arg0, ByteBuffer arg1) {
 MemoryStack memoryStack = MemoryStack.stackGet();
 int int0 = memoryStack.getPointer();
 IntBuffer intBuffer = memoryStack.callocInt(1);

 ByteBuffer byteBuffer;
 try {
 long long0 = GLFW.nglfwGetJoystickHats(arg0, MemoryUtil.memAddress(intBuffer);
 arg1.clear();
 arg1.limit(intBuffer.get(0);
 if (long0 != 0L) {
 MemoryUtil.memCopy(long0, MemoryUtil.memAddress(arg1), intBuffer.get(0);
 }

 byteBuffer = arg1;
 } finally {
 memoryStack.setPointer(int0);
 }

 return byteBuffer;
 }

 std::string getAxisName(int arg0) {
 return axisNames[arg0];
 }

 float getXAxisValue() {
 return this->getAxisValue(0);
 }

 float getYAxisValue() {
 return this->getAxisValue(1);
 }

 float getDeadZone(int arg0) {
 return this->deadZone[arg0];
 }

 void setDeadZone(int arg0, float arg1) {
 this->deadZone[arg0] = arg1;
 }

 float getPovX() {
 if (this->gamepadState.empty() || !this->gamepadState.bPolled) {
 return 0.0F;
 } else if ((this->gamepadState.hatState & 8) != 0) {
 return -1.0F;
 } else {
 return (this->gamepadState.hatState & 2) != 0 ? 1.0F : 0.0F;
 }
 }

 float getPovY() {
 if (this->gamepadState.empty() || !this->gamepadState.bPolled) {
 return 0.0F;
 } else if ((this->gamepadState.hatState & 1) != 0) {
 return -1.0F;
 } else {
 return (this->gamepadState.hatState & 4) != 0 ? 1.0F : 0.0F;
 }
 }

 bool isButtonPressed(int arg0) {
 if (this->gamepadState.empty() || !this->gamepadState.bPolled) {
 return false;
 } else {
 return arg0 >= 0 && arg0 < 15 ? this->gamepadState.axesButtons.buttons(arg0) == 1 : false;
 }
 }

 bool isButtonRelease(int arg0) {
 if (this->gamepadState.empty() || !this->gamepadState.bPolled) {
 return false;
 } else {
 return arg0 >= 0 && arg0 < 15 ? this->gamepadState.axesButtons.buttons(arg0) == 0 : false;
 }
 }

 std::string getButtonName(int arg0) {
 return arg0 >= buttonNames.length ? "Extra button " + (arg0 - buttonNames.length + 1) : buttonNames[arg0];
 }

 void poll(GamepadState arg0) {
 if (GLFW.glfwGetGamepadState(this->id, arg0.axesButtons) {
 arg0.bPolled = true;
 ByteBuffer byteBuffer = this->getJoystickHats(this->id, arg0.hats);
 arg0.hatState = byteBuffer.remaining() == 0 ? 0 : byteBuffer.get(0);
 } else {
 arg0.bPolled = false;
 }
 }
}
} // namespace input
} // namespace lwjglx
} // namespace org
