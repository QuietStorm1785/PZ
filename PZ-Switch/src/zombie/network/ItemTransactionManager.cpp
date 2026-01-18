#include "zombie/network/ItemTransactionManager.h"

namespace zombie {
namespace network {

void ItemTransactionManager::update() {
 // TODO: Implement update
}

bool ItemTransactionManager::isConsistent(int int0, int int1, int int2) {
 // TODO: Implement isConsistent
 return false;
}

void ItemTransactionManager::receiveOnClient(ByteBuffer byteBuffer,
 short var1) {
 // TODO: Implement receiveOnClient
}

void ItemTransactionManager::receiveOnServer(ByteBuffer byteBuffer,
 UdpConnection udpConnection,
 short var2) {
 // TODO: Implement receiveOnServer
}

void ItemTransactionManager::createItemTransaction(int int0, int int1,
 int int2) {
 // TODO: Implement createItemTransaction
}

void ItemTransactionManager::removeItemTransaction(int int0, int int1,
 int int2) {
 // TODO: Implement removeItemTransaction
}

void ItemTransactionManager::sendItemTransaction(UdpConnection udpConnection,
 uint8_t byte0, int int0,
 int int1, int int2) {
 // TODO: Implement sendItemTransaction
}

private
ItemTransactionManager::ItemRequest(int int0, int int1, int int2) {
 // TODO: Implement ItemRequest
 return nullptr;
}

void ItemTransactionManager::setState(uint8_t byte0) {
 // TODO: Implement setState
}

bool ItemTransactionManager::isTimeout() {
 // TODO: Implement isTimeout
 return false;
}

} // namespace network
} // namespace zombie
