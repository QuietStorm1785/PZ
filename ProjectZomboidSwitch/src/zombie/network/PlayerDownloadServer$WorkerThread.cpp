#include "zombie\network/PlayerDownloadServer$WorkerThread.h"

namespace zombie {
namespace network {

void PlayerDownloadServer$WorkerThread::run() {
    // TODO: Implement run
}

void PlayerDownloadServer$WorkerThread::runInner() {
    // TODO: Implement runInner
}

void PlayerDownloadServer$WorkerThread::putCommand(EThreadCommand var1, ClientChunkRequest var2) {
    // TODO: Implement putCommand
}

int PlayerDownloadServer$WorkerThread::compressChunk(Chunk var1) {
    // TODO: Implement compressChunk
    return 0;
}

void PlayerDownloadServer$WorkerThread::sendChunk(Chunk var1) {
    // TODO: Implement sendChunk
}

void PlayerDownloadServer$WorkerThread::sendNotRequired(Chunk var1, bool var2) {
    // TODO: Implement sendNotRequired
}

void PlayerDownloadServer$WorkerThread::sendLargeArea(ClientChunkRequest var1) {
    // TODO: Implement sendLargeArea
}

void PlayerDownloadServer$WorkerThread::sendArray(ClientChunkRequest var1) {
    // TODO: Implement sendArray
}

bool PlayerDownloadServer$WorkerThread::isRequestCancelled(Chunk var1) {
    // TODO: Implement isRequestCancelled
    return false;
}

} // namespace network
} // namespace zombie
