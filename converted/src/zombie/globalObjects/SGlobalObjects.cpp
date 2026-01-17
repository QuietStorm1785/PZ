#include "zombie/globalObjects/SGlobalObjects.h"

namespace zombie {
namespace globalObjects {

void SGlobalObjects::noise(const std::string &message) {
  // TODO: Implement noise
}

SGlobalObjectSystem SGlobalObjects::registerSystem(const std::string &name) {
  // TODO: Implement registerSystem
  return nullptr;
}

SGlobalObjectSystem SGlobalObjects::newSystem(const std::string &name) {
  // TODO: Implement newSystem
  return nullptr;
}

int SGlobalObjects::getSystemCount() {
  // TODO: Implement getSystemCount
  return 0;
}

SGlobalObjectSystem SGlobalObjects::getSystemByIndex(int index) {
  // TODO: Implement getSystemByIndex
  return nullptr;
}

SGlobalObjectSystem SGlobalObjects::getSystemByName(const std::string &name) {
  // TODO: Implement getSystemByName
  return nullptr;
}

void SGlobalObjects::update() {
  // TODO: Implement update
}

void SGlobalObjects::chunkLoaded(int wx, int wy) {
  // TODO: Implement chunkLoaded
}

void SGlobalObjects::initSystems() {
  // TODO: Implement initSystems
}

void SGlobalObjects::saveInitialStateForClient(ByteBuffer bb) {
  // TODO: Implement saveInitialStateForClient
}

bool SGlobalObjects::receiveClientCommand(const std::string &systemName,
                                          const std::string &command,
                                          IsoPlayer playerObj,
                                          KahluaTable args) {
  // TODO: Implement receiveClientCommand
  return false;
}

void SGlobalObjects::load() {
  // TODO: Implement load
}

void SGlobalObjects::save() {
  // TODO: Implement save
}

void SGlobalObjects::OnIsoObjectChangedItself(const std::string &systemName,
                                              IsoObject isoObject) {
  // TODO: Implement OnIsoObjectChangedItself
}

void SGlobalObjects::Reset() {
  // TODO: Implement Reset
}

} // namespace globalObjects
} // namespace zombie
