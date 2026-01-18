#include "zombie/popman/NetworkZombieManager.h"

namespace zombie {
namespace popman {

NetworkZombieManager NetworkZombieManager::getInstance() {
  // TODO: Implement getInstance
  return nullptr;
}

int NetworkZombieManager::getAuthorizedZombieCount(
    UdpConnection udpConnection) {
  // TODO: Implement getAuthorizedZombieCount
  return 0;
}

int NetworkZombieManager::getUnauthorizedZombieCount() {
  // TODO: Implement getUnauthorizedZombieCount
  return 0;
}

bool NetworkZombieManager::canSpotted(IsoZombie zombie0) {
  // TODO: Implement canSpotted
  return false;
}

void NetworkZombieManager::updateAuth(IsoZombie zombie0) {
  // TODO: Implement updateAuth
}

void NetworkZombieManager::moveZombie(IsoZombie zombie0,
                                      UdpConnection udpConnection,
                                      IsoPlayer player) {
  // TODO: Implement moveZombie
}

void NetworkZombieManager::getZombieAuth(UdpConnection udpConnection,
                                         ByteBuffer byteBuffer) {
  // TODO: Implement getZombieAuth
}

void NetworkZombieManager::clearTargetAuth(UdpConnection udpConnection,
                                           IsoPlayer player) {
  // TODO: Implement clearTargetAuth
}

void NetworkZombieManager::removeZombies(UdpConnection udpConnection) {
  // TODO: Implement removeZombies
}

void NetworkZombieManager::recheck(UdpConnection udpConnection) {
  // TODO: Implement recheck
}

} // namespace popman
} // namespace zombie
