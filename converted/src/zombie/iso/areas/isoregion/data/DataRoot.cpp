#include "zombie/iso/areas/isoregion/data/DataRoot.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace data {

public DataRoot::DataRoot() {
 // TODO: Implement DataRoot
 return nullptr;
}

void DataRoot::getAllChunks(List<DataChunk> list) {
 // TODO: Implement getAllChunks
}

DataCell DataRoot::getCell(int int0) {
 // TODO: Implement getCell
 return nullptr;
}

DataCell DataRoot::addCell(int int0, int int1, int int2) {
 // TODO: Implement addCell
 return nullptr;
}

DataChunk DataRoot::getDataChunk(int chunkx, int chunky) {
 // TODO: Implement getDataChunk
 return nullptr;
}

void DataRoot::setDataChunk(DataChunk dataChunk) {
 // TODO: Implement setDataChunk
}

IsoWorldRegion DataRoot::getIsoWorldRegion(int x, int y, int z) {
 // TODO: Implement getIsoWorldRegion
 return nullptr;
}

uint8_t DataRoot::getSquareFlags(int x, int y, int z) {
 // TODO: Implement getSquareFlags
 return 0;
}

IsoChunkRegion DataRoot::getIsoChunkRegion(int x, int y, int z) {
 // TODO: Implement getIsoChunkRegion
 return nullptr;
}

void DataRoot::resetAllData() {
 // TODO: Implement resetAllData
}

void DataRoot::EnqueueDirtyDataChunk(DataChunk chunk) {
 // TODO: Implement EnqueueDirtyDataChunk
}

void DataRoot::EnqueueDirtyIsoWorldRegion(IsoWorldRegion mr) {
 // TODO: Implement EnqueueDirtyIsoWorldRegion
}

void DataRoot::DequeueDirtyIsoWorldRegion(IsoWorldRegion mr) {
 // TODO: Implement DequeueDirtyIsoWorldRegion
}

void DataRoot::updateExistingSquare(int x, int y, int z, uint8_t flags) {
 // TODO: Implement updateExistingSquare
}

void DataRoot::processDirtyChunks() {
 // TODO: Implement processDirtyChunks
}

private DataRoot::SelectInfo(DataRoot dataRoot) {
 // TODO: Implement SelectInfo
 return nullptr;
}

void DataRoot::reset(int _x, int _y, int _z, bool createSquare) {
 // TODO: Implement reset
}

void DataRoot::reset(int _x, int _y, int _z, bool createChunk, bool createSquare) {
 // TODO: Implement reset
}

void DataRoot::ensureCell(bool boolean0) {
 // TODO: Implement ensureCell
}

void DataRoot::ensureChunk(bool boolean0) {
 // TODO: Implement ensureChunk
}

void DataRoot::ensureSquare(bool boolean0) {
 // TODO: Implement ensureSquare
}

} // namespace data
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
