#include "zombie/network/ReplayManager.h"

namespace zombie {
namespace network {

public
ReplayManager::ReplayManager(IsoPlayer playerx) {
  // TODO: Implement ReplayManager
  return nullptr;
}

bool ReplayManager::isPlay() {
  // TODO: Implement isPlay
  return false;
}

void ReplayManager::recordPlayerPacket(PlayerPacket playerPacket) {
  // TODO: Implement recordPlayerPacket
}

bool ReplayManager::startRecordReplay(IsoPlayer playerx,
                                      const std::string &string) {
  // TODO: Implement startRecordReplay
  return false;
}

bool ReplayManager::stopRecordReplay() {
  // TODO: Implement stopRecordReplay
  return false;
}

bool ReplayManager::startPlayReplay(IsoPlayer playerx,
                                    const std::string &string,
                                    UdpConnection udpConnection) {
  // TODO: Implement startPlayReplay
  return false;
}

bool ReplayManager::stopPlayReplay() {
  // TODO: Implement stopPlayReplay
  return false;
}

void ReplayManager::update() {
  // TODO: Implement update
}

} // namespace network
} // namespace zombie
