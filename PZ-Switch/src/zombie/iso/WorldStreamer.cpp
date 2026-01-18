#include "zombie/iso/WorldStreamer.h"

namespace zombie {
namespace iso {

int WorldStreamer::bufferSize(int int0) {
 // TODO: Implement bufferSize
 return 0;
}

ByteBuffer WorldStreamer::ensureCapacity(ByteBuffer byteBuffer0, int int0) {
 // TODO: Implement ensureCapacity
 return nullptr;
}

ByteBuffer WorldStreamer::getByteBuffer(int int0) {
 // TODO: Implement getByteBuffer
 return nullptr;
}

void WorldStreamer::releaseBuffer(ByteBuffer byteBuffer) {
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

ByteBuffer WorldStreamer::decompress(ByteBuffer byteBuffer) {
 // TODO: Implement decompress
 return nullptr;
}

void WorldStreamer::threadLoop() {
 // TODO: Implement threadLoop
}

void WorldStreamer::create() {
 // TODO: Implement create
}

void WorldStreamer::addJob(IsoChunk chunk, int int0, int int1, bool boolean0) {
 // TODO: Implement addJob
}

void WorldStreamer::DoChunk(IsoChunk chunk, ByteBuffer byteBuffer) {
 // TODO: Implement DoChunk
}

void WorldStreamer::DoChunkAlways(IsoChunk chunk, ByteBuffer byteBuffer) {
 // TODO: Implement DoChunkAlways
}

void WorldStreamer::addJobInstant(IsoChunk chunk, int var2, int var3, int int0,
 int int1) {
 // TODO: Implement addJobInstant
}

void WorldStreamer::addJobConvert(IsoChunk chunk, int var2, int var3, int int0,
 int int1) {
 // TODO: Implement addJobConvert
}

void WorldStreamer::addJobWipe(IsoChunk chunk, int var2, int var3, int int0,
 int int1) {
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

void WorldStreamer::requestLargeAreaZip(int int0, int int1, int int4) {
 // TODO: Implement requestLargeAreaZip
}

void WorldStreamer::cancelOutOfBoundsRequests() {
 // TODO: Implement cancelOutOfBoundsRequests
}

void WorldStreamer::resendTimedOutRequests() {
 // TODO: Implement resendTimedOutRequests
}

void WorldStreamer::receiveChunkPart(ByteBuffer byteBuffer) {
 // TODO: Implement receiveChunkPart
}

void WorldStreamer::receiveNotRequired(ByteBuffer byteBuffer) {
 // TODO: Implement receiveNotRequired
}

void WorldStreamer::compare(WorldStreamer.ChunkRequest chunkRequest,
 ByteBuffer byteBuffer, File file) {
 // TODO: Implement compare
}

void WorldStreamer::compareChunks(IsoChunk chunk0, IsoChunk chunk1) {
 // TODO: Implement compareChunks
}

void WorldStreamer::compareErosion(IsoChunk chunk1, IsoChunk chunk0) {
 // TODO: Implement compareErosion
}

void WorldStreamer::compareSquares(IsoGridSquare square1,
 IsoGridSquare square0) {
 // TODO: Implement compareSquares
}

public
WorldStreamer::ChunkComparator() {
 // TODO: Implement ChunkComparator
 return nullptr;
}

void WorldStreamer::init() {
 // TODO: Implement init
}

int WorldStreamer::compare(IsoChunk chunk0, IsoChunk chunk1) {
 // TODO: Implement compare
 return 0;
}

bool WorldStreamer::isReceived() {
 // TODO: Implement isReceived
 return false;
}

void WorldStreamer::release(WorldStreamer.ChunkRequest chunkRequest) {
 // TODO: Implement release
}

} // namespace iso
} // namespace zombie
