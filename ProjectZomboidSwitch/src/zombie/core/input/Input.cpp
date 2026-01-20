#include <string>
#include "zombie\core\input/Input.h"

namespace zombie {
namespace core {
namespace input {

std::string Input::getKeyName(int var0) {
    // TODO: Implement getKeyName
    return "";
}

int Input::getKeyCode(const std::string& var0) {
    // TODO: Implement getKeyCode
    return 0;
}

int Input::getControllerCount() {
    // TODO: Implement getControllerCount
    return 0;
}

int Input::getAxisCount(int var1) {
    // TODO: Implement getAxisCount
    return 0;
}

float Input::getAxisValue(int var1, int var2) {
    // TODO: Implement getAxisValue
    return 0;
}

std::string Input::getAxisName(int var1, int var2) {
    // TODO: Implement getAxisName
    return "";
}

bool Input::isControllerLeftD(int var1) {
    // TODO: Implement isControllerLeftD
    return false;
}

bool Input::isControllerRightD(int var1) {
    // TODO: Implement isControllerRightD
    return false;
}

bool Input::isControllerUpD(int var1) {
    // TODO: Implement isControllerUpD
    return false;
}

bool Input::isControllerDownD(int var1) {
    // TODO: Implement isControllerDownD
    return false;
}

Controller Input::checkControllerButton(int var1, int var2) {
    // TODO: Implement checkControllerButton
    return nullptr;
}

bool Input::isButtonPressedD(int var1, int var2) {
    // TODO: Implement isButtonPressedD
    return false;
}

bool Input::wasButtonPressed(int var1, int var2) {
    // TODO: Implement wasButtonPressed
    return false;
}

bool Input::isButtonStartPress(int var1, int var2) {
    // TODO: Implement isButtonStartPress
    return false;
}

bool Input::isButtonReleasePress(int var1, int var2) {
    // TODO: Implement isButtonReleasePress
    return false;
}

void Input::initControllers() {
    // TODO: Implement initControllers
}

void Input::onControllerConnected(Controller var1) {
    // TODO: Implement onControllerConnected
}

void Input::onControllerDisconnected(Controller var1) {
    // TODO: Implement onControllerDisconnected
}

void Input::poll() {
    // TODO: Implement poll
}

Controller Input::getController(int var1) {
    // TODO: Implement getController
    return nullptr;
}

int Input::getButtonCount(int var1) {
    // TODO: Implement getButtonCount
    return 0;
}

std::string Input::getButtonName(int var1, int var2) {
    // TODO: Implement getButtonName
    return "";
}

void Input::updateGameThread() {
    // TODO: Implement updateGameThread
}

bool Input::checkConnectDisconnect(ControllerState var1) {
    // TODO: Implement checkConnectDisconnect
    return false;
}

void Input::quit() {
    // TODO: Implement quit
}

} // namespace input
} // namespace core
} // namespace zombie
