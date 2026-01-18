#include "zombie/core/input/Input.h"

namespace zombie {
namespace core {
namespace input {

std::string Input::getKeyName(int code) {
 // TODO: Implement getKeyName
 return "";
}

int Input::getKeyCode(const std::string &keyName) {
 // TODO: Implement getKeyCode
 return 0;
}

int Input::getControllerCount() {
 // TODO: Implement getControllerCount
 return 0;
}

int Input::getAxisCount(int index) {
 // TODO: Implement getAxisCount
 return 0;
}

float Input::getAxisValue(int index, int axis) {
 // TODO: Implement getAxisValue
 return 0;
}

std::string Input::getAxisName(int index, int axis) {
 // TODO: Implement getAxisName
 return "";
}

bool Input::isControllerLeftD(int index) {
 // TODO: Implement isControllerLeftD
 return false;
}

bool Input::isControllerRightD(int index) {
 // TODO: Implement isControllerRightD
 return false;
}

bool Input::isControllerUpD(int index) {
 // TODO: Implement isControllerUpD
 return false;
}

bool Input::isControllerDownD(int index) {
 // TODO: Implement isControllerDownD
 return false;
}

Controller Input::checkControllerButton(int int0, int int1) {
 // TODO: Implement checkControllerButton
 return nullptr;
}

bool Input::isButtonPressedD(int button, int index) {
 // TODO: Implement isButtonPressedD
 return false;
}

bool Input::wasButtonPressed(int index, int button) {
 // TODO: Implement wasButtonPressed
 return false;
}

bool Input::isButtonStartPress(int index, int button) {
 // TODO: Implement isButtonStartPress
 return false;
}

bool Input::isButtonReleasePress(int index, int button) {
 // TODO: Implement isButtonReleasePress
 return false;
}

void Input::initControllers() {
 // TODO: Implement initControllers
}

void Input::onControllerConnected(Controller controller) {
 // TODO: Implement onControllerConnected
}

void Input::onControllerDisconnected(Controller controller) {
 // TODO: Implement onControllerDisconnected
}

void Input::poll() {
 // TODO: Implement poll
}

Controller Input::getController(int index) {
 // TODO: Implement getController
 return nullptr;
}

int Input::getButtonCount(int index) {
 // TODO: Implement getButtonCount
 return 0;
}

std::string Input::getButtonName(int index, int button) {
 // TODO: Implement getButtonName
 return "";
}

void Input::updateGameThread() {
 // TODO: Implement updateGameThread
}

bool Input::checkConnectDisconnect(ControllerState controllerState) {
 // TODO: Implement checkConnectDisconnect
 return false;
}

void Input::quit() {
 // TODO: Implement quit
}

} // namespace input
} // namespace core
} // namespace zombie
