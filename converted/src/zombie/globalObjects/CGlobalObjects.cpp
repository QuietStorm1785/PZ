#include "zombie/globalObjects/CGlobalObjects.h"

namespace zombie {
namespace globalObjects {

void CGlobalObjects::noise(const std::string &message) {
  // TODO: Implement noise
}

CGlobalObjectSystem CGlobalObjects::registerSystem(const std::string &name) {
  // TODO: Implement registerSystem
  return nullptr;
}

CGlobalObjectSystem CGlobalObjects::newSystem(const std::string &name) {
  // TODO: Implement newSystem
  return nullptr;
}

int CGlobalObjects::getSystemCount() {
  // TODO: Implement getSystemCount
  return 0;
}

CGlobalObjectSystem CGlobalObjects::getSystemByIndex(int index) {
  // TODO: Implement getSystemByIndex
  return nullptr;
}

CGlobalObjectSystem CGlobalObjects::getSystemByName(const std::string &name) {
  // TODO: Implement getSystemByName
  return nullptr;
}

void CGlobalObjects::initSystems() {
  // TODO: Implement initSystems
}

void CGlobalObjects::loadInitialState(ByteBuffer bb) {
  // TODO: Implement loadInitialState
}

bool CGlobalObjects::receiveServerCommand(const std::string &systemName,
                                          const std::string &command,
                                          KahluaTable args) {
  // TODO: Implement receiveServerCommand
  return false;
}

void CGlobalObjects::Reset() {
  // TODO: Implement Reset
}

} // namespace globalObjects
} // namespace zombie
