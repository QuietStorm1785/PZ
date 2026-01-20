#include <string>
#include "zombie\globalObjects/SGlobalObjectSystem.h"

namespace zombie {
namespace globalObjects {

public SGlobalObjectSystem::SGlobalObjectSystem(const std::string& var1) {
    // TODO: Implement SGlobalObjectSystem
    return nullptr;
}

GlobalObject SGlobalObjectSystem::makeObject(int var1, int var2, int var3) {
    // TODO: Implement makeObject
    return nullptr;
}

void SGlobalObjectSystem::setModDataKeys(KahluaTable var1) {
    // TODO: Implement setModDataKeys
}

void SGlobalObjectSystem::setObjectModDataKeys(KahluaTable var1) {
    // TODO: Implement setObjectModDataKeys
}

void SGlobalObjectSystem::setObjectSyncKeys(KahluaTable var1) {
    // TODO: Implement setObjectSyncKeys
}

void SGlobalObjectSystem::update() {
    // TODO: Implement update
}

void SGlobalObjectSystem::chunkLoaded(int var1, int var2) {
    // TODO: Implement chunkLoaded
}

void SGlobalObjectSystem::sendCommand(const std::string& var1, KahluaTable var2) {
    // TODO: Implement sendCommand
}

void SGlobalObjectSystem::receiveClientCommand(const std::string& var1, IsoPlayer var2, KahluaTable var3) {
    // TODO: Implement receiveClientCommand
}

void SGlobalObjectSystem::addGlobalObjectOnClient(SGlobalObject var1) {
    // TODO: Implement addGlobalObjectOnClient
}

void SGlobalObjectSystem::removeGlobalObjectOnClient(SGlobalObject var1) {
    // TODO: Implement removeGlobalObjectOnClient
}

void SGlobalObjectSystem::updateGlobalObjectOnClient(SGlobalObject var1) {
    // TODO: Implement updateGlobalObjectOnClient
}

std::string SGlobalObjectSystem::getFileName() {
    // TODO: Implement getFileName
    return "";
}

KahluaTable SGlobalObjectSystem::getInitialStateForClient() {
    // TODO: Implement getInitialStateForClient
    return nullptr;
}

void SGlobalObjectSystem::OnIsoObjectChangedItself(IsoObject var1) {
    // TODO: Implement OnIsoObjectChangedItself
}

int SGlobalObjectSystem::loadedWorldVersion() {
    // TODO: Implement loadedWorldVersion
    return 0;
}

void SGlobalObjectSystem::load(ByteBuffer var1, int var2) {
    // TODO: Implement load
}

void SGlobalObjectSystem::save(ByteBuffer var1) {
    // TODO: Implement save
}

void SGlobalObjectSystem::load() {
    // TODO: Implement load
}

void SGlobalObjectSystem::save() {
    // TODO: Implement save
}

void SGlobalObjectSystem::Reset() {
    // TODO: Implement Reset
}

} // namespace globalObjects
} // namespace zombie
