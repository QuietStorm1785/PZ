#include "zombie\popman/NetworkZombieManager.h"

namespace zombie {
namespace popman {

NetworkZombieManager NetworkZombieManager::getInstance() {
    // TODO: Implement getInstance
    return nullptr;
}

int NetworkZombieManager::getAuthorizedZombieCount(UdpConnection var1) {
    // TODO: Implement getAuthorizedZombieCount
    return 0;
}

int NetworkZombieManager::getUnauthorizedZombieCount() {
    // TODO: Implement getUnauthorizedZombieCount
    return 0;
}

bool NetworkZombieManager::canSpotted(IsoZombie var0) {
    // TODO: Implement canSpotted
    return false;
}

void NetworkZombieManager::updateAuth(IsoZombie var1) {
    // TODO: Implement updateAuth
}

void NetworkZombieManager::moveZombie(IsoZombie var1, UdpConnection var2, IsoPlayer var3) {
    // TODO: Implement moveZombie
}

void NetworkZombieManager::getZombieAuth(UdpConnection var1, ByteBuffer var2) {
    // TODO: Implement getZombieAuth
}

void NetworkZombieManager::clearTargetAuth(UdpConnection var1, IsoPlayer var2) {
    // TODO: Implement clearTargetAuth
}

void NetworkZombieManager::removeZombies(UdpConnection var0) {
    // TODO: Implement removeZombies
}

void NetworkZombieManager::recheck(UdpConnection var1) {
    // TODO: Implement recheck
}

} // namespace popman
} // namespace zombie
