#include "org/lwjglx/input/Controllers.h"

namespace org {
namespace lwjglx {
namespace input {

void Controllers::create() {
 // TODO: Implement create
}

void Controllers::readGameControllerDB() {
 // TODO: Implement readGameControllerDB
}

void Controllers::readGameControllerDB(File file) {
 // TODO: Implement readGameControllerDB
}

void Controllers::setControllerConnectedCallback(Consumer<Integer> consumer) {
 // TODO: Implement setControllerConnectedCallback
}

void Controllers::setControllerDisconnectedCallback(
 Consumer<Integer> consumer) {
 // TODO: Implement setControllerDisconnectedCallback
}

int Controllers::getControllerCount() {
 // TODO: Implement getControllerCount
 return 0;
}

Controller Controllers::getController(int int0) {
 // TODO: Implement getController
 return nullptr;
}

bool Controllers::isCreated() {
 // TODO: Implement isCreated
 return false;
}

void Controllers::poll(GamepadState[] gamepadStates) {
 // TODO: Implement poll
}

void Controllers::updateControllersCount(int int1, int int0) {
 // TODO: Implement updateControllersCount
}

void Controllers::setDebugToggleControllerPluggedIn(int int0) {
 // TODO: Implement setDebugToggleControllerPluggedIn
}

} // namespace input
} // namespace lwjglx
} // namespace org
