#include "zombie/iso/areas/isoregion/jobs/JobChunkUpdate.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace jobs {

protected JobChunkUpdate::JobChunkUpdate() {
 // TODO: Implement JobChunkUpdate
 return nullptr;
}

void JobChunkUpdate::reset() {
 // TODO: Implement reset
}

UdpConnection JobChunkUpdate::getTargetConn() {
 // TODO: Implement getTargetConn
 return nullptr;
}

void JobChunkUpdate::setTargetConn(UdpConnection udpConnection) {
 // TODO: Implement setTargetConn
}

int JobChunkUpdate::getChunkCount() {
 // TODO: Implement getChunkCount
 return 0;
}

ByteBuffer JobChunkUpdate::getBuffer() {
 // TODO: Implement getBuffer
 return nullptr;
}

long JobChunkUpdate::getNetTimeStamp() {
 // TODO: Implement getNetTimeStamp
 return 0;
}

void JobChunkUpdate::setNetTimeStamp(long long0) {
 // TODO: Implement setNetTimeStamp
}

bool JobChunkUpdate::readChunksPacket(DataRoot dataRoot, List<Integer> list) {
 // TODO: Implement readChunksPacket
 return false;
}

bool JobChunkUpdate::saveChunksToDisk() {
 // TODO: Implement saveChunksToDisk
 return false;
}

bool JobChunkUpdate::saveChunksToNetBuffer(ByteBuffer byteBuffer) {
 // TODO: Implement saveChunksToNetBuffer
 return false;
}

bool JobChunkUpdate::readChunksFromNetBuffer(ByteBuffer byteBuffer, long long0) {
 // TODO: Implement readChunksFromNetBuffer
 return false;
}

bool JobChunkUpdate::canAddChunk() {
 // TODO: Implement canAddChunk
 return false;
}

int JobChunkUpdate::startBufferBlock() {
 // TODO: Implement startBufferBlock
 return 0;
}

void JobChunkUpdate::endBufferBlock(int int0) {
 // TODO: Implement endBufferBlock
}

bool JobChunkUpdate::addChunkFromDataChunk(DataChunk dataChunk) {
 // TODO: Implement addChunkFromDataChunk
 return false;
}

bool JobChunkUpdate::addChunkFromIsoChunk(IsoChunk chunk) {
 // TODO: Implement addChunkFromIsoChunk
 return false;
}

bool JobChunkUpdate::addChunkFromFile(ByteBuffer byteBuffer) {
 // TODO: Implement addChunkFromFile
 return false;
}

} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
