#include "zombie\iso/WorldStreamer.h"

namespace zombie {
namespace iso {

int WorldStreamer::bufferSize(int var1) {
    // TODO: Implement bufferSize
    return 0;
}

ByteBuffer WorldStreamer::ensureCapacity(ByteBuffer var1, int var2) {
    // TODO: Implement ensureCapacity
    return nullptr;
}

ByteBuffer WorldStreamer::getByteBuffer(int var1) {
    // TODO: Implement getByteBuffer
    return nullptr;
}

void WorldStreamer::releaseBuffer(ByteBuffer var1) {
    // TODO: Implement releaseBuffer
}

void WorldStreamer::sendRequests() {
    // TODO: Implement sendRequests
}

void WorldStreamer::updateMain() {
    // TODO: Implement updateMain
}

void WorldStreamer::getStatistics() {
    // TODO: Implement getStatistics
}

void WorldStreamer::loadReceivedChunks() {
    // TODO: Implement loadReceivedChunks
}

ByteBuffer WorldStreamer::decompress(ByteBuffer var1) {
    // TODO: Implement decompress
    return nullptr;
}

void WorldStreamer::threadLoop() {
    // TODO: Implement threadLoop
}

void WorldStreamer::create() {
    // TODO: Implement create
}

void WorldStreamer::addJob(IsoChunk var1, int var2, int var3, bool var4) {
    // TODO: Implement addJob
}

void WorldStreamer::DoChunk(IsoChunk var1, ByteBuffer var2) {
    // TODO: Implement DoChunk
}

void WorldStreamer::DoChunkAlways(IsoChunk var1, ByteBuffer var2) {
    // TODO: Implement DoChunkAlways
}

void WorldStreamer::addJobInstant(IsoChunk var1, int var2, int var3, int var4, int var5) {
    // TODO: Implement addJobInstant
}

void WorldStreamer::addJobConvert(IsoChunk var1, int var2, int var3, int var4, int var5) {
    // TODO: Implement addJobConvert
}

void WorldStreamer::addJobWipe(IsoChunk var1, int var2, int var3, int var4, int var5) {
    // TODO: Implement addJobWipe
}

bool WorldStreamer::isBusy() {
    // TODO: Implement isBusy
    return false;
}

void WorldStreamer::stop() {
    // TODO: Implement stop
}

void WorldStreamer::quit() {
    // TODO: Implement quit
}

void WorldStreamer::requestLargeAreaZip(int var1, int var2, int var3) {
    // TODO: Implement requestLargeAreaZip
}

void WorldStreamer::cancelOutOfBoundsRequests() {
    // TODO: Implement cancelOutOfBoundsRequests
}

void WorldStreamer::resendTimedOutRequests() {
    // TODO: Implement resendTimedOutRequests
}

void WorldStreamer::receiveChunkPart(ByteBuffer var1) {
    // TODO: Implement receiveChunkPart
}

void WorldStreamer::receiveNotRequired(ByteBuffer var1) {
    // TODO: Implement receiveNotRequired
}

void WorldStreamer::compare(ChunkRequest var1, ByteBuffer var2, File var3) {
    // TODO: Implement compare
}

void WorldStreamer::compareChunks(IsoChunk var1, IsoChunk var2) {
    // TODO: Implement compareChunks
}

void WorldStreamer::compareErosion(IsoChunk var1, IsoChunk var2) {
    // TODO: Implement compareErosion
}

void WorldStreamer::compareSquares(IsoGridSquare var1, IsoGridSquare var2) {
    // TODO: Implement compareSquares
}

} // namespace iso
} // namespace zombie
