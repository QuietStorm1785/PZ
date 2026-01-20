#include "zombie\iso/ObjectsSyncRequests.h"

namespace zombie {
namespace iso {

public ObjectsSyncRequests::ObjectsSyncRequests(bool var1) {
    // TODO: Implement ObjectsSyncRequests
    return nullptr;
}

int ObjectsSyncRequests::getObjectInsertIndex(long[] var0, long[] var1, long var2) {
    // TODO: Implement getObjectInsertIndex
    return 0;
}

void ObjectsSyncRequests::putRequestSyncIsoChunk(IsoChunk var1) {
    // TODO: Implement putRequestSyncIsoChunk
}

void ObjectsSyncRequests::putRequestSyncItemContainer(ItemContainer var1) {
    // TODO: Implement putRequestSyncItemContainer
}

void ObjectsSyncRequests::putRequestSyncIsoGridSquare(IsoGridSquare var1) {
    // TODO: Implement putRequestSyncIsoGridSquare
}

void ObjectsSyncRequests::sendRequests(UdpConnection var1) {
    // TODO: Implement sendRequests
}

void ObjectsSyncRequests::receiveSyncIsoChunk(int var1, int var2) {
    // TODO: Implement receiveSyncIsoChunk
}

void ObjectsSyncRequests::receiveSyncIsoGridSquare(int var1, int var2, int var3) {
    // TODO: Implement receiveSyncIsoGridSquare
}

void ObjectsSyncRequests::receiveSyncIsoObject(int var1, int var2, int var3, long var4) {
    // TODO: Implement receiveSyncIsoObject
}

void ObjectsSyncRequests::receiveGridSquareHashes(ByteBuffer var1) {
    // TODO: Implement receiveGridSquareHashes
}

void ObjectsSyncRequests::receiveGridSquareObjectHashes(ByteBuffer var1) {
    // TODO: Implement receiveGridSquareObjectHashes
}

void ObjectsSyncRequests::receiveObject(ByteBuffer var1) {
    // TODO: Implement receiveObject
}

void ObjectsSyncRequests::serverSendRequests(UdpEngine var1) {
    // TODO: Implement serverSendRequests
}

void ObjectsSyncRequests::serverSendRequests(UdpConnection var1) {
    // TODO: Implement serverSendRequests
}

} // namespace iso
} // namespace zombie
